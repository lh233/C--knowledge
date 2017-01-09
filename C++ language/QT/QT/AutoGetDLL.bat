for /r "%cd%" %%i in (*.exe) do (
   C:\Qt\Qt5.7.0\5.7\mingw49_32\bin\windeployqt.exe "%%~nxi"
)

pause 