# MYVXD.mak - makefile for VxD MYVXD

DEVICENAME = MYVXD
TARGET = WIN40
DEBUGGER = SOFTICE
FRAMEWORK = CPP
DEBUG = 1
OBJECTS = MYVXD.OBJ

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

MYVXD.OBJ:	MYVXD.cpp MYVXD.h