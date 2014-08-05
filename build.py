#!/usr/bin/python -u 
import sys
import os
import subprocess
import platform
import argparse
import urllib
import urllib2
import json
import base64
import time
import ast

#
# Parse command line
#
parser = argparse.ArgumentParser()
parser.add_argument("-b", "--build", help="If you want the source to be built", action="store_true")
parser.add_argument("-c", "--config", help="Configuration to build (debug, release, etc.)", default="Debug")
parser.add_argument("-j", "--jenkins", help="Jenkins server to build on")
parser.add_argument("-g", "--generator", help="CMake generator to use")
args = parser.parse_args()

#
# Global build stuff
#
buildStartTime = time.time() * 1000
if not os.path.isdir("_build"):
    os.mkdir("_build")
os.chdir("_build")

#
# jenkins
#
class Job:
    def __init__(self, jenkins, name, config, target, generator, url):
        self.jenkins    = jenkins
        self.name       = name
        self.config     = config
        self.target     = target
        self.generator  = generator
        self.url        = url
        self.node       = None
        self.fullUrl    = None
        self.result     = None
        self.buildUrl   = None
        self.duration   = None

    def findUrl(self):
        self.url = None

    def jobString(self):
        return self.node + ' - ' + self.generator + " - " + self.config

    def submit(self):
        # Find suitable node
        result = self.jenkins.callServerUrl('/label/build_pool/api/python')
        nodeApi = eval(result.read())
        nodeList = nodeApi['nodes']
        for node in nodeList:
            nodeName = node['nodeName']
            if self.target in nodeName:
                self.node = nodeName
                break
        assert(self.node != None)
        params = { "parameter": [ 
            { "name" : "build_node", "value" : self.node },
            { "name" : "config",     "value" : self.config },
            { "name" : "git_commit", "value" : self.jenkins.gitCommit },
            { "name" : "generator",  "value" : self.generator }
        ]}
        data = urllib.urlencode([
            ("json", json.dumps(params)),
            ("Submit", "Build")
        ])
        print "Starting " + self.jobString() + "..."
        result = self.jenkins.callServerUrl(self.url + '/build?token=hydrant', data)

    def findBuildUrl(self):
        jobApi = self.jenkins.callServerUrl(self.url + "/api/python")
        jobPage = ast.literal_eval(jobApi.read())
        maxJob = jobPage["nextBuildNumber"]
        currBuildApi = None        
        for buildNumber in range(maxJob - 1, maxJob - 20, -1):
            try:
                currBuildApi = self.jenkins.callServerUrl(self.url + '/' + str(buildNumber) + '/api/python')
            except:
                continue
            buildPage = ast.literal_eval(currBuildApi.read())
            # Found a valid build...check parameters
            if buildStartTime > buildPage["timestamp"]:
                break # Don't read results from old builds
            if self.name not in buildPage["fullDisplayName"]:
                continue
            if self.node != buildPage["builtOn"]:
                continue
            config = None
            gitCommit = None
            generator = None
            actions = buildPage["actions"]
            for action in actions:
                parameters = action.get("parameters")
                if parameters != None:
                    break
            assert(parameters != None)
            for parameter in parameters:
                if parameter["name"] == "config":
                    config = parameter["value"]
                elif parameter["name"] == "git_commit":
                    gitCommit = parameter["value"]
                elif parameter["name"] == "generator":
                    generator = parameter["value"]
            if gitCommit != self.jenkins.gitCommit:
                continue
            if config != self.config:
                continue
            if generator != self.generator:
                continue
            self.buildUrl = self.url + '/' + str(buildNumber)
            return True
        return False

    def checkBuildStatus(self):
        if self.result != None:
            print self.jobString() + " already finished"
            return True
        if self.buildUrl == None:
            if self.findBuildUrl() == False:
                print self.jobString() + " not yet started"
                return False
        buildApi = self.jenkins.callServerUrl(self.buildUrl + '/api/python')
        buildPage = ast.literal_eval(buildApi.read())
        assert(self.name in buildPage["fullDisplayName"])
        assert(self.node == buildPage["builtOn"])
        result = buildPage["result"]
        if  result == "SUCCESS" or result == "FAILURE" or result == "UNSTABLE":
            # Find gtest artifacts
            artifacts = buildPage["artifacts"]
            for artifact in artifacts:
                artifactPath = artifact["relativePath"]
                fullArtifactPath = self.buildUrl +  '/artifact/' + artifactPath
                artifactName, artifactExtension = os.path.splitext(artifact["fileName"])
                fullArtifactDest = artifactName + "_" + self.node +  "_" + self.generator + "_" + self.config + artifactExtension
                print "Downloading " + self.jenkins.jenkinsUrl + fullArtifactPath + " to " + fullArtifactDest
                artifact = urllib.urlretrieve(self.jenkins.jenkinsUrl + fullArtifactPath, fullArtifactDest)
            print self.jobString() + " finished with " + result
            self.result = result
            self.duration = buildPage["duration"] / 1000.0
            return True
        print "Waiting for " + self.jobString()
        return False

    def printSummaryLine(self, file):
        jobColors = {
            "SUCCESS"  : "#00ff00",
            "FAILURE"  : "#ff0000",
            "UNSTABLE" : "#ffff00",
            }
        color = jobColors[self.result]
        file.write('<tr>\n')
        file.write('<td value="' + self.target + '" bgcolor="' + color + '" fontcolor="black" fontattribute="normal" href="' + self.jenkins.jenkinsUrl + self.buildUrl + '" align="left" width="200"/>\n')
        file.write('<td value="' + self.config + '" bgcolor="' + color + '" fontcolor="black" fontattribute="normal" align="left" width="200"/>\n')
        file.write('<td value="' + self.generator + '" bgcolor="' + color + '" fontcolor="black" fontattribute="normal" align="left" width="200"/>\n')
        file.write('<td value="' + "{0:.1f}".format(self.duration) + '" bgcolor="' + color + '" fontcolor="black" fontattribute="normal" align="left" width="200"/>\n')
        file.write('</tr>\n')

