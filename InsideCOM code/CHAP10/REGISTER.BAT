@echo off
rem
rem Register.bat
rem Registration file for Chapter 10
rem
echo on
regsvr32 /s Server.dll
regsvr32 /s Proxy.dll
Server /RegServer