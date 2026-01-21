.SUFFIXES:				# ignore builtin rules
.PHONY: all clean simpleFOC-port-mg24 docker_image docker_build docker_run

TARGET ?= clean_build
TYPE ?= Debug #Release

COMPONENTS := simpleFOC-port-mg24
all: $(COMPONENTS)
$(COMPONENTS):
	@echo 'Building $@...!'
	make -C projects -f sisdk_project_make.mak $(TARGET) TYPE=$(TYPE) CMAKELIST_DIR=$@/cmake_gcc
clean:
	@echo 'Cleaning $(COMPONENTS)...!'
	@$(foreach component,$(COMPONENTS), \
			make -C projects -f sisdk_project_make.mak clean TYPE=$(TYPE) CMAKELIST_DIR=$(component)/cmake_gcc; \
	)

DOCKER_IMAGE_VERSION ?= latest
DOCKER_IMAGE_NAME ?= simplefoc-port-mg24-build-env:$(DOCKER_IMAGE_VERSION)
DOCKER_WORKSPACE ?= /home/peps
ifeq ($(OS),Windows_NT)
	DOCKER_ARCH ?= x86_64
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
        DOCKER_ARCH ?= x86_64
    else
        DOCKER_ARCH ?= aarch64
    endif
endif
DOCKER_RUN_COMMON_ARGS := --platform linux/$(DOCKER_ARCH) --rm -v $(CURDIR):$(DOCKER_WORKSPACE) -w $(DOCKER_WORKSPACE) $(DOCKER_IMAGE_NAME)

docker_image:
	@echo 'Building Docker Image...!'
	docker build $(CURDIR) -t $(DOCKER_IMAGE_NAME) --platform linux/$(DOCKER_ARCH) --build-arg ARCH=$(DOCKER_ARCH)
docker_build:
	@echo 'Building project with the Docker Image...!'
	docker run $(DOCKER_RUN_COMMON_ARGS) /bin/sh -c "make all"
docker_run:
	@echo 'Running project interactively with the Docker Image...!'
	docker run -it $(DOCKER_RUN_COMMON_ARGS)
