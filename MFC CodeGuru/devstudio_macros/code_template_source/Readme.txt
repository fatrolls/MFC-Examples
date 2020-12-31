
CodeTmpl - Code Template add-in for Visual C++ 5.0
--------------------------------------------------

* Introduction

The CodeTmpl add-in provides a simple mechanism for
inserting commonly used text blocks into your source
code. 

* Install

Build the CodeTmpl project using the Win32 MinDependency
build configuration, and copy the CodeTmpl.txt file into
your DevStudio\SharedIDE directory. Install the CodeTmpl
add-in by selecting Customize from the Tools Menu and 
browsing for the DLL on the 'Add-ins and Macro files'
tab. The add-in should appear as 'CTAddIn Class' in the
list of active add-ins. Once installed a new toolbar 
with a single button should appear for the CodeTmpl add-in.

* Overview

So what does this thing do for me you're wondering. Well the 
CodeTmpl.txt that you copied into your SharedIDE directory
contains chunks of source code delimited into named blocks. 
When you click on the CodeTmpl toolbar button you'll see those
same names appear on a popup menu, and should you select one,
then the appropriate chunk of source code will be glued into 
your current source code document at the insertion point.

* Configuration

Clearly my idea of useful bits of code is probably not yours,
so the CodeTmpl add-in is completely configurable, by simply
editting the CodeTmpl.txt file.

The format of the CodeTmpl.txt file is extremely simple. Basically
you paste your favourite blocks of source code into the file and put 
a pair of 'tags' at the beginning and end of each block. The tag
'#{' goes at the beginning of the block and the tag '#}' goes at the
end. The '#{' tag should be followed by a name for that block that will
appear on the popup menu. The tags must appear at the beginning of a new
line. Any text outside of the tags is ignored, with the exception of 
a string of 2 or more hashes which cause a separator to appear on the pop
up menu. 

For example :

#{Hello World - Console
#include <stdio.h>

int main()
{
    puts("Hello, World");    
}
#}

##########################

#{Hello World - GUI
#include <windows.h>

int PASCAL WinMain(HANDLE hInstance,
                   HANDLE hPrevInstance,
                   LPSTR lpszCommandLine,
                   int cmdShow)          
{
    MessageBox(NULL, "Hello, World", "Example", MB_OK);
}
#}

If your CodeTmpl.txt contained the above text then clicking the
CodeTmpl toolbar button would display a popup menu containing the
options 'Hello World - Console' and 'Hello World - GUI', with a 
separator between them. Selecting 'Hello World - Console' would
paste the text shown between the '#{' and '#}' tags into your
source.

* Tips

If you click the CodeTmpl toolbar button with the <Control> key down,
then the CodeTmpl.txt is re-read by the add-in before the popup
menu is displayed. This is to allow for on the fly configuration 
changes.

When editting the CodeTmpl.txt file in DevStudio, right hand mouse 
click the window in which it is open, select Properties from the
context menu and set Language to C/C++ from the property dialog.
This will give you color coding and make the tab key do what is
ought to.


* Contact me

I hope you will find this add-in useful either for its intended
purpose or just as a source code example. Either way feel free
to e-mail me with any comments, suggestions etc.

Darren Richards.

darrenr@gissing-consulting.co.uk



