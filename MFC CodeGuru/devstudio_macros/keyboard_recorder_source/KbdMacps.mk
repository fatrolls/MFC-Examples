
KbdMacps.dll: dlldata.obj KbdMac_p.obj KbdMac_i.obj
	link /dll /out:KbdMacps.dll /def:KbdMacps.def /entry:DllMain dlldata.obj KbdMac_p.obj KbdMac_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del KbdMacps.dll
	@del KbdMacps.lib
	@del KbdMacps.exp
	@del dlldata.obj
	@del KbdMac_p.obj
	@del KbdMac_i.obj
