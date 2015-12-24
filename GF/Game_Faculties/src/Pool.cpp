#include "../Pool.h"

Asset_Pool::Asset_Pool()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	m_Log->Line( INFO ) << "Asset Pool Initialized.";
}

Asset_Pool::~Asset_Pool()
{
	m_Log->Line( INFO ) << "Asset Pool Deinitialized.";
}

void Asset_Pool::Update()
{

}