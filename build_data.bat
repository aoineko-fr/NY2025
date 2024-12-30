@echo off
@REM setlocal EnableDelayedExpansion

:: Setup path
set Tools=..\..\tools
set MSXtk=%Tools%\MSXtk\bin
set Dest=.\content

:: Create destination folder if needed
if not exist %Dest% md %Dest%

:: Export player sprite
echo -- Export sprite data...
%MSXtk%\MSXimg datasrc/snow.png -out %Dest%/sprt_snow.h -pos 0 0 -size 16 16 -num 10 1 -name g_Sprites -mode sprt -trans 0xFF00C3

:: Generate mathematics tables
echo -- Generate mathematics tables...
%MSXtk%\MSXmath -num 256 -bytes 1 -shift 0 proj 32 -o %Dest%/mt_proj256.bin
%MSXtk%\MSXmath -num 256 -bytes 1 -shift 0 proj 32 -o %Dest%/mt_proj256.h
@REM %MSXtk%\MSXmath -num 256 -bytes 1 -shift 0 proj 4.0 0.05 0.5 -o %Dest%/mt_proj256.bin
@REM %MSXtk%\MSXmath -num 256 -bytes 1 -shift 0 proj 4.0 0.05 0.5 -o %Dest%/mt_proj256.h

%MSXtk%\MSXmath -num 256 -bytes 2 -shift 0 muls -o %Dest%/mt_muls.bin
%MSXtk%\MSXmath -num 256 -bytes 2 -shift 0 muls -o %Dest%/mt_muls.h

%MSXtk%\MSXmath -num 256 -bytes 2 -shift 6  sin cos -o %Dest%/mt_trigo.h
