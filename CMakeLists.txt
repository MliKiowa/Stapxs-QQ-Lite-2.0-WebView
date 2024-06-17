cmake_minimum_required (VERSION 3.10)
# MSVC热调试
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("StapxsQQWebview")

if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# 平台宏
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(_WIN_PLATFORM_ true)
    add_definitions(-D _WIN_PLATFORM_)
endif()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(_LINUX_PLATFORM_ true)
    add_definitions(-D _LINUX_PLATFORM_)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM "x86")
endif()

# 打包类型
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()
if(_LINUX_PLATFORM_)
    find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    pkg_check_modules(WEBKIT2 REQUIRED webkit2gtk-4.0)
    include_directories(${GTK3_INCLUDE_DIRS})
	link_directories(${GTK3_LIBRARY_DIRS})
endif()

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/include/wil/include/")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/include/webview2/build/native/include/")
include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_SOURCE_DIR}/include/StapxsQQWebview/")

if(_WIN_PLATFORM_)
    link_libraries("${PROJECT_SOURCE_DIR}/include/webview2/build/native/${PLATFORM}/WebView2LoaderStatic.lib")
endif()
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/StapxsQQWebview/*.cpp")


if(_WIN_PLATFORM_)
    add_executable (StapxsQQWebview WIN32 "./include/StapxsQQWebview.exe.manifest" ${SOURCES} )
elseif(_LINUX_PLATFORM_)
    add_executable (StapxsQQWebview  ${SOURCES} ${GTK3_LIBRARIES} ${WEBKIT2_LIBRARIES})
endif()