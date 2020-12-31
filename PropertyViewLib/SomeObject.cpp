// SomeObject0.cpp: implementation of the SomeObject0 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SomeObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SomeObject0::SomeObject0()
{
	m_dDouble      = 123.5678;
	m_fFloat       = 234.567f;
	m_nInt         = 345;
	m_uInt         = 0xDEADBEEF;
	m_uChar        = 200;
	m_bBool           = true;

	m_dAngle          = 123.123; 
	m_cColor          = RGB(255,0,0);
	m_sName           = "Robin Hood";
	m_nCombo          = 0;
	m_sTextblock      = "this\nis\na\nTextblock";
	m_sReadOnlyString = "Cannot be changed";

	m_nCentimeters    = 100;

	m_dLargeNumber    = 12345678.12345;

	m_bSizeEnabled    = true;
	m_dWidth          = 12;
	m_dHeight         = 4;

	m_cNewColor = RGB( 255 , 200 , 100 );

	m_dMultiDouble1 = 4.1;
	m_dMultiDouble2 = 5.2;
	m_dMultiDouble3 = 6.3;
	m_dMultiDouble4 = 7.4;

}

SomeObject0::~SomeObject0()
{
}

void SomeObject0::GetProperties( EPropList& PropList )
{
	PropList.AddTab("General");

	//----------//
	// numerics //
	//----------//

//	PropList.AddPropSeparator( this , "Numerics types" );
	PropList.AddPropDouble( this , "double"        , &m_dDouble )->SetComment("Standard numeric property of type 'double'.");
	PropList.AddPropFloat ( this , "float"         , &m_fFloat  )->SetComment("Standard numeric property of type 'float'.");
	PropList.AddPropInt   ( this , "int"           , &m_nInt    )->SetComment("Standard numeric property of type 'int'. All integer types char, short and int are supported in signed or unsigned style. Use SetType() to set bytewidth and sign state of the integer property in question.");
	PropList.AddPropInt   ( this , "unsigned int"  , &m_uInt    )->SetType(4,false)->SetComment("An example of an 'unsigned int' property. This is infact an integer property with bytewidth=4 and signedflag=false. All numeric types support hex values, type 0xA0000000 to verify unsigned nature of this property.");
	PropList.AddPropInt   ( this , "unsigned char" , &m_uChar   )->SetType(1,false)->SetComment("Integer property with bytewidth=1 and signedflag=false.");

	//--------------//
	// simple types //
	//--------------//

//	PropList.AddPropSeparator( this , "Simple types" );
	PropList.AddPropCheck ( this , "bool"             , &m_bBool  )->SetComment("Standard boolean type checkbox, pointing to a 'bool' type member.");
	PropList.AddPropColor ( this , "Color"            , &m_cColor )->SetComment("A color property pointing to a 'COLORREF' member. Enter red, green and blue values separated by commas or spaces, or use button to pick color from standard color selection dialog.");
	PropList.AddPropString( this , "Name"             , &m_sName  )->SetComment("String property pointing to a 'CString' type member.");
	PropList.AddPropString( this , "Read only string" , &m_sReadOnlyString , false  )->SetComment("Read only string property. All properties can be readonly. Usually always like this, or change state dynamically.");
	PropList.AddPropCombo(  this , "Combo" , &m_nCombo )
	->AddString("Choise 0")
	->AddString("Choise 1")
	->AddString("Choise 2")
	->AddString("Choise 3")
	->AddSeparator()
	->AddString("Choise 4")
	->SetComment("Combobox property pointing to an 'int' member. The integer will hold the index of currently selected item, or another userdefined value specified when adding items. Items in the combo list can be separated without affecting the int index.");

	//-------------------------//
	// numeric property tricks //
	//-------------------------//

//	PropList.AddPropSeparator( this , "Numeric tricks" );
	PropList.AddPropDouble( this , "Angle"           , &m_dAngle , "deg" , 0 , 360 )->SetComment("Some 'double' property with unit suffix and range restrictions. Only values [0..360] are allowed for this 'double' type property. Values out of range will be ignored.");
	PropList.AddPropInt   ( this , "A (centimeters)" , &m_nCentimeters , "cm" )->SetComment("Some member, say 'A', stored in memory as centimeters.");
	PropList.AddPropInt   ( this , "A (meters)"      , &m_nCentimeters , "m"  )->SetScale(0.01)->SetComment("Member 'A' stored in memory as centimeters, but shown in gui as meters. All numeric properties can be 'scaled to gui', in this case from cm to m by a scale value of 0.01.");
	PropList.AddPropDouble( this , "Thousands"       , &m_dLargeNumber )->SetStyle(EIconTextButtonProperty::THOUSANDS)->SetComment("It's possibly to put thousand separator style to numeric properties like this.");

	//-------------------------------//
	// testing indent sub properties //
	//-------------------------------//

	PropList.AddPropCheck ( this , "Size"         , &m_bSizeEnabled )->SetComment("Sub properties are easily inserted. All property types can have indent children like this.");
	PropList.StepIndentIn();
	PropList.AddPropDouble( this , "Width"        , &m_dWidth  )->SetComment("This property toggles read only dynamically in the IsPropertyEnabled() function of the property host.");
	PropList.AddPropDouble( this , "Height"       , &m_dHeight )->SetComment("Read only state is determined by the property host in IsPropertyEnabled().");
	PropList.AddPropDouble( this , "Aspect (W/H)" , NULL       )->SetScale( &m_dWidth , &m_dHeight )->SetComment("This null double outputs originally to 1. Address of multiplier and divider doubles scales gui output, in this case the width and height fields. The property is null, and therefore read only.");
	PropList.StepIndentOut();

	//--------------//
	// advanced tab //
	//--------------//

	PropList.AddTab("Advanced");

	EPropertyMultiDouble* pMD = new EPropertyMultiDouble(this,"MultiDouble");
	pMD->AppendSubject( this , &m_dMultiDouble1 );
	pMD->AppendSubject( this , &m_dMultiDouble2 );
	pMD->AppendSubject( this , &m_dMultiDouble3 );
	pMD->AppendSubject( this , &m_dMultiDouble4 );
	PropList.AddProperty( pMD )->SetComment("This points to a list of 'double' instances and prints their range as output, or their shared value if they are all the same. Enter a new value in thie field to set all instances to that value.");

	PropList.StepIndentIn();
	PropList.AddPropDouble( this , "Double 1" , &m_dMultiDouble1 )->SetComment("One of the doubles being watched by the multidouble property.");
	PropList.AddPropDouble( this , "Double 2" , &m_dMultiDouble2 )->SetComment("One of the doubles being watched by the multidouble property.");
	PropList.AddPropDouble( this , "Double 3" , &m_dMultiDouble3 )->SetComment("One of the doubles being watched by the multidouble property.");
	PropList.AddPropDouble( this , "Double 4" , &m_dMultiDouble4 )->SetComment("One of the doubles being watched by the multidouble property.");
	PropList.StepIndentOut();

	PropList.AddPropColor ( this , "Color" , &m_cNewColor , false )->SetComment("A color property that will have each individual channel changed in following sub properties.");
	PropList.StepIndentIn();
	PropList.AddPropInt   ( this , "Red"   , ((char*)&m_cNewColor) + 0 )->SetType( 1 , false )->SetComment("An 'unsigned char' property pointing to the red byte in the 'COLORREF' instance above.");
	PropList.AddPropInt   ( this , "Green" , ((char*)&m_cNewColor) + 1 )->SetType( 1 , false )->SetComment("An 'unsigned char' property pointing to the green byte in the 'COLORREF' instance above.");
	PropList.AddPropInt   ( this , "Blue"  , ((char*)&m_cNewColor) + 2 )->SetType( 1 , false )->SetComment("An 'unsigned char' property pointing to the blue byte in the 'COLORREF' instance above.");
	PropList.StepIndentOut();

	//------------------------------//
	// comment of the object itself //
	//------------------------------//

	PropList.SetComment("Implementing the IPropertyHost interface enables an object to be represented in the property control. Call SetPropertyHost() parsing an object implementing this interface, and the control will immediately call GetProperties() on the host parsed in.");
}

