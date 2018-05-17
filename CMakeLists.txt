cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (nde)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SRCS
    src/data-list.c
    src/log.c
    src/main.c
    src/process.c
    src/shared-runtime.c
)

if(UNIX)
    add_definitions(-DNDE_BUILD_ON_LINUX)
    set(SRCS
        ${SRCS}
        platform/linux/api/runtime.c
    )
endif()

if(APPLE)
    add_definitions(-DNDE_BUILD_ON_MACOS)
endif()

if(WIN32)
    add_definitions(-DNDE_BUILD_ON_WINDOWS)
    set(SRCS
        ${SRCS}
        platform/win32/api/runtime.c
    )
endif()

add_executable(nde ${SRCS})
