cmake_minimum_required(VERSION 3.10)
project(SDK LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 定义平台相关变量
if(WIN32)
    set(LIBCURL_LIB "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib/libcurl_debug.lib")
    set(EXTRA_LIBS ws2_32.lib crypt32.lib)
else()
    set(EXTRA_LIBS pthread)
    find_package(CURL REQUIRED)
endif()

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    ${CMAKE_CURRENT_SOURCE_DIR}/data/area
    ${CMAKE_CURRENT_SOURCE_DIR}/data/other
    ${CMAKE_CURRENT_SOURCE_DIR}/data/task
    ${CMAKE_CURRENT_SOURCE_DIR}/deviceTask
    ${CMAKE_CURRENT_SOURCE_DIR}/portfiles
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/json
)

# 收集所有源文件
file(GLOB SDK_SOURCES
    "*.c"
)

file(GLOB COMMON_SOURCES
    "common/*.c"
)

file(GLOB_RECURSE DATA_SOURCES
    "data/*.c"
)

file(GLOB DEVICE_TASK_SOURCES
    "deviceTask/*.c"
)

file(GLOB PORTFILES_SOURCES
    "portfiles/*.c"
)

set(JSON_SOURCES
    "thirdParty/json/cJSON.c"
)

# 添加静态库目标
add_library(sdk STATIC
    ${SDK_SOURCES}
    ${COMMON_SOURCES}
    ${DATA_SOURCES}
    ${DEVICE_TASK_SOURCES}
    ${PORTFILES_SOURCES}
    ${JSON_SOURCES}
)

# 链接库
if(WIN32)
    target_link_libraries(sdk PRIVATE ${LIBCURL_LIB} ${EXTRA_LIBS})
else()
    target_link_libraries(sdk PRIVATE ${CURL_LIBRARIES} ${EXTRA_LIBS})
endif()

# 编译器选项
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sdk PRIVATE -Wall -Wextra -Werror)
endif()

# 安装规则
install(TARGETS sdk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/sdk
    FILES_MATCHING 
    PATTERN "*.h"
    PATTERN "thirdParty" EXCLUDE
    PATTERN "demos" EXCLUDE
)

# 单独安装第三方头文件
install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/json/cJSON.h
    DESTINATION include/sdk/thirdParty/json
)

install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/
    DESTINATION include/sdk/thirdParty/
)