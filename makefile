#
# Output files
#
TARGET = ./test_math

#
# Test sources
#
TEST_SRCS = test/main.c \
			test/math_test.cpp \
			test/math_test_c.c

#
# Compilation control
#
INCLUDES 	+= 	-Isrc -Iexternal/unit_test/src -Iexternal
DEFINES		+=
LIBS		+= -Lexternal/unit_test -lunittest

C_STD	= -std=c89
CXX_STD	= -std=c++98
WARNINGS	+=	 -Wall -Wextra -pedantic -Wpointer-arith \
				 -Wwrite-strings  -Wredundant-decls -Winline -Wno-long-long \
				 -Wuninitialized -Wconversion -Werror
CPPFLAGS += -MMD -MP $(DEFINES) $(INCLUDES) $(WARNINGS) -g
CFLAGS += $(CPPFLAGS) -Wmissing-declarations -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes $(C_STD)
CXXFLAGS += $(CPPFLAGS) $(CXX_STD)
LDFLAGS += $(LIBS)

#############################################
OBJECTS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS)))
TEST_OBJECTS = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(TEST_SRCS)))
############################################

ifndef V
	SILENT = @
endif

_DEPS := $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: clean test external

all: external $(TARGET) test

external:
	$(MAKE) -C external/unit_test lib

$(TARGET) : $(TEST_OBJECTS) external
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
	$(SILENT) $(MAKE) -C external/unit_test $@
	$(SILENT) $(RM) -f -r $(OBJECTS) $(TEST_OBJECTS) $(_DEPS)
	$(SILENT) $(RM) $(LIBRARY) $(TARGET)

-include $(_DEPS)

