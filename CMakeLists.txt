cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project (nde)

# ---------------------------------
# Pré-requisitos
# ---------------------------------
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/.build-deps")

set(REQUIRED_LIBS)

find_package(CURL REQUIRED)

if(CURL_FOUND)
  #INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
  #SET(REQUIRED_LIBS ${REQUIRED_LIBS} ${CURL_LIBRARIES} )
  message(WARNING "Found the CURL library and development files.")
  message(WARNING "  -> CURL_INCLUDE_DIR: ${CURL_INCLUDE_DIR}")
  message(WARNING "  -> CURL_LIBRARIES: ${CURL_LIBRARIES}")
else(CURL_FOUND)
  message(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

# ---------------------------------
# Versão
# ---------------------------------
file(READ version.txt versionText)

if (NOT versionText)
    message(FATAL_ERROR "Unable to determine version. version.txt file is missing.")
endif()

string(STRIP "${versionText}" NDE_VERSION)
string(REPLACE "." ";" VERSION_PARTS ${NDE_VERSION})
list(GET VERSION_PARTS 0 nde-version_MAJOR)
list(GET VERSION_PARTS 1 nde-version_MINOR)
list(GET VERSION_PARTS 2 nde-version_PATCH)
set( NDE_VERSION_NORMALIZED "${nde-version_MAJOR}.${nde-version_MINOR}.${nde-version_PATCH}" )

# ---------------------------------
# Arquivos e diretórios do projeto
# ---------------------------------
include_directories("${PROJECT_SOURCE_DIR}/include")

set(SRCS_OBJ
    src/data-list.c
    src/log.c
    src/process.c
    src/shared-runtime.c
)

set(SRCS_HTTPS
    src/https.c
)

if(UNIX)
    add_definitions(-DNDE_BUILD_ON_LINUX)
    set(SRCS_OBJ
        ${SRCS_OBJ}
        platform/linux/api/runtime.c
    )
endif()

# if(APPLE)
#     add_definitions(-DNDE_BUILD_ON_MACOS)
# endif()

if(WIN32)
    add_definitions(-DNDE_BUILD_ON_WINDOWS)
    set(SRCS_OBJ
        ${SRCS_OBJ}
        platform/win32/api/runtime.c
    )
endif()

# ---------------------------------
# Alvos
# ---------------------------------
add_library(nde_objects OBJECT ${SRCS_OBJ})
add_executable(nde $<TARGET_OBJECTS:nde_objects> src/main.c)
add_executable(https ${SRCS_HTTPS})

# ---------------------------------
# Arquivos da instalação
# ---------------------------------
install(TARGETS  nde https
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib)

# ---------------------------------
# Empacotamento
# ---------------------------------
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NDE is a Native Development Environment")
set(CPACK_PACKAGE_VENDOR "E5R Development Team")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${NDE_VERSION_NORMALIZED}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-{CPACK_PACKAGE_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/README.md")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
