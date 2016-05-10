#include "../Loader.h"

#include "../../InterAccess.h"
#include "../../AssetAbstract.h"
#include "../AssetMgr.h"
#include "../Pool.h"


Asset_Loader::Asset_Loader()
{
	m_Log = &Object_Faculties::GetManagementLog();
	m_Log->Line( _INFO ) << "Asset Loader Initialized.";
}

Asset_Loader::~Asset_Loader()
{
	m_Log->Line( _INFO ) << "Asset Loader Deinitialized.";
}


//Counts how many Game Asset files exist for a given Asset Type (ie. Factory Type)
unsigned int Asset_Loader::CountAssets( GameAssets::Factory* F )
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
using GameAssets::AssetObject;

void Asset_Loader::LoadMultiFileAssets( GameAssets::Factory* F )
{
	Asset_Manager& AssetMgr = *Object_Faculties::Instance().Manager;
	std::string Ext_List = F->TypeExtensions();
	std::string Record_Ext = F->RecordExtension();
	m_Log->Line( _INFO ) << "Asset_Loader::LoadMultiFileAssets()";
	size_t Cpos = 0;
	size_t Lpos = 0;


	//Counts how many assets are needed and get an array big enough for that number of the given type
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;

	//Get Asset Pool - Then check for nullptr and makes sure it is the right type OR terminate
	AssetObject* p = dynamic_cast<AssetObject*>(F->Create( N ));
	assert( F->IsFactoryType( p ) );

	//Return the pool so we don't need to keep track of where we are in the array
	Object_Faculties::Instance().Pool->Return( p, p[0].GetStorageData().length );

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
				//Replace nullptr with valid address
				p = (AssetObject*)F->Create();
				m_Log->Line( _INFO ) << "New Record";

				//Record the Asset or Terminate
				assert( AssetMgr.RecordAsset( AssetRecordName, p ) );
			}
			else
			{
				m_Log->Line( _INFO ) << "Existing Record";
			}

			//Load a/the file
			m_Log->Line( _DEBUG1 ) << "Loading File"
				<< newl << "Record: " << AssetRecordName
				<< newl << "Address: " << p
				<< newl << "Loading: " << it->first;
			p->Load( it->second + it->first );
			it = std::next( it );
		}
		//Extension list positions
		Lpos = Cpos + 1;
	}
}

//TODO: add conditions for preventing duplicate records
void Asset_Loader::LoadSingleFileAssets( GameAssets::Factory* F )
{
	Asset_Manager& AssetMgr = *Object_Faculties::Instance().Manager;
	std::string Ext_List = F->TypeExtensions();
	m_Log->Line( _INFO ) << "Asset_Loader::LoadSingleFileAssets()";
	size_t Cpos = 0;
	size_t Lpos = 0;

	
	//Counts how many assets are needed and get an array big enough for that number of the given type
	unsigned int N = this->CountAssets( F );
	if ( N == 0 )
		return;

	//Get Asset Pool - Then check for nullptr and makes sure it is the right type OR terminate
	AssetObject* p = dynamic_cast<AssetObject*>(F->Create( N ));
	assert( F->IsFactoryType( p ) );

	//Return the pool so we don't need to keep track of where we are in the array
	Object_Faculties::Instance().Pool->Return( p, p[0].GetStorageData().length );

	//Loading Assets one File at a time doing so one Extension Type at a time
	size_t final_pos = Ext_List.find_last_of( ';' );
	while ( Cpos < final_pos )
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
			p = AssetMgr.GetAsset( it->first );
			if ( p == nullptr )
			{
				//Replace nullptr with valid address
				p = (AssetObject*)F->Create();

				//Load a/the file
				p->Load( it->second + it->first );
				m_Log->Line(_DEBUG2) << "Successful Asset Load"
					<< newl << "Asset: " << it->first 
					<< newl << "Address: " << p;

				//Record the Asset or Terminate
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
		//Extension list positions
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
	const std::vector<GameAssets::Factory*>& FVector = Object_Faculties::Instance().Factories;
	uint Num_Factories = FVector.size();

	for ( uint i = 0; i < Num_Factories; ++i )
	{
		GameAssets::Factory* F = FVector.at( i );
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

GameAssets::AssetObject* Asset_Loader::LoadAsset( GameAssets::Factory* F, std::string FileName )
{
	Asset_Manager& AssetMgr = *Object_Faculties::Instance().Manager;
	m_Log->Line( _INFO ) << "Asset_Loader::LoadAsset()";
	m_Log->Line( _DEBUG1 ) << "Manual Load Procedure"
		<< newl << "File: " << FileName
		<< newl << "Type ID: " << F->Get_TypeID()
		<< newl << "Type ID Extensions: " << F->TypeExtensions();
	
	std::string file_ext = FileName.substr( FileName.find_last_of( '.' ), FileName.npos );
	std::string RecordName = FileName.substr( 0, FileName.find_last_of( '.' ) );

	if ( F->TypeExtensions().find( file_ext ) != std::string::npos )
	{
		GameAssets::AssetObject* p = nullptr;
		RecordName += !F->RecordExtension().empty() ? F->RecordExtension() : file_ext;
		p = AssetMgr.GetAsset( RecordName );
		if ( p == nullptr )
		{
			//Replace nullptr with valid address
			p = (AssetObject*)F->Create();
			m_Log->Line( _DEBUG1 ) << "New Asset"
				<< newl << "Record: " << RecordName
				<< newl << "Address: " << p;

			//Record the Asset or Terminate
			assert( AssetMgr.RecordAsset( RecordName, p ) );
		}
		else
		{
			m_Log->Line( _DEBUG1 ) << "Existing Asset"
				<< newl << "Record: " << RecordName
				<< newl << "Address: " << p;
		}
		//Load a/the file
		p->Load( FileName + file_ext );
		return p;
	}
	m_Log->Line( _ERROR ) << "EXTENSION NOT FOUND - Returns nullptr"
		<< newl << "Extension: " << file_ext;
	return nullptr;
}