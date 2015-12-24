#include "../Storage.h"
#include "../InterAccess.h"

Asset_Storage::Asset_Storage()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	m_Log->Line( INFO ) << "Asset Storage Initialized.";
}

Asset_Storage::~Asset_Storage()
{
	for ( auto ptr : Address_Table )
	{
		delete ptr;
	}
	m_Log->Line( INFO ) << "Asset Storage Deinitialized.";
}

void Asset_Storage::Update()
{

}