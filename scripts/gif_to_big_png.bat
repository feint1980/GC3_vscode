@echo off
setlocal enabledelayedexpansion

:: Check if no arguments
if "%~1"=="" (
    echo [ERROR] No argument provided.
    echo Usage: %~nx0 yourfile.gif [optional_second_argument]
    exit /b 1
)

:: Check if more than 2 arguments
if not "%~3"=="" (
    echo [ERROR] Too many arguments.
    echo Usage: %~nx0 yourfile.gif [optional_second_argument]
    exit /b 1
)

:: Set default value
set "timeTick=1"

:: If argument 2 exists, use it
if not "%~2"=="" (
    set "timeTick=%~2"
)

:: Get the full path of the file and its parent folder
set "file=%~1"
if not exist "%file%" (
    echo [ERROR] File not found: %file%
    exit /b 1
)

set "folder=%~dp1"

mkdir "%folder%/result"
mkdir "%folder%/result/tmp"
mkdir "%folder%/result/Packets"
mkdir "%folder%/result/F_AObjects"


set "giffile=%~1"

for /f "tokens=1,2" %%a in ('magick identify -format "%%w %%h" "%giffile%[0]"') do (
    set "width=%%a"
    set "height=%%b"
)

echo convert gif %1 with: !width! height: !height!
magick convert -coalesce %1 "%folder%/result/tmp/frame_%%03d.png"



:: Count number of files in that folder
set "count=0"
for %%f in ("%folder%/result/tmp/*") do (
    set /a count+=1
)

:: Output result
echo Total files in "%folder%/result/tmp/" = !count!

set "bestDiff=9999"
set "bestCols=0"
set "bestRows=0"

:: Use !count! inside the loop, and ! for variables modified inside loops
for /L %%r in (1,1,!count!) do (
    set /a rem=!count! %% %%r
    if !rem! EQU 0 (
        set /a c=!count! / %%r
        if !c! GEQ %%r (
            set /a diff=!c! - %%r
            if !diff! LSS !bestDiff! (
                set /a bestDiff=!diff!
                set /a bestCols=!c!
                set /a bestRows=%%r
            )
        )
    )
)

echo Best layout: !bestCols! columns x !bestRows! rows

magick montage "%folder%/result/tmp/frame_*.png" -tile !bestCols!x!bestRows! -geometry +0+0 -background none "%folder%/result/Packets/%~n1.png"


set /a totalWidth=width*bestCols
set /a totalHeight=height*bestRows


echo checkTotalwith !totalWidth! checktotalHeight !totalHeight!

set "xmlFile=%folder%/result/Packets/%~n1.xml"

(
echo ^<?xml version="1.0" encoding="UTF-8"?^>
echo ^<TextureAtlas imagePath="%~n1.png" width="%totalWidth%" height="%totalHeight%"^>
) > %xmlFile%
set /a frameNum=0

set /a targetRow = bestRows -1
set /a targetCol = bestCols -1

for /L %%r in (0,1,!targetRow!-1) do (
    for /L %%c in (0,1,!targetCol!-1) do (
        if !frameNum! LEQ !count! (
            set zeroCount=0 
            if !frameNum! LSS 10 (
            set /a zeroCount=!zeroCount! + 1
            )
            if !frameNum! LSS 100 (
            set /a zeroCount=!zeroCount! + 1
            )
            set "FF=!frameNum!"
            rem echo "zeroCount: !zeroCount!"
            for /L %%i in (1,1,!zeroCount!) do (
                set "FF=0!FF!"
            )

            set /a x=%%c * width
            set /a y=%%r * height
            >> "%xmlFile%" echo     ^<sprite n="frame_!FF!.png" x="!x!" y="!y!" w="!width!" h="!height!" /^>
            set /a frameNum+=1
        )
    )
)

echo ^</TextureAtlas^> >> %xmlFile%


set "animFile=%folder%/result/F_AObjects/%~n1.xml"

(
echo ^<F_AObj name="%~n1"^>
) > %animFile%

echo ^<animations^> >> %animFile%


echo ^<animation name = "play"^> >> %animFile%

echo ^<anims^> >> %animFile%

set /a animNum=0
set /a count=!count!-1
for /L %%r in (0,1,!count!) do (

     set zeroCount=0 
    if !animNum! LSS 10 (
    set /a zeroCount=!zeroCount! + 1
    )
    if !animNum! LSS 100 (
    set /a zeroCount=!zeroCount! + 1
    )
    set "FF=!animNum!"
    rem echo "zeroCount: !zeroCount!"
    for /L %%i in (1,1,!zeroCount!) do (
        set "FF=0!FF!"
    )
    >> "%animFile%" echo ^<anim name="%~n1/frame_!FF!.png" time = "%timeTick%" /^>
    set /a animNum+=1
)

echo ^</anims^> >> %animFile%
echo ^</animation^> >> %animFile%
echo ^</animations^> >> %animFile%
echo ^</F_AObj^> >> %animFile%
rmdir /s /q "%folder%/result/tmp/"