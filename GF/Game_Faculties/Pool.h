#ifndef _ASSETPOOL_H
#define _ASSETPOOL_H

#include "AssetAbstract.h"
#include "InterAccess.h"
#include "Storage.h"
#include "Factory.h"
#include "STL.h"
	using namespace GameAssets;

	//TODO: implement minimum pool size
	class Asset_Pool
	{
		using uint = unsigned int;
		using ObjectPool = std::multimap < uint, GameAsset* >;
		using AssetPool = std::unordered_map < uint, ObjectPool > ;
	private:

	protected:
		//std::unordered_map<uint, std::multimap<uint, GameAsset*>> m_AssetPool
		AssetPool m_AssetPool;

	public:
		void Update();

		template<class T>
		T* Get( uint N = 1 )
		{
			T* ptr = nullptr;
			uint id = Asset_Factory<T>::Instance().Get_TypeID();

			AssetPool::iterator pool_it = m_AssetPool.find( id );
			if ( pool_it == m_AssetPool.end() )
			{
				//Create an empty object pool for the array to be returned to later
				std::multimap<uint, GameAsset*> Object_Pool;
				pool_it = m_AssetPool.emplace( id, Object_Pool ).first;
			}

			ObjectPool& objectPool = ( pool_it->second );
			ObjectPool::iterator it = objectPool.lower_bound( N );
			if ( it != objectPool.end() )
			{
				uint remainder = it->first - N;
				assert( Asset_Factory<T>::Instance().IsFactoryType( it->second ) );
				ptr = (T*)it->second;
				
				objectPool.erase( it );
				if ( remainder > 0 )
				{
					// ptr ranges from [0] to [N-1] (ie. N elements)
					// this means [N] to [N + remainder] onwards is our remainder
					objectPool.emplace( remainder, &ptr[N] );
				}
			}
			else
			{
				ptr = Asset_Faculties::Instance().Allocator->Allocate<T>( N );
			}
			return ptr;
		}

		void Return( GameAsset* ptr, uint N = 1 )
		{
			unsigned int id = ptr->TypeID();
			AssetPool::iterator TPool_it = m_AssetPool.find( id );
			assert( TPool_it != m_AssetPool.end() );
			TPool_it->second.emplace( N, ptr );
		}

	};

#endif