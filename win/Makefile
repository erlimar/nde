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
LK_FLAGS = /nologo /SUBSYSTEM:CONSOLE user32.lib

# -----------------------------------------------------------------------------------------
# OBJETOS
# -----------------------------------------------------------------------------------------

OBJECTS = $(BUILD_DIR)\main.obj \
	$(BUILD_DIR)\runtime.obj \
	$(BUILD_DIR)\process.obj \

# -----------------------------------------------------------------------------------------
# ALVOS PRINCIPAIS
# -----------------------------------------------------------------------------------------

all: $(TARGET) $(BUILD_DIR)\winparent.exe $(BUILD_DIR)\winchild.exe

clean: $(BUILD_DIR)
	$(RM) $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(LK) $(LK_FLAGS) /OUT:$(TARGET) $(OBJECTS)

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

# -----------------------------------------------------------------------------------------
# ALVOS DOS TESTES
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)\win-parent.obj: $(SRC_DIR)\win-parent.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\win-parent.obj %s

$(BUILD_DIR)\win-child.obj: $(SRC_DIR)\win-child.c
	$(CC) $(CC_FLAGS) /Fo$(BUILD_DIR)\win-child.obj %s

$(BUILD_DIR)\winparent.exe: $(BUILD_DIR) $(BUILD_DIR)\win-parent.obj
	$(LK) $(LK_FLAGS) /OUT:$(BUILD_DIR)\winparent.exe $(BUILD_DIR)\win-parent.obj

$(BUILD_DIR)\winchild.exe: $(BUILD_DIR) $(BUILD_DIR)\win-child.obj
	$(LK) $(LK_FLAGS) /OUT:$(BUILD_DIR)\winchild.exe $(BUILD_DIR)\win-child.obj 
