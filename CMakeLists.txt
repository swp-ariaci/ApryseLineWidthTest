cmake_minimum_required(VERSION 3.25)

project(LineWidthTest)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
