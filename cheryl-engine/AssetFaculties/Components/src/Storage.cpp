#include "../Storage.h"
#include "../../InterAccess.h"

Asset_Storage::Asset_Storage()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Storage Initialized.";
}

Asset_Storage::~Asset_Storage()
{
	for ( auto ptr : Address_Table )
	{
		m_Log->Line( _DEBUG1 ) << "Delete Pointer"
			<< newl << "Address: " << ptr;
		delete[] ptr;
	}
	m_Log->Line( _INFO ) << "Asset Storage Deinitialized.";
}

void Asset_Storage::Update()
{

}