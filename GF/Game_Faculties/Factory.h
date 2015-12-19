#ifndef _ASSETFACTORY_H
#define _ASSETFACTORY_H

#include "AssetAbstract.h"
#include "InterAccess.h"
#include "Pool.h"
#include "STL.h"
using namespace GameAssets;

template<class T>
class Asset_Factory : public Factory
{
private:
	uint TID = 0;
	Asset_Factory(){
		Asset_Faculties::Instance().Factories.push_back( ( Factory* )this );
		TID = Asset_Faculties::Instance().Factories.size();
	}

public:
	static Asset_Factory<T>& Instance(){
		static Asset_Factory<T> instance;
		return instance;
	}

	GameAsset* Create( uint N = 1 )	{
		return (GameAsset*)Asset_Faculties::Instance().Pool->Get<T>( N );
	}

	T* LoadAsset( std::string FileName ){
		GameAsset* p = Asset_Faculties::Instance().LoadAsset( FileName );
		return IsFactoryType( p ) ? (T*)p : nullptr;
	}

	T* GetAsset( std::string AssetName ){
		GameAsset* p = Asset_Faculties::Instance().GetAsset( AssetName );
		return IsFactoryType( p ) ? (T*)p : nullptr;
	}

	bool IsFactoryType( GameAsset* p ){
		return ( p->TypeID() == TID );
	}

	uint Get_TypeID(){
		return TID;
	}

	static uint TypeID(){
		return Instance().TID;
	}

	std::string& TypeExtensions(){
		static std::string extensions = "";
		return extensions;
	}

	std::string& RecordExtension(){
		static std::string extension = "";
		return extension;
	}
};

/*template<class T>
T* Asset_Faculties::GetAsset( std::string AssetName )
{
	return Asset_Factory<T>::Instance().GetAsset( AssetName );
}*/

#endif