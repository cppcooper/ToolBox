#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"
#include "../AssetAbstract.h"
using namespace logger;

class Asset_Storage
{
	using uint = unsigned int;
private:
	logger::Log* m_Log;

protected:
	std::set<GameAssets::GameObject*> Address_Table;

public:
	Asset_Storage();
	~Asset_Storage();
	void Update();

	template<class T>
	T* Allocate( uint N = 1 )
	{
		m_Log->Line( _INFO ) << "Asset_Storage::Allocate()";
		if ( N > 0 )
		{
			T* ptr = new T[N];
			GameAssets::Storage_Data storage;
			storage.allocation = ptr;
			storage.length = N;
			storage.bytes = N * sizeof( T );
			for ( uint i = 0; i < N; ++i )
			{
				GameAssets::GameObject* p = &ptr[i];
				storage.index = i;
				p->SetStorageData( storage );
			}
			m_Log->Line( _DEBUG1 ) << "Memory Allocated"
				<< newl << "Address:" << ptr
				<< newl << "Elements: " << N
				<< newl << "Size: " << sizeof( T ) * N << " Bytes";
			Address_Table.emplace( (GameAssets::GameObject*)ptr );
			return ptr;
		}
		m_Log->Line( _ERROR ) << "ALLOCATION FAILED - Returns nullptr";
		//Likely should be an assert() or exit()
		return nullptr;
	}

	template<class T>
	void Deallocate( T* ptr )
	{
		m_Log->Line( _INFO ) << "Asset_Storage::Deallocate()";
		std::set<GameAssets::GameObject*>::iterator it = Address_Table.find( (GameAssets::GameObject*)ptr );
		if ( it != Address_Table.end() && *it == ptr )
		{
			delete ptr;
			Address_Table.erase( it );
			m_Log->Line( _DEBUG1 ) << "Deallocated: " << ptr;
		}
		else
		{
			m_Log->Line( _ERROR ) << "Pointer Not Found"
				<< newl << "Pointer: " << ptr;
		}
	}

	// Class T must be of GameObject derivation
	template<class T>
	bool Find( T* ptr )
	{
		m_Log->Line( _INFO ) << "Asset_Storage::Find()";
		if ( Address_Table.empty() )
		{
			m_Log->Line( _WARNING ) << "Allocation Address Table is empty\n";
			return false;
		}

		/* This pointer is not guaranteed to have been allocated by us, so it may not be a GameObject allocation data to view
		Additionally it may be an address in the middle of an array we allocated
		*/

		GameAssets::GameObject* p = ptr->storage.allocation;
		std::set<GameAssets::GameObject*>::iterator it = Address_Table.lower_bound( (GameAssets::GameObject*)ptr );
		if ( it == Address_Table.end() )
		{
			it = std::prev( it );
		}
		else if ( *it != p )
		{
			if ( it != Address_Table.begin() )
			{
				it = std::prev( it );
			}
		}

		if ( *it == p && ( *it )->TypeID() == p->TypeID() )
		{
			m_Log->Line( _DEBUG1 ) << "Found Address"
				<< newl << "Pointer: " << ptr
				<< newl << "Found Under: " << p;
			return true;
		}
		else
		{
			m_Log->Line( _WARNING ) << "Address Not Found"
				<< newl << "Pointer: " << ptr
				<< newl << "Allocation Pointer: " << p;
			return false;
		}
	}
};

