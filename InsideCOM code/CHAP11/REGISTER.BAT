@echo off
rem
rem Register.bat
rem Registration file for Chapter 11
rem
echo on
regsvr32 /s Server.dll
Server /RegServer