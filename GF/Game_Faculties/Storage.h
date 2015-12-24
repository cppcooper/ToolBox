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
		m_Log->Line( INFO ) << "Allocating " << N * sizeof( T ) << " Bytes";
		if ( N > 0 )
		{
			GameAsset* p = new T[N]; //TODO: determine if this will cause run-time errors (GameAsset* vs T*)
			for ( uint i = 0; i < N; ++i )
			{
				p[i].storage.allocation = p;
				p[i].storage.length = N;
				p[i].storage.index = i;
				p[i].storage.bytes = N * sizeof( T );
			}
			assert( p == p[N - 1].storage.allocation ); //For the above TODO
			m_Log->Line( DEBUG1 ) << "Allocated " << p << " -- as " << N << " sized array";
			Address_Table.emplace( p );
			return (T*)p;
		}
		m_Log->Line( ERROR ) << "Allocation failed, returning nullptr";
		return nullptr;
	}

	template<class T>
	void Deallocate( T* ptr )
	{
		m_Log->Line( INFO ) << "Deallocating " << ptr;
		std::set<GameAsset*>::iterator it = Address_Table.find( (GameAsset*)ptr );
		if ( it != Address_Table.end() && *it == ptr )
		{
			delete ptr;
			Address_Table.erase( it );
			m_Log->Line( DEBUG1 ) << "Deallocated " << ptr;
		}
		else
		{
			m_Log->Line( ERROR ) << "Could not find pointer: " << ptr << " -- Deallocation FAILED";
		}
	}

	// Class T must be of GameAsset derivation
	template<class T>
	bool Find( T* ptr )
	{
		m_Log->Line( INFO ) << "Finding address " << ptr;
		if ( Address_Table.empty() )
		{
			m_Log->Line( ERROR ) << "Allocation Address Table is empty";
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
			m_Log->Line( DEBUG1 ) << "Found Address " << ptr << " under " << p << " in the Address Table";
			return true;
		}
		else
		{
			m_Log->Line( DEBUG1 ) << "Could not find the address " << ptr;
			return false;
		}
	}
};

#endif