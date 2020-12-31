@ECHO OFF

ECHO Cleaning...

del /S %1*.hpp%2%3%4
rem del /S %1*.map%2%3%4
del /S %1*.dcu%2%3%4
del /S %1*.bak%2%3%4
del /S %1*.gid%2%3%4
del /S %1*.fts%2%3%4
del /S %1*.~*%2%3%4
del /S %1*.dsk%2%3%4
del /S %1*.ddp%2%3%4
del /S %1*.bkm%2%3%4
del /S %1*_orig_?.*%2%3%4
del /S %1*.ressrc%2%3%4
del /S %1*.cesettings%2%3%4
del /S %1*.stat%2%3%4
del /S %1*.identcache%2%3%4
del /S %1*.local%2%3%4