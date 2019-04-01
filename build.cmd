@echo off
cd build/vs2010
msbuild /nologo /verbosity:quiet /p:Configuration="Release|x64" NativeFileDialog.sln
