#ifndef _ASSETSTORAGE_H
#define _ASSETSTORAGE_H

#include "AssetAbstract.h"
#include "STL.h"
using namespace GameAssets;

class Asset_Storage
{
	using uint = unsigned int;
protected:
	std::set<GameAsset*> Address_Table;

public:
	~Asset_Storage();
	void Update();

	template<class T>
	T* Allocate( uint N = 1 )
	{
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
			Address_Table.emplace( p );
			return (T*)p;
		}
		return nullptr;
	}

	template<class T>
	void Deallocate( T* ptr )
	{
		std::set<GameAsset*>::iterator it = Address_Table.find( (GameAsset*)ptr );
		if ( it != Address_Table.end() && *it == ptr )
		{
			delete ptr;
			Address_Table.erase( it );
		}
	}

	template<class T>
	bool Find( T* ptr )
	{
		if ( Address_Table.empty() )
			return false;

		GameAsset* p = ptr->storage.allocation;
		std::set<GameAsset*>::iterator it = Address_Table.lower_bound( (GameAsset*)ptr );
		if ( it == Address_Table.end() )
			it = std::prev( it );

		if ( *it != p )
		{
			if ( it != Address_Table.begin() )
			{
				it = std::prev( it );
			}
			else
			{
				return false;
			}
		}

		return ( *it == p && ( *it )->TypeID() == p->TypeID() );
	}
};

#endif