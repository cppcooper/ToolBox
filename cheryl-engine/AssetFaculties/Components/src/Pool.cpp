#include "../Pool.h"

Object_Pool::Object_Pool()
{
	m_Log = &Asset_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Pool Initialized.";
}

Object_Pool::~Object_Pool()
{
	m_Log->Line( _INFO ) << "Asset Pool Deinitialized.";
}

void Object_Pool::Update()
{

}