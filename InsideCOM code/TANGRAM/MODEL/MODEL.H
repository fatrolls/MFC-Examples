#ifndef _CTangramModel_h__
#define _CTangramModel_h__

///////////////////////////////////////////////////////////
//
//
//	Model.h - Header file for the TangramModel component implementation
//
//
#include <ocidl.h> //For IConnectionPoint
#include "CUnknown.h"

#include "tantype.h"
#include "Model_I.h"

class CConnectionPoint ;

///////////////////////////////////////////////////////////
//
//	CTangramModel
//
class CTangramModel	:	public CUnknown,
						public ITangramModel,
						public ITangramTransform,
						public IConnectionPointContainer
{
public:	
	// Creation
	static HRESULT CreateInstance(	IUnknown* pOuterUnknown,
									CUnknown** ppNewComponent ) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface( const IID& iid, void** ppv) ;

	// ITangramModel Methods
	virtual HRESULT __stdcall GetNumberOfVertices(long* pNumVertices) ;
	virtual HRESULT __stdcall GetVertices(long cVertices, TangramPoint2d* points) ;
	virtual HRESULT __stdcall SetVertices(long cVertices, TangramPoint2d* points) ;

	// Transform Methods
	virtual HRESULT __stdcall Translate(double x, double y) ;
	virtual HRESULT __stdcall GetTranslation(TangramPoint2d* point);
	virtual HRESULT __stdcall Rotate(double fDegrees) ;
	virtual HRESULT __stdcall GetRotation( double* pRotation) ;

	// IConnectionPointContainer Methods
	virtual HRESULT __stdcall EnumConnectionPoints(IEnumConnectionPoints **ppEnum) ;
	virtual HRESULT __stdcall FindConnectionPoint(REFIID riid, IConnectionPoint **ppCP) ;

	// Construction
	CTangramModel(IUnknown* pOuterUnknown) ;

	// Destruction
	~CTangramModel() ;

// Internal Helper Functions
private:
	// Applies the current transform to the vertices.
	void applyTransform() ;

	// Fire the event.
	void FireEvent() ;

// Members variables.
private:
	// Untransformed vertices in model co-ordinates.
	TangramPoint2d* m_pVertices;

	// Transformed vertices in model co-ordintes.
	TangramPoint2d* m_pTransformVertices ;

	// Number of vertices in this model.
	int m_cVertices ;

	// Angle of rotation in degrees.
	double m_dDegrees ;

	// Cache for the cos of the angle of rotation.
	double m_cosDegrees; 

	// Cache for the sin of the angle of rotation.
	double m_sinDegrees; 

	// Point to translate the origin.
	TangramPoint2d m_ptdTranslate ;

	// Connection Point support
	CConnectionPoint* m_pConnectionPoint ;
};
#endif