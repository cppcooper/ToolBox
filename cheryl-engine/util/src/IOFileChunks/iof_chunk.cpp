#include "iof_chunk.h"
namespace iof
{
	inline unsigned __int32					MAKE_ID32(unsigned __int32 rawID)
	{
		int j = sizeof(unsigned __int32);
		char* unconverted = (char*)(&rawID);
		char* converted = new char[j];

		for (int i = 0; i < sizeof(unsigned __int32); ++i)
		{
			converted[i] = unconverted[--j];
		}
		unsigned __int32 R = *(unsigned __int32*)(converted);
		delete[] converted;

		return R;
	}

	inline unsigned __int64					MAKE_ID64(unsigned __int64 rawID)
	{
		int j = sizeof(unsigned __int64);
		char* unconverted = (char*)(&rawID);
		char* converted = new char[j];

		for (int i = 0; i < sizeof(unsigned __int64); ++i)
		{
			converted[i] = unconverted[--j];
		}
		unsigned __int32 R = *(unsigned __int64*)(converted);
		delete[] converted;

		return R;
	}

	inline bool										check_header(const iof_header* reading_material)
	{
		unsigned __int32 ID = reading_material->header.BASEID_Code;
		unsigned __int64 pad = reading_material->header.padding;

		if (((ID == BID_FORM) || (ID == BID_CAT) || (ID == BID_BODY)) && (pad == 0))
			return true;
		else
			return false;
	}

	inline bool										checkfor_subChunks(const iof_chunk* reading_material)
	{
		if ((reading_material->header.BASEID_Code != BID_BODY) && (reading_material->header.Size >= (2 * sizeof(iof_header))))
		{
			iof_header H = iof_header(&reading_material->data[sizeof(iof_header)]);
			return check_header(&H);
		}
		else
			return false;
	}

	unsigned __int32								count_subChunks(const iof_chunk* reading_material)
	{
		iof_positions* Positions = find_subChunks(reading_material);
		unsigned __int32 R = Positions->count_entries() - 1;
		delete Positions;
		return R;
	}

	iof_positions*									find_subChunks( const iof_chunk* reading_material )
	{
		//Current Positional Data
		unsigned __int64 Current_Position = 0;
		unsigned __int64 Position_Skip = 0;
		unsigned __int64 Current_Parent_Position = 0;

		//Position List Handler Object
		iof_positions* Positions = new iof_positions();

		const char* data = reading_material->data;

		//Loop for reading entire chunk
		while ( Current_Position < reading_material->header.Size )
		{//while Not out of bounds

			//May be able to optimize this While check
			//We need to check if we've made it to the end or beyond the Parent's chunk


			///Need to find a way to include the reading material's header as apart of the data being parsed
			/// cast_to_char_ptr( const iof_chunk* reading_material )
			while ( Current_Position < ( Current_Parent_Position + FileHeader( &( data[Current_Parent_Position] ) ).header.Size ) )
			{//We are still inside our parent chunk
				FileHeader temp_h = FileHeader( &data[Current_Position] );

				if ( check_header( &temp_h ) )
				{//VALID Header

					//Record our current valid header position and its parent position
					Positions->add_entries( Current_Parent_Position, Current_Position );

					if ( temp_h.header.BASEID_Code != BID_BODY )
					{//Header is capable of holding sub chunks, which would all be a mere header's width away
						Position_Skip = FileHeader::h_bytes;
						Current_Parent_Position = Current_Position;
					}
					else
					{//Header must be of type BODY so the next header must be at least on the other side of the BODY
						Position_Skip = temp_h.header.Size;
					}
					Current_Position += Position_Skip;
				}
				else//INVALID Header
				{
					//We set our current position to the position of our Current Parent
					Current_Position = Current_Parent_Position;

					//We set our skip amount to the size of our Parent's Chunk size
					Position_Skip = FileHeader( &data[Current_Position] ).header.Size;

					//We set our Parent to our Current Parent's Parent
					Current_Parent_Position = Positions->get_parent_of( Current_Parent_Position );

					//We set our New Current Position
					Current_Position += Position_Skip;
				}
			}
			//We have gone to the end of our Current Parent's chunk, so now we change back to its parent
			Current_Parent_Position = Positions->get_parent_of( Current_Parent_Position );
		}
		delete[] data;
		return Positions;
	}

