@echo off

if not exist build\. mkdir build
pushd build

set opts=-DENABLE_ASSERT

REM # nologo: If this flag is present, the compiler executable doesn't print Microsoft banner and other unnecessary logs while compiling

set flags=-nologo

cl  %opts% %flags% ..\main.cpp

popd