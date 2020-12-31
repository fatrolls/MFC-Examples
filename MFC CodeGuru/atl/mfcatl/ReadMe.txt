This code is a very basic sample of "adding" ATL to the existing
MFC project. I'm getting asked about MFC+ATL very often. Hope people
find it useful.
Contains VB(5.0) client and OCX(VC++5.0) that has
MFC control and ATL In-Proc server.
The way I did it is straightforward: Wizards generated 2 projects, MFC(Control) and ATL(In-Proc server) and essentially I just copied ATL code into MFC and used
IDL file instead of ODL.

Daniel Ilkanayev
ilkanayev@worldnet.att.net

