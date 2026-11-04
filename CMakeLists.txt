cmake_minimum_required(VERSION 3.20)
project(shop CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shop
    src/main.cpp
)

target_include_directories(shop PRIVATE third_party)

if (WIN32)
    # 必须作用在目标上；add_compile_options 在这种写法下不生效
    target_compile_options(shop PRIVATE /utf-8)
    set(MYSQL_ROOT "C:/Program Files/MySQL/MySQL Server 8.0")
    target_include_directories(shop PRIVATE ${MYSQL_ROOT}/include)
    target_link_directories(shop PRIVATE ${MYSQL_ROOT}/lib)
    target_link_libraries(shop PRIVATE libmysql ws2_32)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(MYSQL REQUIRED mysqlclient)
    target_include_directories(shop PRIVATE ${MYSQL_INCLUDE_DIRS})
    target_link_libraries(shop PRIVATE ${MYSQL_LIBRARIES})
endif()
