
Icmpcomps.dll: dlldata.obj Icmpcom_p.obj Icmpcom_i.obj
	link /dll /out:Icmpcomps.dll /def:Icmpcomps.def /entry:DllMain dlldata.obj Icmpcom_p.obj Icmpcom_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Icmpcomps.dll
	@del Icmpcomps.lib
	@del Icmpcomps.exp
	@del dlldata.obj
	@del Icmpcom_p.obj
	@del Icmpcom_i.obj
