Attribute VB_Name = "Module1"
Private Declare Function RegQueryValueEx& Lib "advapi32.dll" Alias "RegQueryValueExA" _
(ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, _
lpType As Long, lpData As Any, lpcbData As Long)

'this function opens a reg key
Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" _
(ByVal hKey As Long, ByVal lpSubKey As String, _
ByVal ulOptions As Long, ByVal samDesired As Long, _
phkResult As Long) As Long

'need decl. to close open key
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey _
As Long) As Long

Public Const KEY_QUERY_VALUE = 1

Option Explicit

Public Function FindPath(ByVal strKey As String, ByVal strSubKeys As String, _
Optional ByVal strValueName As String) As String
'retrieves a particular registry key value
'   note that it only works for string data for now
    
    'return helpfile path if successful, otherwise returns zero-length string
    Dim strTemp As String
    Dim lngRetVal As Long 'return value of function call
    Dim lngKey As Long  'type of key to be queried
    Dim lnghandle As Long
    Dim lngType As Long  'stores returned type of data being returned
    Dim strData As String 'buffer to store returned data
    Dim lngDataSize As Long  'contains size of buffer (strData) to store returned data
    Dim i As Long  'counter var
    Dim strTemp2 As String  'hold one char ata time
    
    'make room for returned string value
    
    
    'determine which key is being queried
    Select Case strKey
        Case "HKEY_CLASSES_ROOT"
            lngKey = &H80000000
        Case "HKEY_CURRENT_CONFIG"
            lngKey = &H80000005
        Case "HKEY_CURRENT_USER"
            lngKey = &H80000001
        Case "HKEY_DYN_DATA"
            lngKey = &H80000006
        Case "HKEY_LOCAL_MACHINE"
            lngKey = &H80000002
        Case "HKEY_PERFORMANCE_DATA"
            lngKey = &H80000004
        Case "HKEY_USERS"
            lngKey = &H80000003
        Case Else
            FindPath = ""
            Exit Function
    
    End Select
    
    lngRetVal = RegOpenKeyEx(lngKey, strSubKeys, 0&, KEY_QUERY_VALUE, lnghandle)
    If lngRetVal Then
        FindPath = ""
        Exit Function
    End If
    
    'now retrieve info from open key
    strData = Space(255)
    'lngRetVal = RegQueryValueEx(lnghandle, strValueName, 0, lngType, strData, 32)
    lngRetVal = RegQueryValueEx(lnghandle, strValueName, 0, lngType, ByVal strData, 255)
    'check for errors
    If lngRetVal Then
        FindPath = ""
        Exit Function
    End If
    
    'now close opened key
    lngRetVal = RegCloseKey(lnghandle)
    If lngRetVal Then
        FindPath = ""
        Exit Function
    End If
           
    'trim up resulting string
    For i = 1 To Len(strData)
        strTemp2 = Mid(strData, i, 1)
        If Asc(strTemp2) = 0 Then
            strData = Mid(strData, 1, i - 2)
            Exit For
        End If
    Next
        
    FindPath = strData
           
End Function
