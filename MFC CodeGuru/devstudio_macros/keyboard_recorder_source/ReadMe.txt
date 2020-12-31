-------------------------------------------------------------
KbdMac - VC4.2 style keyboard macro recorder for DevStudio 97
-------------------------------------------------------------

Although the new VBScript support in DevStudio is excellent, I 
often miss the ability to record a quick keystroke macro like 
you could in VC4.2. KbdMac is an add-in for Developer Studio
that emulates that old VC4.2 functionality.

KbdMac works by using the Journalling Hook functionality, in a
similar fashion to the old Windows 3.1 Recorder application, but 
only keystrokes in the current instance of DevStudio are recorded.

Compile the project in Visual C++ (Win32 Release MinDependency),
and install the resulting KbdMac.dll by selecting Customize from
the Tools Menu and browsing for the DLL on the 'Add-ins and Macro
files' tab. The add-in should appear as 'KMAddIn Class' in the list
of active add-ins. Once installed a new toolbar should appear with
3 buttons for record/stop/play, that operate in a similar way to the
old VC4.2 ones.

Darren Richards.

Feedback, suggestions, etc. to :
darrenr@gissing-consulting.co.uk






