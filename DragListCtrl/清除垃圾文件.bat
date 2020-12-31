rd /s /q Debug
rd /s /q Release
rd /s /q Unicode_Release
rd /s /q Unicode_Debug

del /s /q *.ncb
del /s /q *.opt
del /s /q *.plg
del /s /q *.aps
del /s /q AppLog.txt
del /s /q DebugData.txt

attrib -h -s -r *.suo

del /s /q *.user
del /s /q *.suo


