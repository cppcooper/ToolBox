#include "../Pool.h"

Object_Pool::Object_Pool()
{
	m_Log = &Object_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Pool Initialized.";
}

Object_Pool::~Object_Pool()
{
	m_Log->Line( _INFO ) << "Asset Pool Deinitialized.";
}

void Object_Pool::Update()
{

}

void Object_Pool::Return( GameAssets::ManagedObject* ptr, uint N )
{
	unsigned int id = ptr->TypeID();
	m_Log->Line( _INFO ) << "Object_Pool::Return()";
	m_Log->Line( _DEBUG1 ) << "Returning Object(s)"
		<< newl << "Type ID:" << id
		<< newl << "Address: " << ptr
		<< newl << "Array Elements: " << N;
	AssetPool::iterator TPool_it = m_AssetPool.find( id );
	assert( TPool_it != m_AssetPool.end() );
	TPool_it->second.emplace( N, ptr );

}