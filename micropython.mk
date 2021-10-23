COLLARTX_MOD_DIR := $(USERMOD_DIR)

# Add our source files to the respective variables.
SRC_USERMOD += $(COLLARTX)/collarmodule.c
SRC_USERMOD_CXX += $(COLLARTX)/collartx.cpp

# Add our module directory to the include path.
CFLAGS_USERMOD += -I$(COLLARTX)
CXXFLAGS_USERMOD += -I$(COLLARTX)

# We use C++ features so have to link against the standard library.
LDFLAGS_USERMOD += -lstdc++
