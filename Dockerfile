### This is a template Dockerfile for the CI/CD pipeline

FROM ubuntu:24.04

ENV TZ=Europe/Budapest
ENV DEBIAN_FRONTEND=noninteractive

ARG ARCH=x86_64
ENV ARCH=$ARCH

ARG INSTALL_SONARQUBE=NO

# Define the URLs for the tools
# These can be overridden at build time using --build-arg flags
# Example: docker build --build-arg ARM_GCC_URL="https://example.com/custom-gcc.tar.xz" .
##### TODO #####
# Check and update version numbers if necessary
ARG ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/arm-gnu-toolchain-12.2.rel1-${ARCH}-arm-none-eabi.tar.xz"
ARG SIMPLICITY_COMMANDER_URL="https://www.silabs.com/documents/login/software/SimplicityCommander-Linux.zip"
ARG SONAR_SCANNER_URL="https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-6.1.0.4477-linux-x64.zip"
ARG SONAR_BUILD_WRAPPER="https://sonarqube.silabs.net/static/cpp/build-wrapper-linux-x86.zip"

# Install all necessary packages in one layer
RUN apt-get update \
    && apt-get install --no-install-recommends -y \
    build-essential \
    cmake \
    curl \
    git \
    jq \
    libglib2.0-0 \
    libpcre2-dev \
    make \
    ninja-build \
    unzip \
    wget \
    zip \
    $([ "$INSTALL_SONARQUBE" = "YES" ] && echo "openjdk-17-jdk") \
    && rm -rf /var/lib/apt/lists/*

# Install latest CMake
ADD https://apt.kitware.com/kitware-archive.sh /tmp/kitware-archive.sh
RUN bash /tmp/kitware-archive.sh \
    && rm /tmp/kitware-archive.sh

# Install GNU Arm Embedded Toolchain and Simplicity Commander
# REGEXP: $(find . -maxdepth 1 -type d -name 'arm-gnu-toolchain-*' | head -n 1)
# This will find the first folder in the current directory that starts with 'arm-gnu-toolchain-'
# This is necessary because the downloaded archive contains a folder with a version number in the name
# and we don't know what that version number is.
WORKDIR /tmp
ADD "$ARM_GCC_URL" arm-gnu-toolchain.tar.xz
ADD "$SIMPLICITY_COMMANDER_URL" SimplicityCommander-Linux.zip

RUN tar -xf arm-gnu-toolchain.tar.xz \
    && TOOLCHAIN_FOLDER=$(find . -maxdepth 1 -type d -name 'arm-gnu-toolchain-*' | head -n 1) \
    && mv "$TOOLCHAIN_FOLDER" /opt/gcc-arm-none-eabi \
    && rm arm-gnu-toolchain.tar.xz -rf \
    && unzip SimplicityCommander-Linux.zip \
    && tar -xf SimplicityCommander-Linux/Commander-cli_linux_${ARCH}_*.tar.bz \
    && mv commander-cli /opt/commander-cli \
    && rm -rf SimplicityCommander-Linux.zip SimplicityCommander-Linux

# Download and install SonarQube scanner and build-wrapper
# REGEX: $(find /opt -maxdepth 1 -type d -name 'sonar-scanner-*' | head -n 1)
# This will find the first folder in /opt that starts with 'sonar-scanner-'
# This is necessary because the downloaded archive contains a folder with a version number in the name
# and we don't know what that version number is.
RUN if [ "$INSTALL_SONARQUBE" = "YES" ]; then \
    curl --proto '=https' -fsSL "$SONAR_SCANNER_URL" -o /tmp/sonar-scanner-cli.zip \
    && unzip /tmp/sonar-scanner-cli.zip -d /opt \
    && SCANNER_FOLDER=$(find /opt -maxdepth 1 -type d -name 'sonar-scanner-*' | head -n 1) \
    && ln -s ${SCANNER_FOLDER}/bin/sonar-scanner /usr/local/bin/sonar-scanner \
    && rm /tmp/sonar-scanner-cli.zip \
    && curl --proto '=https' -fsSL "$SONAR_BUILD_WRAPPER" -o /tmp/build-wrapper-linux-x86.zip \
    && unzip /tmp/build-wrapper-linux-x86.zip -d /opt \
    && ln -s /opt/build-wrapper-linux-x86/build-wrapper-linux-x86 /usr/local/bin/build-wrapper \
    && rm /tmp/build-wrapper-linux-x86.zip \
    && mkdir -p /etc/profile.d \
    && echo 'export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64' >> /etc/profile.d/sonarqube.sh \
    && echo 'export PATH="${PATH}:${JAVA_HOME}/bin:/opt/build-wrapper-linux-x86/"' >> /etc/profile.d/sonarqube.sh; \
    fi

ENV POST_BUILD_EXE="/opt/commander-cli/commander-cli"
ENV ARM_GCC_DIR="/opt/gcc-arm-none-eabi"
ENV NINJA_EXE_PATH=""
ENV PATH="${PATH}:/opt/gcc-arm-none-eabi/bin"
ENV PATH="${PATH}:/usr/local/bin"

WORKDIR /home
