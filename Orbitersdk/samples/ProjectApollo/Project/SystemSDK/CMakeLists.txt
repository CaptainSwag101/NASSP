project(SystemSDK)

set(INCLUDE_DIRS
    ${NASSP_SOURCE_ROOT}/src_sys
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals
    ${ORBITERSDK_DIR}/include
)
set(SOURCES
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/SystemSDK.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/BUILD.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Matrix.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Vectors.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/VSMGMT.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals/esysparse.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals/esystems.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals/hsysparse.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals/hsystems.cpp
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals/thermal.cpp
)

link_directories(${ORBITERSDK_DIR}/lib)
link_directories(${ORBITERSDK_DIR}/XRSound)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Orbiter
    Orbitersdk
    XRSound
)