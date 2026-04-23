FROM ubuntu:24.04

ENV TZ=Europe/Budapest
ENV DEBIAN_FRONTEND=noninteractive

ARG ARCH=x86_64
ENV ARCH=$ARCH

# Define the URLs for the tools
# Check and update version numbers if necessary
ARG ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/arm-gnu-toolchain-12.2.rel1-${ARCH}-arm-none-eabi.tar.xz"
ARG SIMPLICITY_COMMANDER_URL="https://www.silabs.com/documents/login/software/SimplicityCommander-Linux.zip"

#add 3rd party repositories
RUN apt-get update  \
    && apt-get install --no-install-recommends -y \
    apt-utils \
    gpg \
    gpg-agent \
    ca-certificates \
    software-properties-common \
    && add-apt-repository ppa:openjdk-r/ppa

#Install necessary packages
RUN apt-get install --no-install-recommends -y \
    build-essential \
    cmake \
    curl \
    git \
    libpcre2-dev \
    make \
    ninja-build \
    openjdk-17-jdk \
    unzip \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*

# Install latest CMake
ADD https://apt.kitware.com/kitware-archive.sh /tmp/kitware-archive.sh
RUN bash /tmp/kitware-archive.sh \
    && rm /tmp/kitware-archive.sh

# Install GNU Arm Embedded Toolchain
# REGEXP: $(find . -maxdepth 1 -type d -name 'arm-gnu-toolchain-*' | head -n 1)
# This will find the first folder in the current directory that starts with 'arm-gnu-toolchain-'
# This is necessary because the downloaded archive contains a folder with a version number in the name
# and we don't know what that version number is.
WORKDIR /tmp
ADD "$ARM_GCC_URL" arm-gnu-toolchain.tar.xz

RUN tar -xf arm-gnu-toolchain.tar.xz \
    && TOOLCHAIN_FOLDER=$(find . -maxdepth 1 -type d -name 'arm-gnu-toolchain-*' | head -n 1) \
    && mv "$TOOLCHAIN_FOLDER" /opt/gcc-arm-none-eabi \
    && rm arm-gnu-toolchain.tar.xz -rf

# Install Simplicity Commander
ADD "$SIMPLICITY_COMMANDER_URL" SimplicityCommander-Linux.zip
RUN unzip SimplicityCommander-Linux.zip \
    && tar -xf SimplicityCommander-Linux/Commander-cli_linux_${ARCH}_*.tar.bz \
    && mv commander-cli /opt/commander-cli \
    && rm -rf SimplicityCommander-Linux.zip SimplicityCommander-Linux

ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
ENV POST_BUILD_EXE="/opt/commander-cli/commander-cli"
ENV ARM_GCC_DIR="/opt/gcc-arm-none-eabi"
ENV PATH="${PATH}:${JAVA_HOME}/bin"
ENV PATH="${PATH}:/opt/gcc-arm-none-eabi/bin"
ENV PATH="${PATH}:/usr/local/bin"

WORKDIR /home
