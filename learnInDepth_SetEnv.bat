@echo off
SET ARM_CROSS_TOOLCHAIN_PATH=C:\ARM\bin
SET PYTHON_PATH=C:\Python311
SET goil_PATH=..\..\

SET PATH=%ARM_CROSS_TOOLCHAIN_PATH%;%PYTHON_PATH%;%goil_PATH%;%PATH%

echo Environment variables have been set.
