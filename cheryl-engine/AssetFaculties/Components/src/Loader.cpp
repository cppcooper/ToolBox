#include "../Loader.h"

#include "../../InterAccess.h"
#include "../AssetAbstract.h"
#include "../AssetMgr.h"
#include "../Pool.h"
using namespace GameAssets;


Asset_Loader::Asset_Loader()
{
	m_Log = &Asset_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Loader Initialized.";
}

Asset_Loader::~Asset_Loader()
{
	m_Log->Line( _INFO ) << "Asset Loader Deinitialized.";
}


//TODO: Check that loops exit when required

//Counts how many Game Asset files exist for a given Asset Type (ie. Factory Type)
unsigned int Asset_Loader::CountAssets( Factory* F )
{
	std::set<std::string> Assets;
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	m_Log->Line( _INFO ) << "Asset_Loader::CountAssets()";
	size_t Cpos = 0;
	size_t Lpos = 0;

	//Collects files into an std::set<string>
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		//This outer loop goes through all the extensions in Ext_List
		Cpos = Ext_List.find_first_of( ';', Lpos );
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		m_Log->Line( _DEBUG3 ) << "Extension Reading Data"
			<< newl << "Extension List: " << Ext_List
			<< newl << "Cpos: " << Cpos
			<< newl << "Lpos: " << Lpos;

		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );
		m_Log->Line( _DEBUG3 ) << "Files Data"
			<< newl << "Current Extension: " << Current_Ext
			<< newl << "File Count: " << File_Listing.size();

		auto it = File_Listing.begin();
		while ( it != File_Listing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;
			Assets.emplace( AssetRecordName );
			it = std::next( it );
		}
		Lpos = Cpos + 1;
	}
	m_Log->Line( _DEBUG1 ) << "Count Complete"
		<< newl << "Type ID: " << F->Get_TypeID()
		<< newl << "Count: " << Assets.size();
	return Assets.size();
}

