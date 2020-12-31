Readme.Txt
==========
Stored Procedure Class Wizard (SPCW) is a development tool that can be
used exclusively to generate class files (.cpp and .h) derived from MFC's
CRecordset for stored procedures. 

Note that running SPCW against MS SQL Server production databases is
NOT recommended.

Following are the steps for generating class files:

Step 1:
=======
Choose <Connect> from the <File> menu.

Step 2:
=======
Select the procedure name for which you want to generate class files.

Microsoft SQL Server specific:

For procedures that return result set columns, choose <Execute Procedure>
from the <File> menu before generating the class files.

Step 3:
=======
Choose <Generate Class> from the <File> menu to generate .cpp and .h
recordset files.

Whenever you add/modify a procedure, choose <Refresh> from the <View>
menu and then repeat step 3 (steps 2 & 3 in the case of MS SQL Server).

To connect to another data source, first disconnect the current connection
and then connect.

Add the following lines to StdAfx.h:

#include <afxdb.h> // MFC database classes

#define ODBC_DSN_INFO	_T("ODBC;DSN=<Data_Source_Name>") 







