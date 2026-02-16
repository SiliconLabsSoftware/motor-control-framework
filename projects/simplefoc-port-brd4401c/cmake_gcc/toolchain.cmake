set(CMAKE_SYSTEM_NAME                   Generic)
set(CMAKE_SYSTEM_PROCESSOR              arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE       STATIC_LIBRARY)

if (WIN32)
  set(EXE_SUFFIX ".exe")
  cmake_path(SET USER_DIR "$ENV{USERPROFILE}" NORMALIZE)
else()
  set(EXE_SUFFIX "")
  cmake_path(SET USER_DIR "$ENV{HOME}" NORMALIZE)
endif ()

# Use the SLT tooling to find the install paths so the tools are
# found across multiple machines. This requires placing the 'slt'
# tool on PATH
execute_process(COMMAND slt where gcc-arm-none-eabi
                OUTPUT_VARIABLE "ARM_GCC_SLT_PATH"
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND slt where commander
                OUTPUT_VARIABLE "COMMANDER_SLT_PATH"
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND slt where ninja
                OUTPUT_VARIABLE "NINJA_SLT_PATH"
                OUTPUT_STRIP_TRAILING_WHITESPACE)


if (DEFINED ENV{ARM_GCC_DIR})
  set(TOOLCHAIN_DIR "$ENV{ARM_GCC_DIR}/bin/")
elseif (ARM_GCC_SLT_PATH)
  set(TOOLCHAIN_DIR "${ARM_GCC_SLT_PATH}/bin/")
elseif (WIN32)
  set(TOOLCHAIN_DIR "/bin/")
elseif (APPLE)
  set(TOOLCHAIN_DIR "${USER_DIR}/.silabs/slt/installs/conan/p/gcc-af360b79bab9e3/p/bin/")
else()
  set(TOOLCHAIN_DIR "/bin/")
endif ()

if (DEFINED ENV{POST_BUILD_EXE})
  set(POST_BUILD_EXE "$ENV{POST_BUILD_EXE}")
elseif (COMMANDER_SLT_PATH)
  if (WIN32)
    set(POST_BUILD_EXE "${COMMANDER_SLT_PATH}/commander.exe")
  elseif (APPLE)
    set(POST_BUILD_EXE "${COMMANDER_SLT_PATH}/Contents/MacOS/commander")
  else()
    set(POST_BUILD_EXE "${COMMANDER_SLT_PATH}/commander")
  endif ()
elseif (WIN32)
  set(POST_BUILD_EXE "")
elseif (APPLE)
  set(POST_BUILD_EXE "${USER_DIR}/.silabs/slt/installs/archive/Commander.app/Contents/MacOS/commander")
else()
  set(POST_BUILD_EXE "")
endif ()

if (DEFINED ENV{NINJA_EXE_PATH})
  set(NINJA_RUNTIME_PATH "$ENV{NINJA_EXE_PATH}")
elseif (NINJA_SLT_PATH)
  set(NINJA_RUNTIME_PATH "${NINJA_SLT_PATH}/ninja")
elseif (WIN32)
  set(NINJA_RUNTIME_PATH "")
elseif (APPLE)
  set(NINJA_RUNTIME_PATH "${USER_DIR}/.silabs/slt/installs/conan/p/ninja48deaaf744f20/p/ninja")
else()
  set(NINJA_RUNTIME_PATH "")
endif ()
# Use default lookup mechanisms if the OS specific values are not set above
if (NINJA_RUNTIME_PATH)
	set(CMAKE_MAKE_PROGRAM ${NINJA_RUNTIME_PATH} CACHE FILEPATH "" FORCE)
endif ()

set(TARGET_TRIPLET "arm-none-eabi-")
set(CMAKE_C_COMPILER    ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcc${EXE_SUFFIX})
set(CMAKE_CXX_COMPILER  ${TOOLCHAIN_DIR}${TARGET_TRIPLET}g++${EXE_SUFFIX})
set(CMAKE_ASM_COMPILER  ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcc${EXE_SUFFIX})
set(CMAKE_LINKER        ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcc${EXE_SUFFIX})
set(CMAKE_AR            ${TOOLCHAIN_DIR}${TARGET_TRIPLET}ar${EXE_SUFFIX})
set(CMAKE_SIZE_UTIL     ${TOOLCHAIN_DIR}${TARGET_TRIPLET}size${EXE_SUFFIX})
set(CMAKE_STRIP         ${TOOLCHAIN_DIR}${TARGET_TRIPLET}strip${EXE_SUFFIX})
set(CMAKE_OBJCOPY       ${TOOLCHAIN_DIR}${TARGET_TRIPLET}objcopy${EXE_SUFFIX})
set(CMAKE_OBJDUMP       ${TOOLCHAIN_DIR}${TARGET_TRIPLET}objdump${EXE_SUFFIX})
set(CMAKE_NM_UTIL       ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcc-nm${EXE_SUFFIX})
set(CMAKE_RANLIB        ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcc-ranlib${EXE_SUFFIX})
set(CMAKE_GCOV          ${TOOLCHAIN_DIR}${TARGET_TRIPLET}gcov${EXE_SUFFIX})

set(OBJCOPY_SREC_CMD    "-O;srec")
set(OBJCOPY_IHEX_CMD    "-O;ihex")
set(OBJCOPY_BIN_CMD     "-O;binary")

set(CMAKE_C_STANDARD_REQUIRED   OFF)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS          OFF)

set(CMAKE_C_FLAGS_RELEASE               "" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE             "" CACHE STRING "")

# Response file support
SET(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS   1)
SET(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
SET(CMAKE_C_RESPONSE_FILE_LINK_FLAG         "@")
SET(CMAKE_CXX_RESPONSE_FILE_LINK_FLAG       "@")
SET(CMAKE_NINJA_FORCE_RESPONSE_FILE         1 CACHE INTERNAL "")


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)

set(CMAKE_EXECUTABLE_SUFFIX     .out)
set(CMAKE_EXECUTABLE_SUFFIX_C   .out)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .out)
