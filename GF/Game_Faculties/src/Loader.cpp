#include "../Loader.h"

#include "../AssetAbstract.h"
#include "../InterAccess.h"
#include "../AssetMgr.h"
#include "../Pool.h"
using namespace GameAssets;


Asset_Loader::Asset_Loader()
{
	m_Log = &Asset_Faculties::Instance().GetManagementLog();
	m_Log->Line( INFO ) << "Asset Loader Initialized.";
}

Asset_Loader::~Asset_Loader()
{
	m_Log->Line( INFO ) << "Asset Loader Deinitialized.";
}


//TODO: Check that loops exit when required

//Counts how many Game Asset files exist for a given Asset Type (ie. Factory Type)
unsigned int Asset_Loader::CountAssets( Factory* F )
{
	std::set<std::string> Assets;
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	m_Log->Line( INFO ) << "Counting Catalogued Assets of Type ID: " << F->Get_TypeID() << ", Extension Types to count: " << F->TypeExtensions();
	size_t Cpos = 0;
	size_t Lpos = 0;

	//Collects files into an std::set<string>
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		//This outer loop goes through all the extensions in Ext_List
		Cpos = Ext_List.find_first_of( ';', Lpos );
		m_Log->Line( DEBUG2 ) << "Reading extension.. Cpos: " << Cpos << ", Lpos: " << Lpos;

		std::string Extension = Ext_List.substr( Lpos, Cpos - Lpos );
		m_Log->Line( DEBUG1 ) << "Counting Assets of extension type: " << Extension;
		file_directory& FileListing = file_mgr.Get_Files( Extension );

		auto it = FileListing.begin();
		while ( it != FileListing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;
			Assets.emplace( AssetRecordName );
		}
		Lpos = Cpos + 1;
	}
	m_Log->Line( DEBUG1 ) << "There was " << Assets.size() << " asset files counted.";
	return Assets.size();
}

void Asset_Loader::LoadMultiFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	m_Log->Line( INFO ) << "Loading Multi-File Assets of Type ID: " << F->Get_TypeID();
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
		m_Log->Line( DEBUG3 ) << "Reading extension.. Cpos: " << Cpos << ", Lpos: " << Lpos;
		
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
				m_Log->Line( DEBUG2 ) << "New Asset: " << AssetRecordName << " Address: " << p;
				assert( AssetMgr.RecordAsset( AssetRecordName, p ) );
			}
			else
			{
				m_Log->Line( DEBUG2 ) << "Existing Asset: " << AssetRecordName << " Address: " << p;
			}

			m_Log->Line( DEBUG1 )
				<< std::endl << "Asset Record: " << AssetRecordName << ", pointer = " << p
				<< std::endl << "Loading file: " << it->first
				<< std::endl;
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
	m_Log->Line( INFO ) << "Loading Single-File Assets of Type ID: " << F->Get_TypeID();
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
		m_Log->Line( DEBUG3 ) << "Reading extension.. Cpos: " << Cpos << ", Lpos: " << Lpos;

		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );

		//Load assets with files of the Current_Extension
		auto it = File_Listing.begin();
		while ( it != File_Listing.end() )
		{
			p = AssetMgr.GetAsset( it->first );
			if ( p == nullptr )
			{
				p = F->Create();
				p->Load( it->second + it->first );
				m_Log->Line( DEBUG1 ) << "Asset loaded" << std::endl << "Asset: " << it->first << std::endl << "Address: " << p;
				assert( AssetMgr.RecordAsset( it->first, p ) );
			}
			else
			{
				m_Log->Line( ERROR ) << "Asset was previously loaded" << std::endl << "Asset: " << it->first << std::endl << "Address: " << p;
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
	m_Log->Line( INFO ) << "Asset Loader.... Loading all registered asset files";
	const std::vector<Factory*>& FVector = Asset_Faculties::Instance().Factories;
	uint Num_Factories = FVector.size();

	for ( uint i = 0; i < Num_Factories; ++i )
	{
		Factory* F = FVector.at( i );
		m_Log->Line( DEBUG1 ) << "Auto-Load sequence: Processing Type ID #" << F->Get_TypeID();
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

GameAsset* Asset_Loader::LoadAsset( Factory* F, std::string FileName )
{
	m_Log->Line( INFO ) << "Manual Load Procedure"
		<< std::endl << "Asset: " << FileName
		<< std::endl << "Type ID: " << F->Get_TypeID();
	std::string file_ext = FileName.substr( FileName.find_last_of( '.' ), FileName.npos );
	FileName = FileName.substr( 0, FileName.find_last_of( '.' ) );

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;

	if ( F->TypeExtensions().find( file_ext ) != std::string::npos )
	{
		GameAsset* p = nullptr;
		LogStream& logLine = m_Log->Line( DEBUG1 );
		logLine << std::endl << "Asset File: " + FileName;
		if ( !F->RecordExtension().empty() )
		{
			p = AssetMgr.GetAsset( FileName + F->RecordExtension() );
			logLine << F->RecordExtension();
		}
		else
		{
			p = AssetMgr.GetAsset( FileName + file_ext );
			logLine << file_ext;
		}
		logLine << std::endl << "Address: ";
		if ( p == nullptr )
		{
			p = F->Create();
			logLine << std::endl << "*Asset Loaded*";
			assert( AssetMgr.RecordAsset( FileName + F->RecordExtension(), p ) );
		}
		else
		{
			logLine << std::endl << "*Asset Reloaded*";
		}
		logLine << std::endl;
		p->Load( FileName + file_ext );
		return p;
	}
	m_Log->Line( ERROR ) << FileName << " is not a valid Asset File. - nullptr return";
	return nullptr;
}