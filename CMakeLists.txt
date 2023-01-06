cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME gtest)
project ($(PROJECT_NAME) CXX)

add_executable(
    result
    gtest.cpp
)

set_property(TARGET result PROPERTY CXX_STANDARD 20)

# project (main CXX)

# add_executable(
#     result 
#     main.cpp
# )