#include "../../AssetTypes/BasicTypes.h"
void Asset_Loader::LoadMultiFileAssets( Factory* F )
{
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	m_Log->Line( _INFO ) << "Asset_Loader::LoadMultiFileAssets()";
	size_t Cpos = 0;
	size_t Lpos = 0;

	//Counts how many assets are needed and get an array big enough for that number of the given type
	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameObject* p = F->Create( N );
	assert( F->IsFactoryType( p ) );
	Asset_Faculties::Instance().Pool->Return( p, p[0].GetStorageData().length );

	//Loading Assets one File at a time doing so one Extension Type at a time
	while ( Cpos != std::string::npos )
	{
		Cpos = Ext_List.find_first_of( ';', Lpos );
		
		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		m_Log->Line( _DEBUG3 ) << "Extension Reading Data"
			<< newl << "Extension List: " << Ext_List
			<< newl << "Cpos: " << Cpos
			<< newl << "Lpos: " << Lpos;

		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );
		m_Log->Line( _DEBUG3 ) << "Files Data"
			<< newl << "Current Extension: " << Current_Ext
			<< newl << "File Count: " << File_Listing.size();

		//Load assets with files of the Current_Extension
		auto it = File_Listing.begin();
		while ( it != File_Listing.end() )
		{
			std::string AssetRecordName = it->first.substr( 0, it->first.find_last_of( '.' ) ) + Record_Ext;

			p = AssetMgr.GetAsset( AssetRecordName );
			if ( p == nullptr )
			{
				p = F->Create(); //Guarantees (p != nullptr)
				m_Log->Line( _INFO ) << "New Record";
				assert( AssetMgr.RecordAsset( AssetRecordName, p ) );
			}
			else
			{
				m_Log->Line( _INFO ) << "Existing Record";
			}

			m_Log->Line( _DEBUG1 ) << "Loading File"
				<< newl << "Record: " << AssetRecordName
				<< newl << "Address: " << p
				<< newl << "Loading: " << it->first;
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
	m_Log->Line( _INFO ) << "Asset_Loader::LoadSingleFileAssets()";
	size_t Cpos = 0;
	size_t Lpos = 0;

	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;
	
	//Counts how many assets are needed and get an array big enough for that number of the given type
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;
	GameObject* p = F->Create( N );
	Asset_Faculties::Instance().Pool->Return( p, p[0].GetStorageData().length );

	//Loading Assets one File at a time doing so one Extension Type at a time
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
	{
		Cpos = Ext_List.find_first_of( ',', Lpos );

		std::string Current_Ext = Ext_List.substr( Lpos, Cpos - Lpos );
		m_Log->Line( _DEBUG3 ) << "Extension Reading Data"
			<< newl << "Extension List: " << Ext_List
			<< newl << "Cpos: " << Cpos
			<< newl << "Lpos: " << Lpos;

		file_directory& File_Listing = file_mgr.Get_Files( Current_Ext );
		m_Log->Line( _DEBUG3 ) << "Files Data"
			<< newl << "Current Extension: " << Current_Ext
			<< newl << "File Count: " << File_Listing.size();

		//Load assets with files of the Current_Extension
		auto it = File_Listing.begin();
		while ( it != File_Listing.end() )
		{
			p = AssetMgr.GetAsset( it->first );
			if ( p == nullptr )
			{
				p = F->Create();
				p->Load( it->second + it->first );
				m_Log->Line(_DEBUG2) << "Successful Asset Load"
					<< newl << "Asset: " << it->first 
					<< newl << "Address: " << p;
				assert( AssetMgr.RecordAsset( it->first, p ) );
			}
			else
			{
				m_Log->Line( _ERROR ) << "Failed Asset Load - Pre-existing Asset"
					<< newl << "Asset: " << it->first 
					<< newl << "Address: " << p;
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
	m_Log->Line( _INFO ) << "Asset Loader::LoadAssets()";
	const std::vector<Factory*>& FVector = Asset_Faculties::Instance().Factories;
	uint Num_Factories = FVector.size();

	for ( uint i = 0; i < Num_Factories; ++i )
	{
		Factory* F = FVector.at( i );
		m_Log->Line( _DEBUG1 ) << "Auto-Load Sequence"
			<< newl << "Type ID:" << F->Get_TypeID();
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
		m_Log->Line( _INFO ) << "Sequence Completed for Type ID:" << F->Get_TypeID();
	}
}

GameObject* Asset_Loader::LoadAsset( Factory* F, std::string FileName )
{
	m_Log->Line( _INFO ) << "Asset_Loader::LoadAsset()";
	m_Log->Line( _DEBUG1 ) << "Manual Load Procedure"
		<< newl << "File: " << FileName
		<< newl << "Type ID: " << F->Get_TypeID()
		<< newl << "Type ID Extensions: " << F->TypeExtensions();
	
	std::string file_ext = FileName.substr( FileName.find_last_of( '.' ), FileName.npos );
	std::string RecordName = FileName.substr( 0, FileName.find_last_of( '.' ) );
	Asset_Manager& AssetMgr = *Asset_Faculties::Instance().Manager;

	if ( F->TypeExtensions().find( file_ext ) != std::string::npos )
	{
		GameObject* p = nullptr;
		RecordName += !F->RecordExtension().empty() ? F->RecordExtension() : file_ext;
		p = AssetMgr.GetAsset( RecordName );
		if ( p == nullptr )
		{
			p = F->Create();
			m_Log->Line( _DEBUG1 ) << "New Asset"
				<< newl << "Record: " << RecordName
				<< newl << "Address: " << p;
			assert( AssetMgr.RecordAsset( RecordName, p ) );
		}
		else
		{
			m_Log->Line( _DEBUG1 ) << "Existing Asset"
				<< newl << "Record: " << RecordName
				<< newl << "Address: " << p;
		}
		p->Load( FileName + file_ext );
		return p;
	}
	m_Log->Line( _ERROR ) << "EXTENSION NOT FOUND - Returns nullptr"
		<< newl << "Extension: " << file_ext;
	return nullptr;
}