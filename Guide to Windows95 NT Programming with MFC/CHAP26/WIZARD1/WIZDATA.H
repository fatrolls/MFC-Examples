///////////////////////////////////////////////////////////////////
// Module   : WIZDATA.H
//
// Purpose  : Definition of an application-specific data structure
//            used for the WIZARD1 program. 
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#ifndef __WIZDATA_H__
#define __WIZDATA_H__

// Sample data structure for holding wizard info
typedef struct tagSAMPLEWIZDATA
{
   CString  sFirstName;
   CString  sLastName;
   CString  sCompany;
   CString  sEmail;
   CString  sFood;
   CString  sCompiler;
}
SAMPLEWIZDATA;

#endif  // __WIZDATA_H__
