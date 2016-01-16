#include "../TileSet.h"

#include "../../InterAccess.h"
#include "../../Factory.h"
#include "../../AssetMgr.h"
#include "2dtools.h"
using namespace GameAssets;

TYPE_ID_IMPL( TileSet )
void TileSet::Load( std::string file )
{
	assert( !m_Initialized );
	std::ifstream Data;
	Data.open( file );
	if ( Data.is_open() )
	{
		Data >> m_TileCount;

		ushort TexLength = 0;
		Data >> TexLength;
		char* TexFile = new char[TexLength + 1];
		memset( TexFile, 0, TexLength + 1 );
		Data.read( TexFile, 1 );
		Data.read( TexFile, TexLength );
		m_Tex = Asset_Factory<Texture>::Instance().GetAsset( TexFile );
		assert( m_Tex != nullptr );

		uint& Tex_width = m_Tex->width;
		uint& Tex_height = m_Tex->height;

		ushort width = 0, height = 0;
		Data >> width;
		Data >> height;

		m_vStride = 5 * sizeof( float );
		m_vCount = m_TileCount * 4;
		m_Vertices = new float[m_vCount * 5];
		for ( m_FrameIndex = 0; m_FrameIndex < m_TileCount; ++m_FrameIndex )
		{
			ushort x = 0, y = 0;
			Data >> x;
			Data >> y;

			AnchorBottomLeft( &m_Vertices[m_FrameIndex * 20], Tex_width, Tex_height, width, height, x, y );
		}
	}
	else
	{
		assert( 0 ); //Couldn't open file
	}
	assert( !Data.fail() );
	Data.close();

	m_Shader = Asset_Factory<GLSLProgram>::Instance().GetAsset( "2d_default.glslp" );
	assert( m_Shader != nullptr );

	m_FrameIndex = 0;
	Init();
}
