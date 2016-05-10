#pragma once

#include "../../tools_logger.h"
#include "STL.h"

class ManagedObject_Storage;
class Asset_Loader;

namespace GameAssets
{
	class ManagedObject;
	extern logger::LogStream LogLine( logger::LogLevel level );

	/* Asset Factory Base Class
	Defines factory interface
	*/
	class Factory
	{
	protected:
		Factory(){}

	public:
		virtual ManagedObject* Create( uint32_t N = 1 ) = 0;
		//TODO: virtual bool Destroy( ManagedObject* p ) = 0;
		virtual uint32_t Get_TypeID() = 0;
		virtual std::string& TypeExtensions() = 0;
		virtual std::string& RecordExtension() = 0;
		virtual bool IsFactoryType( ManagedObject* p ) = 0;
	};
	
	struct Storage_Data
	{
		ManagedObject* allocation = nullptr;
		unsigned int index = 0;
		unsigned int length = 0;
		unsigned int bytes = 0;
	};
	

	/* Game Object Base Class
	*/
	class ManagedObject
	{
	protected:
#define TYPE_ID_IMPL(TYPE) unsigned int TYPE::TypeID() { static unsigned int id = Object_Factory<TYPE>::Instance().Get_TypeID(); return id; }

#define TYPE_ID_IMPL_INLINE(TYPE) unsigned int TypeID() { static unsigned int id = Object_Factory<TYPE>::Instance().Get_TypeID(); return id; }

	public:
		virtual ~ManagedObject(){}
		virtual uint32_t TypeID() = 0;
		virtual void Reset() = 0;
		const Storage_Data& GetStorageData() const { return storage; }
		void SetStorageData( const Storage_Data& data ) { storage = data; }
		
	protected:
		Storage_Data storage;
	};


	/* Asset Base Class
	Defines asset interface
	*/
	class AssetObject : public ManagedObject
	{
	public:
		virtual void Load( std::string filename ) = 0;
	};
}

