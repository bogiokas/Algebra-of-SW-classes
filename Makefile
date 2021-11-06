Executable = main
SRC_DIR = src
BUILD_DIR = build
LOG_DIR = log

## logging flags - uncomment if terminal gets too crowded
#makeLogDir = mkdir -p $(LOG_DIR)
#LOGGING = 2> $(LOG_DIR)/make_$(notdir $@).log
#LOGGING_RUN = > $(LOG_DIR)/run.log
#rmEmptyLogFiles = find . -type f -empty -delete

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

depFlags = -MMD -MP

CXX = g++
versionFlags = -std=c++17
warningFlags = -Wall -Wextra -Wshadow -Weffc++
allFlags = $(versionFlags) $(warningFlags) $(depFlags)

$(Executable): $(OBJS)
	$(makeLogDir)
	$(CXX) $(OBJS) $(allFlags) -o $@ $(LOGGING)
	$(rmEmptyLogFiles)
	./$@ $(LOGGING_RUN)
	$(rmEmptyLogFiles)
	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(makeLogDir)
	mkdir -p $(dir $@)
	$(CXX) $(allFlags) -c $< -o $@ $(LOGGING)
	$(rmEmptyLogFiles)

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(Executable)
