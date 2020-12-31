BOOL Carfieldlee::SaveOBJ()
{
	ADODB::_ConnectionPtr       pConnection;
	ADODB::_RecordsetPtr        pRecordset;   //各个列的集合
	_variant_t RecordsAffected;

	CString strPath = _T("");;
	CString strFile = _T("波妞.mdb");
	CString DBName=_T("Provider=Microsoft.JET.OLEDB.4.0;Data source=");
	DBName=DBName+strPath+strFile;
	pConnection.CreateInstance(__uuidof(ADODB::Connection));
	pRecordset.CreateInstance(__uuidof(ADODB::Recordset)); //为Recordset对象创建实例
	/******************连接数据库********************/
	try
	{
		pConnection->ConnectionTimeout = 8;
		//连接ACCESS
		pConnection->Open(_bstr_t(DBName),_T(""),_T(""),ADODB::adModeUnknown);
	}
	catch(_com_error e)///捕捉异常
	{
		strErrormessage.Format(_T("连接数据库失败!\r错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(strErrormessage);
		return ;
	} 

	CString strTableName = _T("模型");
	try
	{
		pRecordset->CursorLocation=ADODB::adUseClient;
		_bstr_t strCmd=_T("SELECT * FROM ") + strTableName;
		pRecordset->Open(strCmd,_variant_t((IDispatch*)pConnection,TRUE),
			ADODB::adOpenStatic,ADODB::adLockOptimistic,ADODB::adCmdText);
	}
	catch(_com_error &e)
	{
		strErrormessage.Format(_T("连接数据库表%s失败!\r错误信息:%s"),strTableName,e.ErrorMessage());
		M5MessageBox(NULL, strErrormessage);
		return ;
	}

	pRecordset->AddNew();
	pRecordset->PutCollect(_T("经度"), 115 );
	pRecordset->PutCollect(_T("纬度"), 30 );

	CMemFile memFile;
	CArchive ar(&memFile, CArchive::store);
	m_pCarfielldee->Serialize(ar); //******************************* 需要保存的对象指针*********************/
	ar.Close();

	// 取得内存文件的长度
	long lSize = memFile.GetLength();
	LPBYTE lpInfo = memFile.Detach();

	VARIANT			varBLOB;
	SAFEARRAY		*psa;
	SAFEARRAYBOUND	rgsabound[1];

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = dwSize;

	// 创建safearray对象存取流数据
	psa = SafeArrayCreateVector( VT_UI1, 0, lSize);
	// 指向字节数组的指针
	unsigned char *pData = NULL;
	// 取得一个 safe array的指针. 锁定数组.
	SafeArrayAccessData( psa, (void**)&pData );
	// 拷贝内存文件到 safearray
	memcpy( pData, lpInfo, lSize );
	// 清理缓冲区
	delete lpInfo;
	// 锁定对 safearray的访问
	SafeArrayUnaccessData(psa);

	varBLOB.vt = VT_ARRAY | VT_UI1;
	varBLOB.parray = psa;
	pRecordset->GetFields()->GetItem(_variant_t("空间信息"))->AppendChunk(varBLOB);	
	pRecordset->Update(); 

	if(pConnection->State)
		pConnection->Close();
	pConnection.Release();

	if(pRecordset->State)
		pRecordset->Close();
	pRecordset=NULL;

	return TRUE;
}


BOOL Carfieldlee::ReadOBJ()
{
	ADODB::_ConnectionPtr       pConnection;
	ADODB::_RecordsetPtr        pRecordset;   //各个列的集合
	_variant_t RecordsAffected;
	CString strErrormessage, strCondition, strTableName;

	CString strPath = _T("");;
	CString strFile = _T("波妞.mdb");
	CString DBName=_T("Provider=Microsoft.JET.OLEDB.4.0;Data source=");
	DBName=DBName+strPath+strFile;
	pConnection.CreateInstance(__uuidof(ADODB::Connection));
	pRecordset.CreateInstance(__uuidof(ADODB::Recordset)); //为Recordset对象创建实例
	/******************连接数据库********************/
	try
	{
		pConnection->ConnectionTimeout = 8;
		//连接ACCESS
		pConnection->Open(_bstr_t(DBName),_T(""),_T(""),ADODB::adModeUnknown);
	}
	catch(_com_error e)///捕捉异常
	{
		strErrormessage.Format(_T("连接数据库失败!\r错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(strErrormessage);
		return ;
	} 

	strTableName = _T("模型");
	strCondition.Format(_T("WHERE ID=%d"), 3);
	try
	{
		_bstr_t strCmd=_T("SELECT * FROM ") + strTableName + _T(" ") + strCondition;
		pRecordset=pConnection->Execute(strCmd,&RecordsAffected,ADODB::adCmdText);
	}
	catch(_com_error &e)
	{
		strErrormessage.Format(_T("连接数据库表%s失败!\r错误信息:%s"),strTableName,e.ErrorMessage());
		AfxMessageBox(strErrormessage);
		return FALSE;
	}

	int nln = 1;
	try
	{
		while(!pRecordset->adoEOF)
		{
			//读出序列化进去的 空间信息 
			long lDataSize = pRecordset->GetFields()->GetItem(_variant_t("空间信息"))->ActualSize;
			if(lDataSize <= 0) 
			{
				strErrormessage.Format(_T("数据库 表-模型 中第%d行--空间信息--有误！  已经跳过！"),nln);
				AfxMessageBox(strErrormessage);
				pRecordset->MoveNext();
				nln++;
				continue;
			}

			_variant_t varBLOB;
			VariantInit (&varBLOB);

			varBLOB = pRecordset->GetFields()->GetItem(_variant_t("空间信息"))->GetChunk(lDataSize);
			if(varBLOB.vt == (VT_ARRAY | VT_UI1))
			{
				BYTE *pBuf = NULL;
				SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
				SafeArrayUnaccessData (varBLOB.parray);

				CMemFile memfile;
				memfile.Attach(pBuf,lDataSize);
				memfile.SeekToBegin();
				CArchive ar(&memfile, CArchive::load);

				m_pCarfielldee = new Carfieldlee;
				m_pCarfielldee->Serialize(ar); //*************************************需要赋值的指针****************************//

				ar.Close();
				memfile.Detach();
			}
			VariantClear(&varBLOB);

			pRecordset->MoveNext();
			nln++;  
		}

	}
	catch(_com_error &e)
	{
		strErrormessage.Format(_T("读数据库表%s失败!\r错误信息:%s"),strTableName,e.ErrorMessage());
		AfxMessageBox(strErrormessage);
		return FALSE;
	}

	if(pConnection->State)
		pConnection->Close();
	pConnection.Release();

	if(pRecordset->State)
		pRecordset->Close();
	pRecordset=NULL;

	return TRUE;
}