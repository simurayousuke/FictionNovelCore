rd /s/q .\release
xcopy .\Release.win32 .\release /e
set path=release
del /f/s/q .\%path%\*.obj
del /f/s/q .\%path%\*.lib
del /f/s/q .\%path%\*.exp
del /f/s/q .\%path%\*.iobj
del /f/s/q .\%path%\*.ipdb
del /f/s/q .\%path%\*.log
del /f/s/q .\%path%\*.pdb
del /f/s/q .\%path%\*.cache
del /f/s/q .\%path%\*.res
rd /s/q .\%path%\FictionNovelCore.tlog
rd /s/q .\%path%\res