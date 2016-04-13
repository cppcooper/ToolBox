#pragma once

#include "../../../tools_logger.h"
#include "../STL.h"

class Asset_Storage;
class Asset_Loader;

namespace GameAssets
{
	class GameAsset;
	extern logger::LogStream LogLine( logger::LogLevel level );

	/* Asset Factory Base Class
	Defines factory interface
	*/
	class Factory
	{
	protected:
		using uint = unsigned int;
		Factory(){}

	public:
		virtual GameAsset* Create( uint N = 1 ) = 0;
		//TODO: virtual bool Destroy( GameAsset* p ) = 0;
		virtual uint Get_TypeID() = 0;
		virtual std::string& TypeExtensions() = 0;
		virtual std::string& RecordExtension() = 0;
		virtual bool IsFactoryType( GameAsset* p ) = 0;
	};
	
	struct Storage_Data
	{
		GameAsset* allocation = nullptr;
		unsigned int index = 0;
		unsigned int length = 0;
		unsigned int bytes = 0;
	};
	
	/* Asset Base Class
	Defines asset interface
	*/
	class GameAsset
	{
	protected:
		using uint = unsigned int;
		
#define TYPE_ID_IMPL(TYPE)																				\
	unsigned int TYPE::TypeID()	{																		\
		static unsigned int id = Asset_Factory<TYPE>::Instance().Get_TypeID();	\
		return id;																										\
			}

	public:
		virtual ~GameAsset(){}
		virtual uint TypeID() = 0;
		virtual void Load( std::string filename ) = 0;
		virtual void Reset() = 0;
		const Storage_Data& GetStorageData() const { return storage; }
		void SetStorageData( const Storage_Data& data ) { storage = data; }
		
	protected:
		Storage_Data storage;
	};
}

