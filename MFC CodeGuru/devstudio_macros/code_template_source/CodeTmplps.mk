
CodeTmplps.dll: dlldata.obj CodeTmpl_p.obj CodeTmpl_i.obj
	link /dll /out:CodeTmplps.dll /def:CodeTmplps.def /entry:DllMain dlldata.obj CodeTmpl_p.obj CodeTmpl_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del CodeTmplps.dll
	@del CodeTmplps.lib
	@del CodeTmplps.exp
	@del dlldata.obj
	@del CodeTmpl_p.obj
	@del CodeTmpl_i.obj
