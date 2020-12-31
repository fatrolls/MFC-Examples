//
// Iface.cpp
// To compile, use: cl Iface.cpp
//
#include <iostream.h>
#include <objbase.h>   // Define interface.

void trace(const char* pMsg) {cout << pMsg << endl ;}

// Abstract interfaces
interface IX
{
	virtual void __stdcall Fx1() = 0 ;
	virtual void __stdcall Fx2() = 0 ;
} ;

interface IY
{
	virtual void __stdcall Fy1() = 0 ;
	virtual void __stdcall Fy2() = 0 ;
} ;

// Interface implementation
class CA : public IX, 
           public IY
{
public:

	// Implement interface IX.
	virtual void __stdcall Fx1() {cout << "CA::Fx1" << endl ;}
	virtual void __stdcall Fx2() {cout << "CA::Fx2" << endl ;}

	// Implement interface IY.
	virtual void __stdcall Fy1() {cout << "CA::Fy1" << endl ;}
	virtual void __stdcall Fy2() {cout << "CA::Fy2" << endl ;}

} ;


// Client
int main()
{
	trace("Client: Create an instance of the component.") ;
	CA* pA = new CA ;

	// Get an IX pointer.
	IX* pIX = pA ;

	trace("Client: Use the IX interface.") ;
	pIX->Fx1() ;
	pIX->Fx2() ;

	// Get an IY pointer.
	IY* pIY = pA ;

	trace("Client: Use the IY interface.") ;
	pIY->Fy1() ;
	pIY->Fy2() ;

	trace("Client: Delete the component.") ;
	delete pA ;

	return 0 ;
}
