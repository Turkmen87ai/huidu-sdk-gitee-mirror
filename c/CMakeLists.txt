cmake_minimum_required(VERSION 3.10)
project(ProjectSDK LANGUAGES C)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加SDK子目录
add_subdirectory(sdk)

# 添加演示程序
add_subdirectory(demos/demo0_based)
add_subdirectory(demos/demo1_deviceInfo)
add_subdirectory(demos/demo2_task)
add_subdirectory(demos/demo3_baseProgram)
add_subdirectory(demos/demo4_multiProgram)
add_subdirectory(demos/demo5_dynamicContent)
add_subdirectory(demos/demo6_multiArea)

# 安装配置
install(DIRECTORY ${CMAKE_SOURCE_DIR}/sdk/ DESTINATION include/sdk
    FILES_MATCHING 
    PATTERN "*.h"
    PATTERN "thirdParty" EXCLUDE
    PATTERN "demos" EXCLUDE
)

install(DIRECTORY 
    ${CMAKE_SOURCE_DIR}/sdk/thirdParty/curl
    DESTINATION include/sdk/thirdParty
)

install(FILES 
    ${CMAKE_SOURCE_DIR}/sdk/thirdParty/json/cJSON.h
    DESTINATION include/sdk/thirdParty/json
)