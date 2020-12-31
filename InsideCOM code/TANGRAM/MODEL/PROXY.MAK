#################################################
#
# Chapter 13 - Tangram Sample
#
#	Model Component - Proxy/Stub DLL.
#

# ***** The Shared directory must be on the include pat *****

# Builds the Proxy/Stub DLL for the Model Component.
OUTDIR=Proxy
SHAREDIR=..\Share
#
# Flags - Always compiles debug.
#
CPP_FLAGS=/c /MTd /Zi /Og 
DLL_LINK_FLAGS=/NOD /DLL 

#################################################
#
# Targets
#

all : proxy.dll

#################################################
#
# Proxy Source Files
#
$(OUTDIR)\dlldata.obj : dlldata.c 
	cl /c /DWIN32 /DREGISTER_PROXY_DLL /Fo"$*.obj" dlldata.c

$(OUTDIR)\model_i_p.obj : model_i_p.c $(SHAREDIR)\model_i.h
	cl /c /DWIN32 /DREGISTER_PROXY_DLL /Fo"$*.obj" model_i_p.c

$(OUTDIR)\model_i.obj : $(SHAREDIR)\model_i.c
	cl /c /DWIN32 /DREGISTER_PROXY_DLL /Fo"$*.obj" $(SHAREDIR)\model_i.c

$(OUTDIR)\event_i.obj : $(SHAREDIR)\event_i.c
	cl /c /DWIN32 /DREGISTER_PROXY_DLL /Fo"$*.obj" $(SHAREDIR)\event_i.c

$(OUTDIR)\event_i_p.obj : event_i_p.c
	cl /c /DWIN32 /DREGISTER_PROXY_DLL /Fo"$*.obj" event_i_p.c
	

PROXYSTUBOBJS=	$(OUTDIR)\dlldata.obj 	\
				$(OUTDIR)\model_i_p.obj	\
				$(OUTDIR)\model_i.obj 	\
				$(OUTDIR)\event_i.obj 	\
				$(OUTDIR)\event_i_p.obj


PROXYSTUBLIBS=	kernel32.lib	\
		rpcndr.lib	\
		rpcns4.lib	\
		rpcrt4.lib	\
		uuid.lib 

proxy.dll : $(PROXYSTUBOBJS) proxy.def
	link /dll /out:proxy.dll /def:proxy.def $(PROXYSTUBOBJS) $(PROXYSTUBLIBS) 
	regsvr32 /s proxy.dll

	