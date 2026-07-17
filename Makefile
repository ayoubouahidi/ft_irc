# IRC Server Makefile

CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -g
LDFLAGS := -lpthread

# Output binary name
TARGET := irc_server

# Directories
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/objects
DEP_DIR := $(BUILD_DIR)/deps

# Source files
SOURCES := main.cpp \
	Networking/server.cpp \
	Networking/server_init.cpp \
	Parsing/Channel.cpp \
	Parsing/Client.cpp \
	Commands/CommandHandler.cpp \
	Commands/Authentication/Nick.cpp \
	Commands/Authentication/Pass.cpp \
	Commands/Authentication/Register.cpp \
	Commands/Authentication/User.cpp \
	Commands/ChannelMessages/Join.cpp \
	Commands/ChannelMessages/Privmsg.cpp \
	Commands/OperatorCommands/Invite.cpp \
	Commands/OperatorCommands/Kick.cpp \
	Commands/OperatorCommands/Mode.cpp \
	Commands/OperatorCommands/Topic.cpp

# Object files
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Dependency files
DEPENDS := $(SOURCES:%.cpp=$(DEP_DIR)/%.d)

# Include paths
INCLUDES := -I. -INetworking -IParsing -ICommands

# Default target
all: $(TARGET)

# Link target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ Build complete: $(TARGET)"

# Compile object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@
	@echo "✓ Compiled: $<"

# Include dependency files
-include $(DEPENDS)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	@echo "✓ Clean complete"

# Deep clean (removes object files in root)
distclean: clean
	rm -f **/*.o
	@echo "✓ Distclean complete"

# Rebuild
rebuild: clean all

# Help
help:
	@echo "IRC Server Makefile"
	@echo "==================="
	@echo "Targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build directory and binary"
	@echo "  distclean - Remove all generated files"
	@echo "  rebuild   - Clean and build"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Compilation flags: $(CXXFLAGS)"

.PHONY: all clean distclean rebuild help
