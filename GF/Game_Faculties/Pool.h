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
		logger::Log* m_Log;

	protected:
		//std::unordered_map<uint, std::multimap<uint, GameAsset*>> m_AssetPool
		AssetPool m_AssetPool;

	public:
		Asset_Pool();
		~Asset_Pool();
		void Update();

		template<class T>
		T* Get( uint N = 1 )
		{
			T* ptr = nullptr;
			uint id = Asset_Factory<T>::Instance().Get_TypeID();
			m_Log->Line( INFO ) << "Getting a Pool of size: " << N << " Pool id: " << id;

			AssetPool::iterator pool_it = m_AssetPool.find( id );
			if ( pool_it == m_AssetPool.end() )
			{
				//Create an empty object pool for the array to be returned to later
				std::multimap<uint, GameAsset*> Object_Pool;
				pool_it = m_AssetPool.emplace( id, Object_Pool ).first;
				m_Log->Line( DEBUG1 ) << "A pool of type id ('" << id << "') did not exist. So one was made.";
			}

			ObjectPool& objectPool = ( pool_it->second );
			ObjectPool::iterator it = objectPool.lower_bound( N );
			if ( it != objectPool.end() )
			{
				uint remainder = it->first - N;
				assert( Asset_Factory<T>::Instance().IsFactoryType( it->second ) );
				ptr = (T*)it->second;
				m_Log->Line( DEBUG1 ) << "An Object Pool with *at least* " << N << " elements has been found at: " << ptr;
				
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
				m_Log->Line( DEBUG1 ) << "An Object Pool with " << N << " elements cannot be found";
				ptr = Asset_Faculties::Instance().Allocator->Allocate<T>( N );
			}
			return ptr;
		}

		void Return( GameAsset* ptr, uint N = 1 )
		{
			unsigned int id = ptr->TypeID();
			m_Log->Line( INFO ) << "An Object Pool with " << N << " of type id: " << id << " is being returned.";
			AssetPool::iterator TPool_it = m_AssetPool.find( id );
			assert( TPool_it != m_AssetPool.end() );
			TPool_it->second.emplace( N, ptr );
		}

	};

#endif