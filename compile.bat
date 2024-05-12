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
set data=data/bkg.o data/bkgMap.o data/sprites.o data/cursores.o 

@REM INCLUDE
%CC% -c -o include/printer.o include/printer.c
set incl=include/printer.o

@REM GAME
%CC% -c -o classes/Game/PlaneData.o classes/Game/PlaneData.c
%CC% -c -o classes/Game/GameVisualiser.o  classes/Game/GameVisualiser.c
%CC% -c -o classes/Game/Cursor.o classes/Game/Cursor.c
%CC% -c -o classes/Game/PlaneFabric.o classes/Game/PlaneFabric.c
%CC% -c -o classes/Game/GameLogic.o classes/Game/GameLogic.c
set game=classes/Game/PlaneData.o classes/Game/GameVisualiser.o classes/Game/Cursor.o classes/Game/PlaneFabric.o classes/Game/GameLogic.o

set classes=%game%

@REM Compile a .gb file from the compiled .o files
if %FORMAT% EQU gbc (
	set CREATE_BIN=%CC% -Wm-yc -o %PROJNAME%.%FORMAT%
) else (
	set CREATE_BIN=%CC% -o %PROJNAME%.%FORMAT% 
)
%CREATE_BIN% %data% %classes% %incl% main.o

@REM delete intermediate files created for the conmpilation process
DEL /S *.asm > NUL 2>&1
DEL /S *.lst > NUL 2>&1
DEL /S *.ihx > NUL 2>&1
DEL /S *.sym > NUL 2>&1
DEL /S *.o   > NUL 2>&1
DEL /S *.map > NUL 2>&1
DEL /S *.noi > NUL 2>&1
