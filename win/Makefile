## Copyright (c) E5R Development Team. All rights reserved.
## Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.
# -----------------------------------------------------------------------------------------
# Makefile para construir nde no Windows usando Microsoft NMAKE.
#
# Compiladores suportados:
# - Microsoft Visual C++ Build Tools >= 2015
# -----------------------------------------------------------------------------------------

BUILD_DIR = ..\build
SRC_DIR = ..\src
API_SRC_DIR = .\api
INCLUDE_DIR = ..\include

MKDIR = mkdir
DEL = erase /F /Q
RM = rmdir /S /Q

CC = cl.exe
CC_FLAGS = /nologo /c /Wall /Gw /Gy /GA /I$(INCLUDE_DIR)

# -----------------------------------------------------------------------------------------
# COMMONS TARGETS
# -----------------------------------------------------------------------------------------

all: $(BUILD_DIR) \
$(BUILD_DIR)\main.obj \
$(BUILD_DIR)\process.obj

clean: $(BUILD_DIR)
	$(RM) $(BUILD_DIR)

# -----------------------------------------------------------------------------------------
# NDE CORE TARGETS
# -----------------------------------------------------------------------------------------

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

$(BUILD_DIR)\main.obj: $(SRC_DIR)\main.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\main.obj %s

# -----------------------------------------------------------------------------------------
# NDE WIN API TARGETS
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)\process.obj: $(API_SRC_DIR)\process.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\process.obj %s