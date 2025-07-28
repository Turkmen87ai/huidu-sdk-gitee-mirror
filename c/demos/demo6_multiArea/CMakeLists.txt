cmake_minimum_required(VERSION 3.10)
project(demo6_multiArea LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(demo6_multiArea main.c)

# 包含路径 - 指向SDK和第三方库
target_include_directories(demo6_multiArea PRIVATE
    ../../sdk
    ../../sdk/common
    ../../sdk/data
	../../sdk/data/area
	../../sdk/data/other
	../../sdk/data/task
    ../../sdk/deviceTask
    ../../sdk/portfiles
    ../../sdk/thirdParty
    ../../sdk/thirdParty/json
)

# 链接SDK库
target_link_libraries(demo6_multiArea PRIVATE sdk)

# 设置输出目录
set_target_properties(demo6_multiArea PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 安装可执行文件
install(TARGETS demo6_multiArea
    RUNTIME DESTINATION bin
)

# 添加自定义运行目标
add_custom_target(run_demo6
    COMMAND demo6_multiArea
    DEPENDS demo6_multiArea
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "Running demo6_multiArea"
)