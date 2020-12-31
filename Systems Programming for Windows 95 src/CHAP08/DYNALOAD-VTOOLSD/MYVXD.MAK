# MYVXD.mak - makefile for VxD MYVXD

DEVICENAME = MYVXD
DYNAMIC = 1
TARGET = WIN40
DEBUGGER = SOFTICE
FRAMEWORK = C
DEBUG = 1
OBJECTS = MYVXD.OBJ

all: $(DEVICENAME).VXD

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

MYVXD.OBJ:	MYVXD.c MYVXD.h
