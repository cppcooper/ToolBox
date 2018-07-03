/**
* IO File Chunks
* --------------
* This library implements a binary file format capable of recursively organizing data.
* The library comes with a slew of utilities for storing data in binary format.
* Changelog:
*           -----REDACTED-----
*           2013/12/21 - 1.0.0
*           -----REDACTED-----
*           -----REDACTED-----
*           2015/11/8 - 2.5.1.7
*           -----REDACTED-----
*           -----REDACTED-----
*           2017/04/04 - 3.0.0a
*           2017/06/03 - 3.0.1a
* ============================
* TODO: We need to forward declare STL types
* TODO: Remove STL includes
* TODO: Rename file
*/

#ifndef _TOOLS_IOFCHUNKS_H
#define _TOOLS_IOFCHUNKS_H
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <int_typedefs.h>

#define MAKE_ID(a,b,c,d) ((a)|((b)<<8)|((c)<<16)|((d)<<24)) //32-bit Little-Endian
#define BID_FORM MAKE_ID('F','O','R','M')
#define BID_BODY MAKE_ID('B','O','D','Y')
#define BID_CAT MAKE_ID('C','A','T',' ')


namespace fileio
{
    /** A HeaderFormat, this struct, is the basis for our file format.
    * <0> <Recursive Flag> <Chunk Format> <Data Format> <Data Length> <0> <Data>
    * <0 0 0> <1> <1 0 0 0 0> <1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0> <1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0> <0 0 0> <Data> **/
    struct HeaderInfo
    {
        uint64 PADDING_Front : 3;
        uint64 Recursive     : 1;   /** Chunks can be recursive. **/
        uint64 ChunkFormat   : 5;   /** We can have 32 Chunk Formats. **/
        uint64 DataFormat    : 20;  /** Supports 1,048,576 Formats for organizing your data. **/
        uint64 DataLength    : 32;  /** Max Chunk Size: 4.294 GiB **/
        uint64 PADDING_Back  : 3;

        bool isValid() const { return ~(PADDING_Front | PADDING_Back); }
    };

    /** A DataHeader contains information useful in parsing external-data(relative to these objects).
    * The information is packed into a 64 bit variable.
    * The information is also availabe as an Array of Bytes.
    TODO: rewrite **/
    struct DataHeader
    {
        enum { h_bytes = sizeof( HeaderInfo ) };
        union
        {
            uint64          m_tag;
            HeaderInfo      m_info;
            char            m_serial[h_bytes];
        };
    };

    /** A DataBody is a pointer to the data body.
     * It contains a pointer to the first byte in the data body following the data header.
     * It stores an offset to the pointer
     * TODO: decide whether to
     *      A) point to the parent and offset to the data body.
     *      B) point to the data body and save an offset to the parent
     *      C) point to the data body and save an offset to the header
     *      D) point to the header and save an offset to the data body
     * ->   E) point to the head of the memory allocation
     * TODO: rewrite comment
     * **/
    struct DataBody 
    {
        std::shared_ptr<char> DataPointer;
        char*   DataPointer_o = nullptr;
        uint32  Offset = 0;
        //TODO: use shared pointer to memory block head, then offset will be of use
    };


    /** **/
    struct Chunk
    {
        DataHeader  m_DataHeader;
        DataBody    m_DataBody;
    };

    /** **/
    class SmartChunk : protected Chunk
    {
        friend class ChunkBuilder;
    protected:
        Chunk*  m_Parent = nullptr;
        SmartChunk* m_Prev = nullptr;
        SmartChunk* m_Next = nullptr;

    public:
        bool IsRecursive()     const {return m_DataHeader.m_info.Recursive;}
        uint8 GetChunkFormat() const {return m_DataHeader.m_info.ChunkFormat;}
        uint32 GetDataFormat() const {return m_DataHeader.m_info.DataFormat;}
        uint32 GetDataLength() const {return m_DataHeader.m_info.DataLength;}

        void SetRecursionFlag( bool NewValue ) {m_DataHeader.m_info.Recursive = NewValue ? 1 : 0;}
        void SetChunkFormat( uint8 NewFormat ) {m_DataHeader.m_info.ChunkFormat = NewFormat & ((1 << 6)-1);}
        void SetDataFormat( uint32 NewFormat ) {m_DataHeader.m_info.DataFormat = NewFormat & ((1 << 21)-1);}
        void SetDataLength( uint32 NewLength ) {m_DataHeader.m_info.DataLength = NewLength;}

        void GetData(char* &data, uint32 &size) const {data = m_DataBody.DataPointer.get() + m_DataBody.Offset; size = m_DataHeader.m_info.DataLength;}
        template<class T>
        SmartChunk& operator<<( T data );
    };

    /** **/
    class ChunkBuilder
    {
        using ChunkData = std::vector<std::unique_ptr<char>>;
    private:
        SmartChunk* root = nullptr; //Will only create one top level Chunk
        ChunkData   buffer;
        //Instruction List //how to operate on the buffer merge/insert/etc??
        
    public:
        //Nest Data
        //Push Chunk
        //Insert Chunk
        //Build Master Chunk - Consolidates data into one array
    };

    /** **/
    class ChunkScanner
    {
    private:
        //Chunk reference
        //read head
        //data size
    };


    /** **/
    class File
    {
    private:
    protected:
    public:
        bool IsOpen();
        void Open(const char* FileName);
        void Close();
    };
}


#endif