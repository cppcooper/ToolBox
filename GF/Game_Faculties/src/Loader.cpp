#include "../Loader.h"

#include "../AssetAbstract.h"
#include "../InterAccess.h"
#include "../AssetMgr.h"
#include "../Pool.h"
using namespace GameAssets;
//TODO: Check that loops exit when required

//Counts how many Game Asset files exist for a given Asset Type (ie. Factory Type)
unsigned int Asset_Loader::CountAssets( Factory* F )
{
	std::set<std::string> Assets;
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	size_t Cpos = 0;
	size_t Lpos = 0;

	//Collects files into an std::set<string>
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		//This outer loop goes through all the extensions in Ext_List
		Cpos = Ext_List.find_first_of( ';', Lpos );

		std::string Extension = Ext_List.substr( Lpos, Cpos - Lpos );
		file_directory& FileListing = file_mgr.Get_Files( Extension );

		auto it = FileListing.begin();
		while ( it != FileListing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;
			Assets.emplace( AssetRecordName );
		}
		Lpos = Cpos + 1;
	}
	return Assets.size();
}

void Asset_Loader::LoadMultiFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	size_t Cpos = 0;
	size_t Lpos = 0;

	//Counts how many assets are needed and get an array big enough for that number of the given type
	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameAsset* p = F->Create( N );
	Asset_Faculties::Instance().Pool->Return( p, p[0].storage.length );

	//Loading Assets one File at a time doing so one Extension Type at a time
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		Cpos = Ext_List.find_first_of( ';', Lpos );
		
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );

		//Load assets with files of the Current_Extension
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

//TODO: add conditions for preventing duplicate records
void Asset_Loader::LoadSingleFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	size_t Cpos = 0;
	size_t Lpos = 0;

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	
	//Counts how many assets are needed and get an array big enough for that number of the given type
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameAsset* p = F->Create( N );
	Asset_Faculties::Instance().Pool->Return( p, p[0].storage.length );

	//Loading Assets one File at a time doing so one Extension Type at a time
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		Cpos = Ext_List.find_first_of( ',', Lpos );
		Cpos = Cpos != Ext_List.npos ? Cpos + 1 : Cpos;
		
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );

		//Load assets with files of the Current_Extension
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

GameAsset* Asset_Loader::LoadAsset( std::string file )
{
	std::string file_ext = file.substr( file.find_last_of( '.' ), file.npos );
	file = file.substr( 0, file.find_last_of( '.' ) );

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	const std::vector<Factory*>& FVector = Asset_Faculties::Instance().Factories;
	uint Num_Factories = FVector.size();

	for ( uint i = 0; i < Num_Factories; ++i )
	{
		Factory* F = FVector.at( i );
		if ( F->TypeExtensions().find( file_ext ) != std::string::npos )
		{
			GameAsset* p = nullptr;
			if ( !F->RecordExtension().empty() )
			{
				p = AssetMgr.GetAsset( file + F->RecordExtension() );
			}
			if ( p == nullptr )
			{
				AssetMgr.RecordAsset
			}
			p = p ? p : F->Create();
			p->Load( file + file_ext );
			return p;
		}
	}
}
