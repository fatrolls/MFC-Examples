
ATLMFCps.dll: dlldata.obj ATLMFC_p.obj ATLMFC_i.obj
	link /dll /out:ATLMFCps.dll /def:ATLMFCps.def /entry:DllMain dlldata.obj ATLMFC_p.obj ATLMFC_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ATLMFCps.dll
	@del ATLMFCps.lib
	@del ATLMFCps.exp
	@del dlldata.obj
	@del ATLMFC_p.obj
	@del ATLMFC_i.obj
