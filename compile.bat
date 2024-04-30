@echo off

@REM set important variables
for %%f in ("%CD%") do set PROJNAME=%%~nxf

set FORMAT=gbc
set CC=c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j

@REM compile .c files into .o files
%CC% -c -o main.o main.c

%CC% -c -o data/sprites.o data/sprites.c
%CC% -c -o data/bkg.o data/bkg.c
%CC% -c -o data/bkgMap.o  data/bkgMap.c
%CC% -c -o data/cursores.o data/cursores.c

set data=data/bkg.o data/bkgMap.o data/sprites.o data/cursores.o

%CC% -c -o include/Sprite.o include/Sprite.c
%CC% -c -o include/BKG.o include/BKG.c
%CC% -c -o include/OAM.o include/OAM.c

set include=include/Sprite.o include/BKG.o include/OAM.o

%CC% -c -o classes/Plane.o classes/Plane.c
%CC% -c -o classes/GameVisualiser.o  classes/GameVisualiser.c

set classes=classes/Plane.o classes/GameVisualiser.o

@REM Compile a .gb file from the compiled .o files
if %FORMAT% EQU gb (
	set CREATE_BIN=%CC% -o %PROJNAME%.%FORMAT% 
) else if %FORMAT% EQU gbc (
	set CREATE_BIN=%CC% -Wm-yc -o %PROJNAME%.%FORMAT%
)
%CREATE_BIN% main.o %include% %data% %classes%

@REM delete intermediate files created for the conmpilation process
DEL /S *.asm > NUL 2>&1
DEL /S *.lst > NUL 2>&1
DEL /S *.ihx > NUL 2>&1
DEL /S *.sym > NUL 2>&1
DEL /S *.o   > NUL 2>&1
DEL /S *.map > NUL 2>&1
DEL /S *.noi > NUL 2>&1

if "%~1" EQU "emu" (
	c:\gbdk\Emulicious\Emulicious.exe %PROJNAME%.%FORMAT%
) else if "%~1" EQU "bgb" (
	C:\gbdk\bgb\bgb.exe %PROJNAME%.%FORMAT%
)