bool SomeObject0::PropertyChanging( const void* pProperty , void* pNewValue )
{
	bool bChangeOK = true;
	return bChangeOK;
}

bool SomeObject0::IsPropertyEnabled( const void* pProperty )
{
	bool bEnabled = true;

	if( pProperty==&m_dWidth || pProperty==&m_dHeight )
	{
		bEnabled = m_bSizeEnabled;
	}

	return bEnabled;
}

//int SomeObject0::GetTreeIcon()
//{
//	return 1;
//}
//
//CString SomeObject0::GetTreeLabel()
//{
//	CString s;
//	s.Format("SomeObject0 (%s)" , m_sName );
//	return s;
//
//}
//
//void SomeObject0::GetTreeChildren( IHostList* pList )
//{
//	pList->Add( &m_Child0 );
//	pList->Add( &m_Child1 );
//	pList->Add( &m_Child2 );
//
//	for( int i=0 ; i<m_vObjects.size() ; i++ )
//	{
//		pList->Add( m_vObjects[i] );
//	}
//}
//
//void SomeObject0::GetTreeContextMenu( EContextMenu* pMenu )
//{
//	pMenu->AddCommand( "Add Node" , 1 , false );
//}

//bool SomeObject0::OnTreeContextCommand( int nCommand )
//{
//	bool bTreeChange = false;
//
//	if( nCommand==1 )
//	{
//		SomeObject0* pSO = new SomeObject0();
//		m_vObjects.push_back(pSO);
//		bTreeChange = true;
//	}
//
//	return bTreeChange;
//}

