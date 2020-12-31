========================================================================
       IMPORTANT INFORMATION
========================================================================
I developed this program to easily track the time I spend on developing
various projects. Now it is a nice starting point for developing you own
taskbar app (see reuseability information below)

To use it, you probably want to change the included ini-file:

[Projekte]
nAktiv=1                                ; thats the active project number
Anzahl=2                                ; thats the number of projects
Projekt1=Odor-Control                   ; the tooltip for project 1
Datei1=E:\Entwicklung\Odor\Odor.zeiten  ; the time-log-file for project 1
Projekt2=Taskbar                        ; the tooltip for project 2
Datei2=c:\temp\taskbar.zeiten           ; the time-log-file for project 2

You may add as many projects as you like, but don't ask me what happens
when you have added too much projects that the menu fills the entire sreen.
Who wants to work on so many projects ;-)

Don't bother about the german strings in this project, I'm sure you'll figure
out what they mean, its obvious.

If not, go to http://www.leo.org/cgi-bin/dict-search this is a good & quick
german <-> english dictonary. (Hans Wedemeyer would have been happy if I would
have entered this link before...)

========================================================================
       REUSEABILITY INFORMATION 1
========================================================================
This project shows how to create an taskbar app, like the volume control
placed in the taskbar notification area.

You may use this code as FREEWARE, as long as you drop me a message saying
what you took from my code and as long as you are using this code for non-
commercial applications.

========================================================================
       REUSEABILITY INFORMATION 2
========================================================================
The code for the class CMyListCrtl ist mainly based on the example provided 
by Codeguru Zafir Anjum at 
http://www.codeguru.com/listview/sel_row.htm
Thank you, Zafir. I extended the code so that you can display one of two
images in the subitems. This is done by setting their text to 0]|[ or 1]|[.


You can contact me via email: 

blenkers@anachem.ruhr-uni-bochum.de

Hope to "see" you!

