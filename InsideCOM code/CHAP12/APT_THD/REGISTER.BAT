@echo off
rem
rem Register.bat
rem Registration file for Chapter 12 apartment-thread example
rem
echo on
regsvr32 -s Proxy.dll
regsvr32 -s Server.dll