SomeObject1::SomeObject1()
{
	m_d00 = 1;
	m_d01 = 2;
	m_d02 = 3;
	m_d03 = 4;
	m_d10 = 5;
	m_d11 = 6;
	m_d12 = 7;
	m_d13 = 8;

	m_pDoubles = new double[32];

	for( int i=0 ; i<32 ; i++ )
	{
		m_pDoubles[i] = i;
	}
}

SomeObject1::~SomeObject1()
{
	delete m_pDoubles;
}

void SomeObject1::GetProperties( EPropList& PropList )
{
	PropList.AddTab("Tab 0");
	PropList.AddPropDouble( this , "Double 00" , &m_d00 );
	PropList.AddPropDouble( this , "Double 01" , &m_d01 );
	PropList.AddPropDouble( this , "Double 02" , &m_d02 );
	PropList.AddPropDouble( this , "Double 03" , &m_d03 );
	PropList.AddTab("Tab 1");
	PropList.AddPropDouble( this , "Double 10" , &m_d10 );
	PropList.AddPropDouble( this , "Double 11" , &m_d11 );
	PropList.AddPropDouble( this , "Double 12" , &m_d12 );
	PropList.AddPropDouble( this , "Double 13" , &m_d13 );
	PropList.AddTab("Tab 2");

	CString s;
	
	for( int i=0 ; i<32 ; i++ )
	{
		s.Format("Double %d",i);
		PropList.AddPropDouble( this , s , &m_pDoubles[i] );
	}
}


/*
ENoteProperty::ENoteProperty( IPropertyHost* pHost , const CString& sName , CString* pProperty ) : EPropertyTextblock( pHost , sName , pProperty )
{
}

int ENoteProperty::GetHeight()
{
	return 60;
}

void ENoteProperty::Draw( CDC* pDC ,  EPropListCtrl* pView , const CRect& r )
{
	EIconTextButtonProperty::Draw(pDC,pView,r);	//this will fill the bg

	CString s = *((CString*)m_pProperty);

	CRect rr = r;

	pDC->DrawText( s , rr , DT_LEFT );

}

int ENoteProperty::GetPreferedWidth( CDC* pDC )
{
	return EPropertyTextblock::GetPreferedWidth(pDC);
}
*/