#ifndef _ASSETFACTORY_H
#define _ASSETFACTORY_H

#include <tools_logger.h>

#include "../STL.h"
#include "../InterAccess.h"

#include "AssetAbstract.h"
#include "Pool.h"

using namespace GameAssets;

template<class T>
class Asset_Factory : public Factory
{
private:
	logger::Log* m_Log;
	uint TID = 0;
	Asset_Factory(){
		Asset_Faculties::Instance().Factories.push_back( ( Factory* )this );
		TID = Asset_Faculties::Instance().Factories.size();
		m_Log = &Asset_Faculties::Instance().GetManagementLog();
		m_Log->Line( _INFO ) << "Factory Initialized #" << TID;
	}

	logger::LogStream gLog( logger::LogLevel level ){
		return m_Log->Line( level );
	}

public:
	~Asset_Factory(){
		m_Log->Line( _INFO ) << "Factory Deinitialized #" << TID;
	}

	static Asset_Factory<T>& Instance(){
		static Asset_Factory<T> instance;
		return instance;
	}

	GameAsset* Create( uint N = 1 ) final override {
		gLog( _INFO ) << "Factory #" << TID << " Creating Array with " << N << " elements.";
		return (GameAsset*)Asset_Faculties::Instance().Pool->Get<T>( N );
	}

	T* Cast( GameAsset* p ){
		if ( IsFactoryType( p ) ){
			return (T*)p;
		}
		else{
			return nullptr;
		}
	}

	std::string& TypeExtensions() final override {
		static std::string extensions = "";
		return extensions;
	}

	std::string& RecordExtension() final override {
		static std::string extension = "";
		return extension;
	}

	uint Get_TypeID() final override {
		return TID;
	}

	static uint TypeID(){
		return Instance().TID;
	}

	bool IsFactoryType( GameAsset* p ){
		assert( p != nullptr );
		gLog( _DEBUG1 ) << "Factory ID: " << TID
			<< newl << "p: " << p
			<< newl << "p Type ID: " << p->TypeID();
		return ( p->TypeID() == TID );
	}

	T* LoadAsset( std::string FileName ){
		gLog( _INFO ) << "Factory #" << TID << " Loading Asset " << FileName.c_str();
		GameAsset* p = Asset_Faculties::Instance().LoadAsset( TID, FileName );
		return IsFactoryType( p ) ? (T*)p : nullptr;
	}

	T* GetAsset( std::string AssetName ){
		gLog( _INFO ) << "Factory #" << TID << " Retrieving Asset " << AssetName.c_str();
		GameAsset* p = Asset_Faculties::Instance().Manager->GetAsset( AssetName );
		if ( p != nullptr && IsFactoryType( p ) ){
			return (T*)p;
		}
		return nullptr;
	}
};

#endif