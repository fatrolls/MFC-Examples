
attrib -h *.suo
del *.suo
del *.user
del *.ncb
del *.aps
del *.opt
del *.plg
del *.old

del Release\*.htm
del Release\*.obj
del Release\*.pdb
del Release\*.pch
del Release\*.ilk
del Release\*.res
del Release\*.idb
del Release\*.dep
del Release\*.bsc
del Release\*.sbr
del Release\*.exp
del Release\*.lib
del Release\*.manifest

rmdir Debug /S /Q
rmdir x64 /S /Q
