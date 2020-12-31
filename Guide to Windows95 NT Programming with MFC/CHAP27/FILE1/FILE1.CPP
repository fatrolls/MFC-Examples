///////////////////////////////////////////////////////////////////
// Module  : FILE1.CPP
//
// Purpose : A simple MFC console application that performs basic 
//           file operations.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 06-27-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"

CString IntToString(INT nNum);

void main()
{
   // Create a file
   CString strFile1 = "C:\\TEMP1.TXT";
   CFile file((LPCTSTR) strFile1, 
      CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);

   // Define a hard return for text file
   CString strNL;
   strNL.Format("\r\n"); 
   
   // Write some data to the file
   CString strBuf = "Some data" + strNL + "Some more data" + strNL;
   file.Write((void*)(LPCTSTR) strBuf, strBuf.GetLength());

   // Close the file
   file.Close();

   // Copy the file
   CString strFile2 = "C:\\TEMP2.TXT";
   ::CopyFile((LPCTSTR) strFile1, (LPCTSTR) strFile2, FALSE);

   // Move the first file to another drive
   ::MoveFileEx("C:\\TEMP1.TXT", "D:\\TEMP1.TXT", 
      MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);

   // Rename the second file
   ::MoveFile("C:\\TEMP2.TXT", "C:\\TEMP2A.TXT");

   // Copy and delete the file on D: drive
   ::CopyFile("D:\\TEMP1.TXT", "D:\\TEMP2.TXT", FALSE);
   ::DeleteFile("D:\\TEMP1.TXT");
}

///////////////////////////////////////////////////////////////////
// IntToString()

CString IntToString(INT nNum)
{
   char szTemp[10];
   
   _itoa(nNum, szTemp, 10); // convert int to string
   return (CString)szTemp;
}



