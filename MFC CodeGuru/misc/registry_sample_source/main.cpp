#include <windows.h>
#include "Registry.h"
#include <iostream.h>

// derive a class from CRegistry to demonstrate the RegistryTreeWalk()
// method.
class CMyReg : public CRegistry {
	public:
		virtual BOOL	OnValueHit(
							LPCTSTR Key,
							LPCTSTR ValueName,
							const CRegVal & Value,
							USHORT Depth
						) {
							cout << "Hit value on path \"" << Key
								 << "\": \"" << ValueName
								 << "\" (depth: " << Depth << ")"
								 << endl;
							return TRUE;	// continue walk
						}

		virtual BOOL	OnKeyHit( LPCTSTR Key, USHORT Depth ) {
							cout << "Hit key \"" << Key
								 << "\" (depth: " << Depth << ")"
								 << endl;
							return TRUE;	// continue walk
						}
};

int main( int, char ** )
{
	// Replace the path in this example with your favourite one.
	CMyReg reg;
	CRegVal regval;
	reg.RegistryTreeWalk(TEXT("Software\\Lemmy"));

	return 0;
}
