@echo off

for /d %%i in (*.*) do (cd %%i
del /s *.ncb
del /s *.opt
del /s *.plg
del /s *.aps
del /s *.fd
des /s *.bak
del /s *.positions
rd /s/q debug
rd /s/q release
cd ..)

