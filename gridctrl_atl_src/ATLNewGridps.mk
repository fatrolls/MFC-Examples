
ATLNewGridps.dll: dlldata.obj ATLNewGrid_p.obj ATLNewGrid_i.obj
	link /dll /out:ATLNewGridps.dll /def:ATLNewGridps.def /entry:DllMain dlldata.obj ATLNewGrid_p.obj ATLNewGrid_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ATLNewGridps.dll
	@del ATLNewGridps.lib
	@del ATLNewGridps.exp
	@del dlldata.obj
	@del ATLNewGrid_p.obj
	@del ATLNewGrid_i.obj
