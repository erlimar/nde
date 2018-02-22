## Copyright (c) E5R Development Team. All rights reserved.
## Licensed under the Apache License, Version 2.0. More license information in LICENSE.txt.
# -----------------------------------------------------------------------------------------
# Makefile para construir nde no Linux usando GNU Make.
#
# Compiladores suportados:
# - GCC >= 4
# -----------------------------------------------------------------------------------------

BUILD_DIR = ../build/linux
SRC_DIR = ../src
LINUX_SRC_DI = ./
API_SRC_DIR = ./api
INCLUDE_DIR = ../include

TARGET = $(BUILD_DIR)/nde

MKDIR = mkdir -p
DEL = rm -f
RM = rm -f -d -r

CC = gcc
CC_FLAGS = -std=c11 -x c -D NDE_BUILD_ON_LINUX -D DEBUG -I$(INCLUDE_DIR) -c 
LK = gcc
LK_FLAGS = 

# -----------------------------------------------------------------------------------------
# OBJETOS
# -----------------------------------------------------------------------------------------

OBJECTS = $(BUILD_DIR)/main.o \
	$(BUILD_DIR)/process.o \
	$(BUILD_DIR)/shared-runtime.o \
	$(BUILD_DIR)/linux-runtime.o \
	$(BUILD_DIR)/log.o \
	$(BUILD_DIR)/data-list.o \

# -----------------------------------------------------------------------------------------
# ALVOS PRINCIPAIS
# -----------------------------------------------------------------------------------------

all: $(TARGET)

test: $(BUILD_DIR)/linuxparent $(BUILD_DIR)/linuxchild

clean: $(BUILD_DIR)
	 $(RM) $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(LK) $(LK_FLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

# -----------------------------------------------------------------------------------------
# ALVOS DOS COMPONENTES NDE
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/main.o $?

$(BUILD_DIR)/process.o: $(SRC_DIR)/process.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/process.o $?

$(BUILD_DIR)/shared-runtime.o: $(SRC_DIR)/shared-runtime.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/shared-runtime.o $?

$(BUILD_DIR)/log.o: $(SRC_DIR)/log.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/log.o $?

$(BUILD_DIR)/data-list.o: $(SRC_DIR)/data-list.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/data-list.o $?

# -----------------------------------------------------------------------------------------
# ALVOS DA API WINDOWS PARA NDE
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)/linux-runtime.o: $(API_SRC_DIR)/runtime.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/linux-runtime.o $?

# -----------------------------------------------------------------------------------------
# ALVOS DOS TESTES
# -----------------------------------------------------------------------------------------

$(BUILD_DIR)/linux-parent.o: $(LINUX_SRC_DI)/linux-parent.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/linux-parent.o $?

$(BUILD_DIR)/linux-child.o: $(LINUX_SRC_DI)/linux-child.c
	$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/linux-child.o $?

$(BUILD_DIR)/linuxparent: $(BUILD_DIR) $(BUILD_DIR)/linux-parent.o
	$(LK) $(LK_FLAGS) -o $(BUILD_DIR)/linuxparent $(BUILD_DIR)/linux-parent.o

$(BUILD_DIR)/linuxchild: $(BUILD_DIR) $(BUILD_DIR)/linux-child.o
	$(LK) $(LK_FLAGS) -o $(BUILD_DIR)/linuxchild $(BUILD_DIR)/linux-child.o
