#
# Output files
#
LIBRARY = ./libunittest.a
TARGET = ./test_unit_test

#
# Library sources
#
SRCS = src/unit_test.c

#
# Test sources
#
TEST_SRCS = test/main.c \
			test/unit_test_test.c \
			test/unit_test_cpp_test.cpp

#
# Compilation control
#
INCLUDES 	+= 	-Isrc
DEFINES		+=

C_STD	= -std=c89
CXX_STD	= -std=c++98
WARNINGS	+=	 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
				 -Wwrite-strings  -Wredundant-decls -Winline -Wno-long-long \
				 -Wuninitialized -Wconversion -Werror
CPPFLAGS += -MMD -MP $(DEFINES) $(INCLUDES) $(WARNINGS) -g
CFLAGS += $(CPPFLAGS) -Wmissing-declarations -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes $(C_STD)
CXXFLAGS += $(CPPFLAGS) $(CXX_STD)

#############################################
OBJECTS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS)))
TEST_OBJECTS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(TEST_SRCS)))
############################################

ifndef V
	SILENT = @
endif

_DEPS := $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: clean test

all: $(TARGET) test

lib $(LIBRARY) : $(OBJECTS)
	@echo "Archiving $@..."
	$(SILENT) ar rcs $(LIBRARY) $(OBJECTS)

$(TARGET) : $(LIBRARY) $(TEST_OBJECTS)
	@echo "Linking $@..."
	$(SILENT) $(CXX) $(LDFLAGS) $(TEST_OBJECTS) $(LIBRARY) -o $(TARGET)

test: $(TARGET)
	@echo "Running tests..."
	$(SILENT) $(TARGET) -t

%.o : %.c
	@echo "Compiling $<..."
	$(SILENT) $(CC) $(CFLAGS) -c $< -o $@

%.o : %.cpp
	@echo "Compiling $<..."
	$(SILENT) $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	$(SILENT) $(RM) -f -r $(OBJECTS) $(TEST_OBJECTS) $(_DEPS)
	$(SILENT) $(RM) $(LIBRARY) $(TARGET)

-include $(_DEPS)