class Jenkins:
    def __init__(self, url, jobUrl):
        self.jenkinsUrl = url
        username = os.environ["JENKINS_USER"]
        password = os.environ["JENKINS_PASS"]
        self.base64AuthString = base64.encodestring('%s:%s' % (username, password)).replace('\n', '')
        self.gitCommit = os.environ["GIT_COMMIT"]
        self.buildName = self.gitCommit[:8]
        self.jobUrl = jobUrl
        self.buildResult = 0
        self.jobs = []
        self.finishedJobs = []

    def callServerUrl(self, url, data=None):
        request = urllib2.Request(self.jenkinsUrl + url, data)
        request.add_header("Authorization", "Basic %s" % self.base64AuthString)   
        result = urllib2.urlopen(request)
        return result

    def buildJobList(self):
        generatorList = {
            'win' : [ 'Visual Studio 11 Win64', 'Visual Studio 12 Win64' ],
            'mac' : [ 'Unix Makefiles', 'Xcode' ],
            'lin' : [ 'Unix Makefiles' ]
        }
        targetList = { "win", "mac", "lin" }
        configList = { "Release", "Debug" }
        jobList = []
        for target in targetList:
            for generator in generatorList[target]:
                for config in configList:
                    job = Job(self, self.buildName, config, target, generator, self.jobUrl)
                    jobList.append(job)
        return jobList

    def submitJobs(self):
        self.jobs = self.buildJobList()
        # Loop through jobs, find node for each job
        for job in self.jobs:
            job.submit()

    def waitForJobs(self):
        print "Waiting for builds to start..."
        jobApi = jenkins.callServerUrl(self.jobUrl + "/api/python")
        jobPage = ast.literal_eval(jobApi.read())
        self.buildResult = 0
        # Wait for all builds to finish
        while len(self.jobs) > 0:
            for job in self.jobs:
                if job.checkBuildStatus() == True:
                    if job.result != "SUCCESS":
                        self.buildResult += 1
                    self.finishedJobs.append(job)
                    self.jobs.remove(job)
                    break
                time.sleep(1)

    def printSummary(self):
        outf = open("summary.xml", "w")
        outf.write('<section name="Build Summary" fontcolor="#ffffff">\n')
        outf.write('<table sorttable="yes">\n')
        outf.write('<tr>\n')
        outf.write('<td value="Platform" bgcolor="white" fontcolor="black" fontattribute="bold" href="" align="center" width="200"/>\n')
        outf.write('<td value="Config" bgcolor="white" fontcolor="black" fontattribute="bold" href="" align="center" width="200"/>\n')
        outf.write('<td value="Build System" bgcolor="white" fontcolor="black" fontattribute="bold" href="" align="center" width="200"/>\n')
        outf.write('<td value="Duration (seconds)" bgcolor="white" fontcolor="black" fontattribute="bold" href="" align="center" width="200"/>\n')
        outf.write('</tr>\n')
        for job in self.finishedJobs:
            job.printSummaryLine(outf)
        outf.write('</table>\n')
        outf.write('</section>\n')
        outf.close()

