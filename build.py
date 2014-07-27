#!/usr/bin/python
import sys
import os
import subprocess
import platform
import argparse

#
# Parse command line
#
parser = argparse.ArgumentParser()
parser.add_argument("-b", "--build", help="If you want the source to be built", action="store_true")
args = parser.parse_args()

if not os.path.isdir("_build"):
    os.mkdir("_build")

print "\n===\nStarting CMake\n===\n"
sys.stdout.flush()

os.chdir("_build")

if platform.system() == "Darwin" or platform.system() == "Linux":
    generator = "Unix Makefiles"
    sh = False 
elif platform.system() == "Windows":
    generator = "Visual Studio 11 Win64"
    sh = True

# Run CMake
cmakeCmd = ["cmake", '-G', generator, ".."]
retCode = subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=sh)

if not args.build:
    sys.exit()
print "\n===\nStarting Build\n===\n"
sys.stdout.flush()


# Build
if platform.system() == "Windows":
    from _winreg import *
    aKey = OpenKey(HKEY_LOCAL_MACHINE, r"SOFTWARE\\Microsoft\\MSBuild\\ToolsVersions\\4.0")
    value  = QueryValueEx(aKey, "MSBuildToolsPath")
    buildCmd = [value[0] + "msbuild", "/p:Configuration=Debug", "/m", "Math.sln"]
    retCode = subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)
    buildCmd = [value[0] + "msbuild", "/p:Configuration=Release", "/m", "Math.sln"]
    retCode = subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)

elif platform.system() == "Darwin":
    buildCmd = ["make", "-j"]
    retCode = subprocess.check_call(buildCmd, stderr=subprocess.STDOUT, shell=sh)


