:: batch usage: https://ss64.com/nt/
:: Command Line arguments (Parameters): https://ss64.com/nt/syntax-args.html
@echo off
cd /d %~dp0
:: /r Loop through files (Recurse subfolders)
:: %~dp1 Expand %1 to a drive letter and path only
:: %~n1 Expand %1 to a file Name without file extension or path - MyFile 
:: or if only a path is present, with no trailing backslash, the last folder in that path.
for /r %%i in (*.jpg, *.png) do ( cwebp %%i -o %%~dpi%%~ni.webp )