cmake_minimum_required(VERSION 3.25)

project(LineWidthTest)

if(NOT DEFINED ENV{APRYSE_LICENSE_KEY})
    message(FATAL_ERROR "Please set the environment variable APRYSE_LICENSE_KEY with your apryse license key")
endif()

set(APRYSE_LICENSE_KEY $ENV{APRYSE_LICENSE_KEY})
configure_file(license.h.in license.h)

set(APRYSE_SDK_ROOT_PATH "$ENV{APRYSE_SDK_PATH}/PDFNetC")
if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    string(APPEND APRYSE_SDK_ROOT_PATH "64/")
else()
    string(APPEND APRYSE_SDK_ROOT_PATH "/")
endif()

add_executable(${PROJECT_NAME} main.cpp license.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_BINARY_DIR}"
    "${APRYSE_SDK_ROOT_PATH}/Headers"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${APRYSE_SDK_ROOT_PATH}/Lib/PDFNetC${CMAKE_LINK_LIBRARY_SUFFIX}")

if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "/DELAYLOAD:${APRYSE_SDK_ROOT_PATH}/Lib/PDFNetC.dll")
endif()

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${APRYSE_SDK_ROOT_PATH}/Lib/PDFNetC.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/PDFNetC.dll")
endif()
