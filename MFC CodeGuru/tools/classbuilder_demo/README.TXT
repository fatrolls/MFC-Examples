ClassBuilder is an Object Oriented C++ front end to your compiler. It lets
you create, manipulate and navigate classes, class relations, class members
and class methods at a high level of abstraction trough a graphical user 
interface. Its rich feature list includes:
- Full code generation for the defined relations and their associated find 
  methods.
- Wizards to insert code, like iteration loops and navigation paths.
- Code syncronisation with compile environment.
- Full code generation for serializing the complete data model when used 
  together with MFC. (The tool is build with itself and uses this feature 
  to save to and read from file).
- Drag and drop support for many things. Adding a member to a class is just
  drag with holding down the Ctrl-key and then drop it on the desired class.
- Documentation generation in RTF and HTML. 
- etc.

This is a demo version, it may be freely distributed as is, without
modification. This demo version is limited to a 30 classes and 50 iterations of
code generation per project.
The author (Jimmy Venema) can be contacted via e-mail at venemaj@ce.philips.nl
or by phone at +31 40 2737871 (work), +31 492 549818 (home).

This release consists of the following files:

README.TXT
	This file.

ClassBuilder.exe 
	The executable, run this program, to start. 

ClassBuilder Getting Started.doc
	This includes a quick tour chapter, the document is still under
        construction.
	
Class.vss
Class.vst
	Visio stencil and template files to make class diagrams,
	which can be read in the ClassBuilder tool.

Template.rtf
	Template Rich Text Format file to use as template for the
	documentation is RTF format. It is used to derive the different
	styles which can be used, like heading1, heading2, ... etc. And as
	first part of the generated document.

Include\CB_CriticalMulti.h
Include\CB_CriticalMultiOwned.h
Include\CB_CriticalSection.h
Include\CB_CriticalSingle.h
Include\CB_CriticalSingleOwned.h
Include\CB_CriticalStaticMulti.h
Include\CB_CriticalStaticMultiOwned.h
Include\CB_CriticalUniqueValueTree.h
Include\CB_CriticalUniqueValueTreeOwned.h
Include\CB_CriticalValueTree.h
Include\CB_CriticalValueTreeOwned.h
Include\CB_IteratorMulti.h
Include\CB_IteratorStaticMulti.h
Include\CB_Multi.h
Include\CB_MultiOwned.h
Include\CB_Single.h
Include\CB_SingleOwned.h
Include\CB_StaticMulti.h
Include\CB_StaticMultiOwned.h
Include\CB_UniqueValueTree.h
Include\CB_UniqueValueTreeOwned.h
Include\CB_ValueTree.h
Include\CB_ValueTreeOwned.h
	Include files needed to compile the generated code.
