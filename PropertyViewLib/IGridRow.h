//----------------------------------------------------------------------//
//                                                                      //
// Implement this interface if you want your class to be represented    //
// as a row in the property grid. By default, all properties of         //
// the class is listed in the grid.                                     //
//                                                                      //
//----------------------------------------------------------------------//

#ifndef IGRIDROW_H
#define IGRIDROW_H

#define UWM_ADD_GRID_ROW     (WM_APP + 1)
#define UWM_PROPERTY_CHANGED (WM_APP + 2)

#include "IPropertyHost.h"
#include "EPropList.h"			//implements IColumnList
#include "EGridCtrl.h"

class EGridCtrl;

class IGridRow : public IPropertyHost
{

public:

	EGridCtrl* m_pGridCtrl;

	IGridRow()
	{
		m_pGridCtrl = NULL;
	}

	//
	// List properties to be represented in each column
	//
	virtual void GetGridColumns(EPropList& PropList)
	{
		GetProperties(PropList);
	}
	
	//
	// The grid row can post property change messages to the ui
	// through here, possibly from another thread
	//
	void PostPropertyChanged( /*IGridRow* pGridRow ,*/ void* pProperty )
	{
		if( m_pGridCtrl != NULL )
		{
			m_pGridCtrl->PostMessage( UWM_PROPERTY_CHANGED , (unsigned int)pProperty , /*(long)pGridRow*/ 0 );
		}
	}

	void PostAddGridRow( IGridRow* pGridRow )
	{
		if( m_pGridCtrl != NULL )
		{
			m_pGridCtrl->PostMessage( UWM_ADD_GRID_ROW , (unsigned int)pGridRow , /*(long)pGridRow*/ 0 );
		}
	}

};

#endif