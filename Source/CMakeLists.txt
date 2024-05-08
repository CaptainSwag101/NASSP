cmake_minimum_required(VERSION 3.19)

# Set the project name
project(NASSP VERSION 8.0.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add /permissive if using C++20 or higher
#add_compile_options(/permissive)

# Group projects in VS
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check if the user has specified a non-default Orbiter installation location.
# If not, use the default and alert the user.
if (NOT DEFINED ${ORBITER_INSTALL_DIR})
    set(ORBITER_INSTALL_DIR ${CMAKE_SOURCE_DIR}/..)
    message("ORBITER_INSTALL_DIR not set, defaulting to: " ${ORBITER_INSTALL_DIR})
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64-bit build?
    set(BUILD64 1)
    set(ARCH "x64")
    set(PLATFORM_STRING "x64")
else()
    set(BUILD64 0)
    set(ARCH "x86")
    set(PLATFORM_STRING "Win32")
endif()

if (NOT ${CMAKE_GENERATOR} STREQUAL "Ninja")
    add_compile_options(/MP)
endif()

if(MSVC)
    # Disable built-in macro for min/max, and flag pointer truncation as an error
    add_compile_options(/we4311 /DNOMINMAX)
    add_link_options("/NODEFAULTLIB:\"LIBCMTD\"")
endif()

# Set project-wide variables
set(ORBITERSDK_DIR ${CMAKE_SOURCE_DIR}/../Orbitersdk)
set(NASSP_SOURCE_ROOT ${CMAKE_SOURCE_DIR}/Source)

# Sub-projects are what actually build all our vessels, MFDs, etc.
include(Projects/PanelSDK.cmake)
include(Projects/LEM.cmake)
include(Projects/Saturn5.cmake)