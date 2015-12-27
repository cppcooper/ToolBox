#ifndef _ASSETSTORAGE_H
#define _ASSETSTORAGE_H

#include "AssetAbstract.h"
#include "STL.h"
#include <tools_logger.h>
using namespace GameAssets;
using namespace logger;

class Asset_Storage
{
	using uint = unsigned int;
private:
	logger::Log* m_Log;

protected:
	std::set<GameAsset*> Address_Table;

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
			T* ptr = new T[N]; //TODO: determine if this will cause run-time errors (GameAsset* vs T*)
			for ( uint i = 0; i < N; ++i )
			{
				GameAsset* p = &ptr[i];
				p->storage.allocation = ptr;
				p->storage.length = N;
				p->storage.index = i;
				p->storage.bytes = N * sizeof( T );
			}
			m_Log->Line( _DEBUG1 ) << "Memory Allocated"
				<< newl << "Address:" << ptr
				<< newl << "Elements: " << N
				<< newl << "Size: " << sizeof( T ) * N << " Bytes";
			Address_Table.emplace( (GameAsset*)ptr );
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
		std::set<GameAsset*>::iterator it = Address_Table.find( (GameAsset*)ptr );
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

	// Class T must be of GameAsset derivation
	template<class T>
	bool Find( T* ptr )
	{
		m_Log->Line( _INFO ) << "Asset_Storage::Find()";
		if ( Address_Table.empty() )
		{
			m_Log->Line( _WARNING ) << "Allocation Address Table is empty\n";
			return false;
		}

		/* This pointer is not guaranteed to have been allocated by us, so it may not be a GameAsset allocation data to view
		Additionally it may be an address in the middle of an array we allocated
		*/

		GameAsset* p = ptr->storage.allocation;
		std::set<GameAsset*>::iterator it = Address_Table.lower_bound( (GameAsset*)ptr );
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

#endif