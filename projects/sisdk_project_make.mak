.SUFFIXES:				# ignore builtin rules
.PHONY: clean configure build clean_build

ifndef CMAKELIST_DIR
$(error CMAKELIST_DIR is not set)
endif
BUILD_DIR := $(CMAKELIST_DIR)/build

clean_build: clean configure build
clean:
	@echo 'Cleaning build directory!'
	cmake -E remove_directory $(BUILD_DIR)
configure:
	@echo 'CMAKE configure...!'
	cmake $(CMAKELIST_DIR) --preset project
build:
	@echo 'CMAKE build...!'
	cmake --build $(BUILD_DIR)