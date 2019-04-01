@echo off
cd build/vs2010
msbuild /nologo /verbosity:quiet /p:Configuration=Release;PlatformToolset=v141 NativeFileDialog.sln
