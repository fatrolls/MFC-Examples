
MeowMonikerps.dll: dlldata.obj MeowMoniker_p.obj MeowMoniker_i.obj
	link /dll /out:MeowMonikerps.dll /def:MeowMonikerps.def /entry:DllMain dlldata.obj MeowMoniker_p.obj MeowMoniker_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del MeowMonikerps.dll
	@del MeowMonikerps.lib
	@del MeowMonikerps.exp
	@del dlldata.obj
	@del MeowMoniker_p.obj
	@del MeowMoniker_i.obj
