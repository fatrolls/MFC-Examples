HOOK is a strange thing in MS Windows family. Nowadays it is very dangerous to have Windows 95 and Windows NT for usage of the public computer cluster. 

Since all the Windows Operating Systems have " hook " drawback in nature, someone think this is a power feature though, chances are more people using Windows could have their password easily stolen no matter they are logging onto network or logging onto FTP or Mail Server.

I design a little code to demonstrate this usage.

My program is devided into two parts: 
hookDLL ---- the DLL I am going to insert into each thread I am monitoring on.
SKDemo  ---- the main program I am using DLL to LISTEN other's password as well as other                                             things goes into that program I am monitoring on.

The hookDLL, while been inserted into the hooked thread's address space, get called whenever the hooked thread called GetMessage or PeekMessage to retrive message from its message queue. It checks to see whether this message is targeting to the window we want to monitor, if so, save the message information, if not just let them go.

All you need is put the hookDLL.dll and SKDemo.exe to the same directory so SKDemo.exe can find hookDLL.dll and load it. After you start the SKDemo.exe, you will find a dialog, and then you may right click the mouse button and the cursor will turn into eyes, hold on the mouse right button and move mouse to other windows, you will find the edit control in dialog change the content. For example, when you decide to monitor the telnet program, you will right click mouse and move to telnet and then you will find "TelnetWClass" in edit control.
That is it! you click the begin hook button, and hide button, it will minimize itself to system tray and monitor telnet. All things going to telnet will be in a hidden file in
C:\passdata.txt.

Note: I have no time to wrap it into C++ code. If someone can do this, it will be great!

 