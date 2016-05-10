#include "../Storage.h"
#include "../../InterAccess.h"

Object_Storage::Object_Storage()
{
	m_Log = &Object_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Storage Initialized.";
}

Object_Storage::~Object_Storage()
{
	for ( auto ptr : Address_Table )
	{
		m_Log->Line( _DEBUG1 ) << "Delete Pointer"
			<< newl << "Address: " << ptr;
		delete[] ptr;
	}
	m_Log->Line( _INFO ) << "Asset Storage Deinitialized.";
}

void Object_Storage::Update()
{

}