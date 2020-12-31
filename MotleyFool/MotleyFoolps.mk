
MotleyFoolps.dll: dlldata.obj MotleyFool_p.obj MotleyFool_i.obj
	link /dll /out:MotleyFoolps.dll /def:MotleyFoolps.def /entry:DllMain dlldata.obj MotleyFool_p.obj MotleyFool_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MotleyFoolps.dll
	@del MotleyFoolps.lib
	@del MotleyFoolps.exp
	@del dlldata.obj
	@del MotleyFool_p.obj
	@del MotleyFool_i.obj
