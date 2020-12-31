@echo.
@echo -------- Should not load slept.dll --------------------------------------
..\bin\sleepold.exe
@echo.
@echo -------- Adding slept.dll to sleepold.exe -------------------------------
..\bin\setdll.exe -d:slept.dll ..\bin\sleepold.exe
@echo.
@echo -------- Should load slept.dll statically -------------------------------
..\bin\sleepold.exe
@echo.
@echo -------- Removing slept.dll from sleepold.exe ---------------------------
..\bin\setdll.exe -r ..\bin\sleepold.exe
@echo.
@echo -------- Should not load slept.dll --------------------------------------
..\bin\sleepold.exe
@echo.
@echo -------- Should load slept.dll dynamically using withdll.exe ------------
..\bin\withdll.exe -d:slept.dll ..\bin\sleepold.exe
@echo.
@echo -------- Should load slept.dll dynamically using injdll.exe ------------
..\bin\sleepinj.exe /i:..\bin\injdll.exe /d:slept.dll ..\bin\sleepold.exe -wait 
@echo.
@echo -------- Should load slept.dll statically -------------------------------
..\bin\sleepnew.exe
@echo.
@echo -------- Test completed. ------------------------------------------------

