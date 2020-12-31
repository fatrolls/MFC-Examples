
Conexeps.dll: dlldata.obj Conexe_p.obj Conexe_i.obj
	link /dll /out:Conexeps.dll /def:Conexeps.def /entry:DllMain dlldata.obj Conexe_p.obj Conexe_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Conexeps.dll
	@del Conexeps.lib
	@del Conexeps.exp
	@del dlldata.obj
	@del Conexe_p.obj
	@del Conexe_i.obj
