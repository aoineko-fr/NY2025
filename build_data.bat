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
%MSXtk%\MSXimg datasrc/snow.png -out %Dest%/sprt_snow.h -pos 0 0 -size 16 16 -num 8 1 -name g_SnowPattern -mode sprt -trans 0xFF00C3

:: Generate mathematics tables
echo -- Generate mathematics tables...
%MSXtk%\MSXmath -num 256 -bytes 1 -shift 0  proj -o %Dest%/mt_proj256.bin
