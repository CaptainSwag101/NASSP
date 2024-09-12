# Set the project name
project(LM_New)

set(INCLUDE_DIRS
    ${NASSP_SOURCE_ROOT}/src_aux
    ${NASSP_SOURCE_ROOT}/src_csm
    ${NASSP_SOURCE_ROOT}/src_launch
    ${NASSP_SOURCE_ROOT}/src_lm
    ${NASSP_SOURCE_ROOT}/src_lm/yaAGS
    ${NASSP_SOURCE_ROOT}/src_mfd
    ${NASSP_SOURCE_ROOT}/src_moon
    ${NASSP_SOURCE_ROOT}/src_saturn
    ${NASSP_SOURCE_ROOT}/src_sys
    ${NASSP_SOURCE_ROOT}/src_sys/SystemSDK/Internals
    ${NASSP_SOURCE_ROOT}/src_sys/yaAGC
    ${ORBITERSDK_DIR}/include
    ${ORBITERSDK_DIR}/XRSound
)
set(SOURCES
    ${NASSP_SOURCE_ROOT}/src_lm_new/LM.cpp
    ${NASSP_SOURCE_ROOT}/src_lm_new/LM_CWEA.cpp
)

link_directories(${ORBITERSDK_DIR}/lib)
link_directories(${ORBITERSDK_DIR}/XRSound)
link_directories(${CMAKE_BINARY_DIR}/Projects/SystemSDK)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    GLU32
    dxguid
    dinput8
    OpenGL32
    User32
    WinMM
    WS2_32
    Orbiter
    Orbitersdk
    SystemSDK
    XRSound
)