	iof_positions*									find_subChunks(const iof_chunk* reading_material, unsigned __int32 levels_to_read)
	{
		//Current Positional Data
		unsigned __int64 Current_Position = 0;
		unsigned __int64 Position_Skip = 0;
		unsigned __int64 Current_Parent_Position = 0;
		unsigned __int32 Current_Level = 0;

		//Position List Handler Object
		iof_positions* Positions = new iof_positions();

		//Loop for reading entire chunk
		while (Current_Position < reading_material->header.Size)
		{//while Not out of bounds

			//May be able to optimize this While check
			//We need to check if we've made it to the end of the parent chunk
			while (Current_Position < (Current_Parent_Position + iof_header(&(reading_material->data[Current_Parent_Position])).header.Size))
			{
				iof_header temp_h = iof_header(&reading_material->data[Current_Position]);

				//We need to check that we haven't already reached the maximum level depth and that we have a valid header to dig into
				if ((Current_Level < levels_to_read) && check_header(&temp_h))
				{//VALID Header

					//Record our current valid header position and its parent position
					Positions->add_entries(Current_Parent_Position, Current_Position);

					if (temp_h.header.BASEID_Code != BID_BODY)
					{//Header is capable of holding sub chunks, which would all be a mere header's width away
						Position_Skip = sizeof(iof_header);
						Current_Parent_Position = Current_Position;
						Current_Level++;
					}
					else
					{//Header must be of type BODY so the next header must be at least on the other side of the BODY
						Position_Skip = temp_h.header.Size;
					}
					Current_Position += Position_Skip;
				}
				else//INVALID Header
				{
					//We set our current position to the position of our Current Parent
					Current_Position = Current_Parent_Position;

					//We set our skip amount to the size of our Parent's Chunk size
					Position_Skip = iof_header(&reading_material->data[Current_Position]).header.Size;

					//We set our Parent to our Current Parent's Parent
					Current_Parent_Position = Positions->get_parent_of(Current_Parent_Position);
					Current_Level--;

					//We set our New Current Position
					Current_Position += Position_Skip;
				}
			}
			//We have gone to the end of our Current Parent's chunk, so now we change back to its parent
			Current_Parent_Position = Positions->get_parent_of(Current_Parent_Position);
			Current_Level--;
		}
		return Positions;
	}

	inline iof_chunk*								copy_to_chunk(const char* data)
	{
		iof_chunk* new_chunk = new iof_chunk();
		int HeaderSize = sizeof(iof_header);

		for (int i = 0; i < HeaderSize; ++i)
		{
			new_chunk->header_c[i] = data[i];
		}
		unsigned __int64 ChunkSize = new_chunk->header.Size - HeaderSize;
		new_chunk->data = new char[ChunkSize];
		for (int i = 0; i < ChunkSize; ++i)
		{
			new_chunk->data[i] = data[i + HeaderSize];
		}

		return new_chunk;
	}

	inline iof_chunk*								cast_to_chunk(char* data)
	{
		iof_chunk* new_chunk = new iof_chunk();
		int HeaderSize = sizeof(iof_header);

		for (int i = 0; i < HeaderSize; ++i)
		{
			new_chunk->header_c[i] = data[i];
		}
		new_chunk->data = &data[HeaderSize];
		return new_chunk;
	}

	inline const iof_chunk*					get_subChunk(const iof_chunk* parent_chunk, unsigned __int64 sub_position)
	{
		return copy_to_chunk(&parent_chunk->data[sub_position - sizeof(iof_header)]);
	}

	std::list<const iof_chunk*>			get_subChunks(const iof_chunk* reading_material, unsigned __int32 levels_to_read)
	{
		iof_positions* Positions = find_subChunks(reading_material, levels_to_read);

		std::list<const iof_chunk*> SUB_CHUNKS;
		std::list<const unsigned __int64> Chunk_Positions;
		std::list<const unsigned __int64>::iterator Chunk_Pos_Itr;
		Chunk_Positions = Positions->get_all();
		Chunk_Pos_Itr = Chunk_Positions.begin();
		Chunk_Pos_Itr++;
		if (Chunk_Pos_Itr != Chunk_Positions.end())
		{
			for (; Chunk_Pos_Itr != Chunk_Positions.end(); ++Chunk_Pos_Itr)
			{
				SUB_CHUNKS.push_back(get_subChunk(reading_material, *Chunk_Pos_Itr));
			}
		}
		delete Positions;
		return SUB_CHUNKS;
	}

	std::list<const iof_chunk*>			get_subChunks(const iof_chunk* reading_material)
	{
		iof_positions* Positions = find_subChunks(reading_material);

		std::list<const iof_chunk*> SUB_CHUNKS;
		std::list<const unsigned __int64> Chunk_Positions;
		std::list<const unsigned __int64>::iterator Chunk_Pos_Itr;
		Chunk_Positions = Positions->get_all();
		Chunk_Pos_Itr = Chunk_Positions.begin();
		Chunk_Pos_Itr++;
		if (Chunk_Pos_Itr != Chunk_Positions.end())
		{
			for (; Chunk_Pos_Itr != Chunk_Positions.end(); ++Chunk_Pos_Itr)
			{
				SUB_CHUNKS.push_back(get_subChunk(reading_material, *Chunk_Pos_Itr));
			}
		}
		delete Positions;
		return SUB_CHUNKS;
	}

	std::list<const iof_chunk*>			list_Chunks(const iof_chunk* reading_material, unsigned __int32 levels_to_read)
	{
		std::list<const iof_chunk*> ALL_CHUNKS = get_subChunks(reading_material, levels_to_read);
		ALL_CHUNKS.push_front(new iof_chunk(*reading_material));
		return ALL_CHUNKS;
	}

	std::list<const iof_chunk*>			list_Chunks(const iof_chunk* reading_material)
	{
		std::list<const iof_chunk*> ALL_CHUNKS = get_subChunks(reading_material);
		ALL_CHUNKS.push_front(new iof_chunk(*reading_material));
		return ALL_CHUNKS;
	}
}
