#ifndef _ASSETPOOL_H
#define _ASSETPOOL_H

#include "AssetAbstract.h"
#include "InterAccess.h"
#include "Storage.h"
#include "Factory.h"
#include "STL.h"
using namespace GameAssets;

class Asset_Pool
{
	using uint = unsigned int;
	using typePool = std::multimap < uint, GameAsset* > ;
	using assetPool = std::unordered_map < uint, typePool > ;
private:

protected:
	std::unordered_map<uint, std::multimap<uint, GameAsset*>> Object_Pools;

public:
	void Update();

	template<class T>
	T* Get( uint N = 1 )
	{
		T* ptr = nullptr;
		uint id = Asset_Factory<T>::Instance().Get_TypeID();
		if ( !Object_Pools.empty() )
		{
			assetPool::iterator PoolPool_it = Object_Pools.find( id );
			if ( PoolPool_it != Object_Pools.end() )
			{
				typePool& TypePool = PoolPool_it->second;
				typePool::iterator pool_it = TypePool.lower_bound( N );
				if ( pool_it != TypePool.end() )
				{
					uint remainder = pool_it->first - N;
					ptr = (T*)pool_it->second;
					TypePool.erase( pool_it );
					if ( remainder > 0 )
					{
						TypePool.emplace( remainder, &ptr[N] );
					}
				}
				else
				{
					ptr = Asset_Faculties::Instance().Allocator->Allocate<T>( N );
				}
			}
		}
		else
		{
			//Create an empty object pool for the array to be returned to later
			std::multimap<uint, GameAsset*> Object_Pool;
			Object_Pools.emplace( id, Object_Pool );
		}
		return ptr;
	}

	void Return( GameAsset* ptr, uint N = 1 )
	{
		unsigned int id = ptr->TypeID();
		assetPool::iterator TPool_it = Object_Pools.find( id );
		assert( TPool_it != Object_Pools.end() );
		TPool_it->second.emplace( N, ptr );
	}

};

#endif