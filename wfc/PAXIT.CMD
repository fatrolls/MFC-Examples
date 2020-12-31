@echo off
"c:\program files\microsoft visual studio\vc98\bin\nmake" core
f:
cd \pax
del c:\temp\wfc.tar
pax -w -f //C/TEMP/WFC.TAR .
cd \wfc
"c:\program files\microsoft visual studio\vc98\bin\nmake" samples
f:
cd \pax
del c:\temp\sample.tar
pax -w -f //C/TEMP/SAMPLE.TAR .
cd \wfc
"c:\program files\microsoft visual studio\vc98\bin\nmake" clean
c:
cd \temp
del wfc.zip
zip -ex wfc wfc.tar
del sample.zip
zip -ex sample sample.tar
dir c:\temp\wfc.*
dir c:\temp\sample.*
