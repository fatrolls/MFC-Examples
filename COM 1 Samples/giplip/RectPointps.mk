
RectPointps.dll: dlldata.obj RectPoint_p.obj RectPoint_i.obj
	link /dll /out:RectPointps.dll /def:RectPointps.def /entry:DllMain dlldata.obj RectPoint_p.obj RectPoint_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del RectPointps.dll
	@del RectPointps.lib
	@del RectPointps.exp
	@del dlldata.obj
	@del RectPoint_p.obj
	@del RectPoint_i.obj