if args.jenkins:
    jenkins = Jenkins(args.jenkins, '/job/Math_component')
    jenkins.submitJobs()
    jenkins.waitForJobs()
    jenkins.printSummary()
    sys.exit(jenkins.buildResult)

#
# CMake
#
class CMakeBuilder:
    def __init__(self, path, generator, config):
        self.path = path
        self.generator = generator
        self.config = config

    def run(self):
        cmakeCmd = ["cmake", '-G', self.generator, '-DCMAKE_BUILD_TYPE=' + self.config, self.path]
        retCode = subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=sh)

#
# Visual Studio Builder
#
class VisualStudioBuilder:
    def __init__(self, solution, generator):
        self.solution = solution
        self.generator = generator

    def build(self):
        from _winreg import *
        if '12' in generator:
            aKey = OpenKey(HKEY_LOCAL_MACHINE, r"SOFTWARE\\Microsoft\\MSBuild\\ToolsVersions\\12.0")
        else:
            aKey = OpenKey(HKEY_LOCAL_MACHINE, r"SOFTWARE\\Microsoft\\MSBuild\\ToolsVersions\\4.0")
        value  = QueryValueEx(aKey, "MSBuildToolsPath")
        buildCmd = [value[0] + "msbuild", "/p:Configuration=" + args.config, "/m", self.solution]
        return subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)

#
# Makefile
# 
class MakefileBuilder:
    def build(self):
        buildCmd = ["make", "-j"]
        return subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)
    
#
# Xcode Builder
#
class XcodeBuilder:
    def build(self):
        buildCmd = ["xcodebuild", '-configuration', args.config]
        return subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)

# Run CMake
print "\n===\nStarting CMake\n===\n"

if platform.system() == "Darwin" or platform.system() == "Linux":
    generator = "Unix Makefiles"
    sh = False 
elif platform.system() == "Windows":
    generator = "Visual Studio 11 Win64"
    sh = True
if args.generator != None:
    generator = args.generator

cmakeBuilder = CMakeBuilder('..', generator, args.config)
cmakeBuilder.run()

if not args.build:
    sys.exit()
print "\n===\nStarting Build\n===\n"

# Build
if "Visual Studio" in generator:
    vsBuilder = VisualStudioBuilder("Math.sln", generator)
    retCode = vsBuilder.build()
elif "Makefile" in generator:
    makefileBuilder = MakefileBuilder()
    retCode = makefileBuilder.build()
elif "Xcode" in generator:
    xcodeBuilder = XcodeBuilder()
    retCode = xcodeBuilder.build()

sys.exit(retCode)
