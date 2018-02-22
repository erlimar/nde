// Copyright (c) E5R Development Team. All rights reserved.
// Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.

#ifndef _NDE_H_
#define _NDE_H_

#if defined(NDE_BUILD_ON_WINDOWS)
    #include <windows.h>
    
    #define NDE_WINDOWS
    #define NDE_MAX_PATH MAX_PATH
#elif defined(NDE_BUILD_ON_LINUX)
    #include <unistd.h>
    
    #define NDE_LINUX
    #define NDE_MAX_PATH _PC_PATH_MAX
#elif defined(NDE_BUILD_ON_MACOS)
    #error "Build Host is macOS!"
#else
    #error "Please define NDE_BUILD_ON_WINDOWS, NDE_BUILD_ON_LINUX or NDE_BUILD_ON_MACOS!"
#endif

// #if (NDE_BUILD_HOST == "WINDOWS")
// #error Windows
// #else
// #error Outro
// #endif

#include <stddef.h>

#define NdeNullPtr NULL

typedef unsigned char NdeByte;
typedef void *NdePtr;
typedef size_t NdePtrSize;

#endif // _NDE_H_
