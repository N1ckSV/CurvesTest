
cmake_minimum_required(VERSION 3.10)

project(Curves LANGUAGES CXX VERSION 1.0)



set(Curves_INCLUDE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")




option(BUILD_SHARED_LIBS "Default type is STATIC" OFF)
option(CURVES_USE_ASSERTIONS "Using exceptions instead of <assert.h> by default" OFF)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX 
    "${CMAKE_CURRENT_SOURCE_DIR}/install/${CMAKE_HOST_SYSTEM_NAME}/" CACHE PATH "Default install path" FORCE)
endif()


message(STATUS)
message(STATUS "C++ Standart: ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Make program: ${CMAKE_MAKE_PROGRAM}")
message(STATUS "C++ Make generator: ${CMAKE_GENERATOR}")
message(STATUS "C++ Make generator: ${CMAKE_GENERATOR}")
message(STATUS "C++ Make generator instance: ${CMAKE_GENERATOR_INSTANCE}")
message(STATUS "C++ Make generator platform: ${CMAKE_GENERATOR_PLATFORM}")
message(STATUS "C++ Make generator toolset: ${CMAKE_GENERATOR_TOOLSET}")
message(STATUS)


find_package(OpenMP REQUIRED)


set(Curves_SOURCE_FILES
    src/Circle.cpp
    src/Ellipse.cpp
    src/Helix.cpp
)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<BOOL:${BUILD_SHARED_LIBS}>:DLL>$<$<CONFIG:Debug>:Debug>")


if(BUILD_SHARED_LIBS)
    add_library(Curves SHARED ${Curves_SOURCE_FILES})
else()
    add_library(Curves STATIC ${Curves_SOURCE_FILES})
    target_compile_definitions(Curves PUBLIC CURVES_STATIC_LINK)
endif()

target_include_directories(Curves PUBLIC ${Curves_INCLUDE_DIR})

if(CURVES_USE_ASSERTIONS)
    target_compile_definitions(Curves PUBLIC CURVES_USE_ASSERTIONS)
endif()

target_compile_definitions(Curves
    PRIVATE
        CURVES_FOREXPORT
)

add_executable(CurvesTest src/Main.cpp)

target_link_libraries(CurvesTest Curves OpenMP::OpenMP_CXX)


install(
	TARGETS Curves CurvesTest
	LIBRARY DESTINATION  ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION  ${CMAKE_INSTALL_LIBDIR}
)