PROJECT       = $(shell basename `readlink -f .`)

MARILYN_LIB   = ../../Marilyn-EM1/3DOCTMgr/Library

CC            = /usr/bin/aarch64-linux-gnu-gcc
CXX           = /usr/bin/aarch64-linux-gnu-g++
LINK          = $(CXX)
DEFINES       = -pipe -mtune=cortex-a57.cortex-a53 -march=armv8-a -O2 -Wall -W -D_REENTRANT -fPIC
CFLAGS        = $(DEFINES)
CXXFLAGS      = $(DEFINES) -std=gnu++11
LFLAGS        = --sysroot=/home/ubuntu/nvidia/jetpack/64_TX2/Linux_for_Tegra/rootfs
INCPATH       = -I. -I$(MARILYN_LIB)/Common -I$(MARILYN_LIB)/defs -I/home/ubuntu/nvidia/jetpack/64_TX2/Linux_for_Tegra/rootfs/usr/include
LIBS          = -Wl,-rpath,/usr/lib -ldl -lrt -lpthread

DEL_FILE      = rm -f
MKDIR         = mkdir -p

SRCDIR        = .
SOURCES_C     = $(wildcard $(SRCDIR)/*.c)
SOURCES_CPP   = $(wildcard $(SRCDIR)/*.cpp)
SOURCES_CPP  += $(MARILYN_LIB)/Common/sharedmemory.cpp
OBJECTS_DIR   = ./obj
OBJECTS       = $(addprefix $(OBJECTS_DIR)/, $(notdir $(SOURCES_C:.c=.o) $(SOURCES_CPP:.cpp=.o)))
DEPENDS       = $(OBJECTS:.o=.d)
DESTDIR       = ./bin
TARGET        = $(DESTDIR)/$(PROJECT)

$(TARGET): $(OBJECTS)
	@$(MKDIR) $(DESTDIR)
	$(LINK) $(LFLAGS) -o $@ $^ $(LIBS)

$(OBJECTS_DIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCPATH) -o $@ -c $<

$(OBJECTS_DIR)/%.o: $(SRCDIR)/%.cpp
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ -c $<

$(OBJECTS_DIR)/%.o: $(MARILYN_LIB)/Common/%.cpp
	@$(MKDIR) $(OBJECTS_DIR)
	@$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ -c $<

.PHONY: all
all: clean $(TARGET)

.PHONY: clean
clean:
	$(DEL_FILE) $(OBJECTS) $(DEPENDS) $(TARGET)

-include $(DEPENDS)
