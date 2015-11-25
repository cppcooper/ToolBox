#include "../Loader.h"

#include "../AssetAbstract.h"
#include "../InterAccess.h"
#include "../AssetMgr.h"
#include "../Pool.h"
using namespace GameAssets;


unsigned int Asset_Loader::CountAssets( Factory* F )
{
	std::set<std::string> Assets;
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	size_t current_pos = 0;
	size_t last_pos = 0;

	while ( current_pos != std::string::npos )
	{
		current_pos = Ext_List.find_first_of( ',', last_pos );

		std::string Extension = Ext_List.substr( last_pos, current_pos - last_pos );//This should NOT include current_pos
		file_directory& FileListing = file_mgr.Get_Files( Extension );

		auto it = FileListing.begin();
		while ( it != FileListing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;
			Assets.emplace( AssetRecordName );
		}
		last_pos = current_pos + 1;
	}
	return Assets.size();
}

void Asset_Loader::LoadMultiFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	size_t Cpos = 0;
	size_t Lpos = 0;

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameAsset* p = F->Create( N );
	Asset_Faculties::Instance().Pool->Return( p, p[0].storage.length );

	while ( Cpos != std::string::npos )
	{
		Cpos = Ext_List.find_first_of( ',', Lpos );
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );//This should NOT include current_pos
		
		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );
		auto it = File_Listing.begin();

		while ( it != File_Listing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;
			p = AssetMgr.GetAsset( AssetRecordName );
			if ( p == nullptr )
			{
				p = F->Create(); //Guarantees (p != nullptr)
				AssetMgr.RecordAsset( AssetRecordName, p );
			}
			p->Load( it->second + it->first );
			it = std::next( it );
		}
		Lpos = Cpos + 1;
	}
}

void Asset_Loader::LoadSingleFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	size_t Cpos = 0;
	size_t Lpos = 0;

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameAsset* p = F->Create( N );
	Asset_Faculties::Instance().Pool->Return( p, p[0].storage.length );

	while ( Cpos != std::string::npos )
	{
		Cpos = Ext_List.find_first_of( ',', Lpos );
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );//This should NOT include current_pos
		
		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );
		auto it = File_Listing.begin();

		while ( it != File_Listing.end() )
		{
			p = AssetMgr.GetAsset( it->first );
			if ( !p )
			{
				p = F->Create();
				p->Load( it->second + it->first );
				AssetMgr.RecordAsset( it->first, p );
			}
			it = std::next( it );
		}
		Lpos = Cpos + 1;
	}
}

void Asset_Loader::RegisterDirectory( std::string path )
{
	file_mgr.Register_Directory( path );
}

void Asset_Loader::LoadAssets()
{
	const std::vector<Factory*>& FVector = Asset_Faculties::Instance().Factories;
	uint Num_Factories = FVector.size();

	for ( uint i = 0; i < Num_Factories; ++i )
	{
		Factory* F = FVector.at( i );
		assert( !F->TypeExtensions().empty() );
		bool bType_Loads_ManyFiles = !F->RecordExtension().empty();
		if ( bType_Loads_ManyFiles )
		{
			LoadMultiFileAssets( F );
		}
		else
		{
			LoadSingleFileAssets( F );
		}
	}
}
