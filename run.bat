@echo off

for %%f in ("%CD%") do set PROJNAME=%%~nxf
set FORMAT=gbc

if "%~1" EQU "emu" (
	c:\gbdk\Emulicious\Emulicious.exe %PROJNAME%.%FORMAT%
) else (
	C:\gbdk\bgb\bgb.exe %PROJNAME%.%FORMAT%
)