@echo off

set PERL_PATH=%UserProfile%\home\bin\perl\bin
set DXSDK_PATH=%ProgramFiles(x86)%\Microsoft DirectX SDK (March 2008)\Utilities\x86

cmd /k "set path=%path%;%PERL_PATH%;%DXSDK_PATH% & cd stdshaders"

