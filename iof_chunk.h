/*
Project: IO File Chunks Library
Start Date: 2013/12/21
Updated: 2015/11/8
Version: 2.5.1.7
Next Version: 3.0
*/
/*
#ifndef _IO_FILE_CHUNKS_H_
#define _IO_FILE_CHUNKS_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#pragma comment (lib,"iofchunks.lib")

#define MAKE_ID(a,b,c,d) ((a)|((b)<<8)|((c)<<16)|((d)<<24)) //32-bit Little-Endian
#define BID_FORM MAKE_ID('F','O','R','M')
#define BID_BODY MAKE_ID('B','O','D','Y')
#define BID_CAT MAKE_ID('C','A','T',' ')

struct							iof_header;
struct							iof_chunk;
class							iof_positions;


namespace iof
{
	extern inline unsigned __int32			MAKE_ID32( unsigned __int32 rawID );
	extern inline unsigned __int64			MAKE_ID64( unsigned __int64 rawID );

	extern inline bool									check_header( const iof_header* reading_material );
	extern inline bool									checkfor_subChunks( const iof_chunk* reading_material );
	extern inline unsigned __int32			count_subChunks( const iof_chunk* reading_material );
	extern iof_positions*							find_subChunks( const iof_chunk* reading_material );
	extern iof_positions*							find_subChunks( const iof_chunk* reading_material, unsigned __int32 levels_to_read );
	
	
	extern inline iof_chunk*						copy_to_chunk( const char* data );
	extern inline iof_chunk*						cast_to_chunk( char* data );
	
	
	extern inline const iof_chunk*			get_subChunk( const iof_chunk* parent_chunk, unsigned __int64 sub_position );
	extern std::list<const iof_chunk*>		get_subChunks( const iof_chunk* reading_material, unsigned __int32 levels_to_read );
	extern std::list<const iof_chunk*>		get_subChunks( const iof_chunk* reading_material );
	extern std::list<const iof_chunk*>		list_Chunks( const iof_chunk* reading_material, unsigned __int32 levels_to_read );
	extern std::list<const iof_chunk*>		list_Chunks( const iof_chunk* reading_material );
}
												///I/O File Header Structure - provides the required structure for a valid header
struct	FileHeader
{
	enum { h_bytes = 24 }; // Number of bytes a header has
	union
	{
		struct
		{
			unsigned __int64		padding;
			unsigned __int32		BASEID_Code;
			union
			{
				char					ASID_Type[4];
				unsigned __int32		ASID_Code;
			};
			unsigned __int64		Size;
		}header;
		char					header_c[h_bytes];
	};
	FileHeader()
	{
		header.ASID_Code = 0;
		header.BASEID_Code = 0;
		header.Size = 0;
		header.padding = 0;
	}
	FileHeader( const char* data )
	{
		for ( int i = 0; i < h_bytes; ++i )
			header_c[i] = data[i];
	}
	FileHeader( const FileHeader& obj )
	{
		for ( int i = 0; i < h_bytes; ++i )
			header_c[i] = obj.header_c[i];
	}
};
												///I/O File Chunk Structure - provides the required structure for a valid chunk
struct FileData : FileHeader
{
	char*					data;

	~FileData()
	{
		if (data != nullptr)
		{
			delete[] data;
		}
		data = nullptr;
	}
};
	
												///I/O File Header Positions - provides a way of easily storing and accessing start positions of headers within an I/O File Chunk. It stores one Parent position for every Child Position.
class						iof_positions
{
	public:
		void														add_entries(unsigned __int64 Parent, unsigned __int64 Child);
		const unsigned __int32						count_entries();
		const unsigned __int64						get_parent_of(unsigned __int64 Child);
		std::list<const unsigned __int64>		get_children_of(unsigned __int64 Parent);
		std::list<const unsigned __int64>		get_all();

	private:
		enum { PARENT, CHILD };
		std::list<const unsigned __int64>					Positions[2];
		std::list<const unsigned __int64>::iterator			Parent_Itr;
		std::list<const unsigned __int64>::iterator			Child_Itr;
};


#endif
