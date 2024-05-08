@echo off

@REM set important variables
for %%f in ("%CD%") do set PROJNAME=%%~nxf
set FORMAT=gbc

set CC=c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j

@REM compile .c files into .o files
%CC% -c -o main.o main.c

@REM DATA
%CC% -c -o data/sprites.o data/sprites.c
%CC% -c -o data/bkg.o data/bkg.c
%CC% -c -o data/bkgMap.o  data/bkgMap.c
%CC% -c -o data/cursores.o data/cursores.c
@REM %CC% -c -o data/window.o data/window.c
set data=data/bkg.o data/bkgMap.o data/sprites.o data/cursores.o 
@REM data/window.o

@REM INCLUDE
@REM %CC% -c -o include/Sprite.o include/Sprite.c
@REM %CC% -c -o include/BKG.o include/BKG.c
@REM %CC% -c -o include/OAM.o include/OAM.c
@REM set include=include/Sprite.o include/BKG.o include/OAM.o

@REM GAME
%CC% -c -o classes/Game/DataPlane.o classes/Game/DataPlane.c
%CC% -c -o classes/Game/GameVisualiser.o  classes/Game/GameVisualiser.c
%CC% -c -o classes/Game/Cursor.o classes/Game/Cursor.c
set game=classes/Game/DataPlane.o classes/Game/GameVisualiser.o classes/Game/Cursor.o

set classes=%game%

@REM Compile a .gb file from the compiled .o files
if %FORMAT% EQU gbc (
	set CREATE_BIN=%CC% -Wm-yc -o %PROJNAME%.%FORMAT%
) else (
	set CREATE_BIN=%CC% -o %PROJNAME%.%FORMAT% 
)
%CREATE_BIN% %data% %classes% main.o

@REM delete intermediate files created for the conmpilation process
DEL /S *.asm > NUL 2>&1
DEL /S *.lst > NUL 2>&1
DEL /S *.ihx > NUL 2>&1
DEL /S *.sym > NUL 2>&1
DEL /S *.o   > NUL 2>&1
DEL /S *.map > NUL 2>&1
DEL /S *.noi > NUL 2>&1
