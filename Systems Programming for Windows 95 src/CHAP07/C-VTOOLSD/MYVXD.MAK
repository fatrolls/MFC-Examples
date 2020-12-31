# MYVXD.mak - makefile for VxD MYVXD

DEVICENAME = MYVXD
FRAMEWORK = C
DEBUG = 1
OBJECTS = myvxd.OBJ

!include $(VTOOLSD)\include\vtoolsd.mak
!include $(VTOOLSD)\include\vxdtarg.mak

myvxd.OBJ:	myvxd.c myvxd.h