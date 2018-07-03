#include "../tools_iofchunks.h"

using namespace FileChunk;

DataHeader::DataHeader()
{
    Format = 0;
}

DataHeader::DataHeader( const char* data )
{
    for ( int i = 0; i < h_bytes; ++i )
    {
        SerializedArray[i] = data[i];
    }
}

DataHeader::DataHeader( const DataHeader& obj )
{
    Format = obj.Format;
}


DataChunk::DataChunk( const DataChunk& obj )
{
    m_DataHeader = obj.m_DataHeader;
    m_DataBody = obj.m_DataBody;
    m_Parent = obj.m_Parent;
}

const char* DataChunk::str()
{
    return m_DataBody.DataPointer - DataHeader::h_bytes;
}