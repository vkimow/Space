@echo off

if exist bin (
    echo "Clear bin directory"
    del /f /s /q bin
)

if exist project (
    echo "Clear project directory"
    del /f /s /q project
) else (
    echo "Create project directory"
    mkdir project
)

echo "Build solution"
call cmake . -B project
PAUSE