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

TARGET = $(BUILD_DIR)\nde.exe

MKDIR = mkdir
DEL = erase /F /Q
RM = rmdir /S /Q

CC = cl.exe
CC_FLAGS = /nologo /c /w -DDEBUG /I$(INCLUDE_DIR)
LK = link.exe
LK_FLAGS = /nologo /DEBUG=FULL /SUBSYSTEM:CONSOLE

# -----------------------------------------------------------------------------------------
# OBJETOS
# -----------------------------------------------------------------------------------------

OBJECTS = $(BUILD_DIR)\main.obj \
	$(BUILD_DIR)\runtime.obj \
	$(BUILD_DIR)\process.obj \

# -----------------------------------------------------------------------------------------
# ALVOS PRINCIPAIS
# -----------------------------------------------------------------------------------------

all: $(TARGET)

clean: $(BUILD_DIR)
	$(RM) $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(LK) $(LK_FLAGS) /PDB:$(BUILD_DIR)\nde.pdb /OUT:$(TARGET) $(OBJECTS)

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

# -----------------------------------------------------------------------------------------
# ALVOS DOS COMPONENTES NDE
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)\main.obj: $(SRC_DIR)\main.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\main.obj %s

$(BUILD_DIR)\process.obj: $(SRC_DIR)\process.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\process.obj %s

# -----------------------------------------------------------------------------------------
# ALVOS DA API WINDOWS PARA NDE
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)\runtime.obj: $(API_SRC_DIR)\runtime.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\runtime.obj %s
