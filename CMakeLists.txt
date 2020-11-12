cmake_minimum_required(VERSION 3.16)

project(HandTracker CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(OpenGL REQUIRED)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt 
				INSTALL_FOLDER ${CMAKE_BINARY_DIR}/pkgs
				BASIC_SETUP CMAKE_TARGETS BUILD missing)

add_executable(HandTracker
	src/main.cpp
	src/Mesh.cpp
	src/Mesh.h
	src/Shader.h
)

target_link_libraries(HandTracker 
	OpenGL::GL 
	CONAN_PKG::glew
	CONAN_PKG::glm
	CONAN_PKG::glfw
)