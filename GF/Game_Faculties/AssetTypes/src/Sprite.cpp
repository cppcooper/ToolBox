#include "../Sprite.h"

#include "../../InterAccess.h"
#include "../../Factory.h"
#include "../../AssetMgr.h"
using namespace GameAssets;


TYPE_ID_IMPL( Sprite )
void Sprite::Load( std::string file )
{
	assert( !m_Initialized );
	std::ifstream Data;
	Data.open( file );
	if ( Data.is_open() )
	{
		ushort Sections = 0;
		Data >> Sections;

		ushort TexLength = 0;
		Data >> TexLength;

		char* TexFile = new char[TexLength + 1];
		memset( TexFile, 0, TexLength + 1 );
		Data.read( TexFile, 1 );
		Data.read( TexFile, TexLength );

		m_Tex = (Texture*)Asset_Faculties::Instance().GetAsset( TexFile );
		assert( m_Tex != nullptr );
		uint& Tex_width = m_Tex->width;
		uint& Tex_height = m_Tex->height;

		
		ushort Frames = 0, width = 0, height = 0, x = 0, y = 0;

		ushort cursor = Data.tellg();
		for ( int i = 0; i < Sections; ++i )
		{
			Data >> Frames;
			m_Frames += Frames;
			Data >> width;
			Data >> height;
			for ( int f = 0; f < Frames; ++f )
			{
				Data >> x;
				Data >> y;
			}
		}
		Data.seekg( cursor );

		m_vCount = 4 * m_Frames;
		m_vLength = 5;
		m_Vertices = new float[m_vCount * m_vLength];
		for ( int i = 0; i < Sections; ++i )
		{
			Data >> Frames;
			Data >> width;
			Data >> height;
			for ( m_FrameIndex = 0; m_FrameIndex < m_Frames; ++m_FrameIndex )
			{
				Data >> x;
				Data >> y;

				///Bottom Left
				m_Vertices[( m_FrameIndex * 20 ) + 0] = 0.0f;															/// X
				m_Vertices[( m_FrameIndex * 20 ) + 1] = 0.0f;															/// Y
				m_Vertices[( m_FrameIndex * 20 ) + 2] = 0.0f;														/// Z
				m_Vertices[( m_FrameIndex * 20 ) + 3] = (float)x / (float)Tex_width;										/// U - Texture mapping
				m_Vertices[( m_FrameIndex * 20 ) + 4] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );		/// V - Texture mapping (Inverted Axis?)

				///Bottom Right
				m_Vertices[( m_FrameIndex * 20 ) + 5] = (float)width;
				m_Vertices[( m_FrameIndex * 20 ) + 6] = 0.0f;
				m_Vertices[( m_FrameIndex * 20 ) + 7] = 0.0f;
				m_Vertices[( m_FrameIndex * 20 ) + 8] = ( (float)x + (float)width ) / (float)Tex_width;
				m_Vertices[( m_FrameIndex * 20 ) + 9] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );

				///Top Right
				m_Vertices[( m_FrameIndex * 20 ) + 10] = (float)width;
				m_Vertices[( m_FrameIndex * 20 ) + 11] = (float)height;
				m_Vertices[( m_FrameIndex * 20 ) + 12] = 0.0f;
				m_Vertices[( m_FrameIndex * 20 ) + 13] = ( (float)x + (float)width ) / (float)Tex_width;
				m_Vertices[( m_FrameIndex * 20 ) + 14] = 1.0f - ( (float)y / (float)Tex_height );

				///Top Left
				m_Vertices[( m_FrameIndex * 20 ) + 15] = 0.0f;
				m_Vertices[( m_FrameIndex * 20 ) + 16] = (float)height;
				m_Vertices[( m_FrameIndex * 20 ) + 17] = 0.0f;
				m_Vertices[( m_FrameIndex * 20 ) + 18] = (float)x / (float)Tex_width;
				m_Vertices[( m_FrameIndex * 20 ) + 19] = 1.0f - ( (float)y / (float)Tex_height );
			}
		}
	}
	else
	{
		assert( 0 ); //Couldn't open file
	}
	assert( !Data.fail() );
	Data.close();

	m_Shader = (GLSLProgram*)Asset_Faculties::Instance().GetAsset( "2d_default.glslp" );
	assert( m_Shader != nullptr );

	m_FrameIndex = 0;
	Init();
}

void Sprite::Reset()
{
	m_Frames = 0;
	m_FrameIndex = 0;
	m_Scale = 1.0f;
	m_Alpha = 1.0f;
	Deinit();
}

Sprite& Sprite::operator[]( ushort frame )
{
	m_FrameIndex = m_Frames ? frame % m_Frames : 0;
	return *this;
}

void Sprite::Draw()
{
	Draw( glm::mat4( 1.f ) );
}

void Sprite::Draw( const glm::mat4& matrix )
{
	glBindVertexArray( m_VAO );
	m_Tex->Bind();
	m_Shader->UseProgram();

	m_Shader->SetUniform( "in_Scale", m_Scale );
	m_Shader->SetUniform( "in_Alpha", m_Alpha );
	m_Shader->SetUniform( "modelMatrix", matrix );

	glDrawArrays( GL_QUADS, m_FrameIndex * 4, 4 );
}

void Sprite::Scale( float scale )
{
	m_Scale = scale; //Apply to Model Matrix
}

void Sprite::SetAlpha( float alpha )
{
	m_Alpha = alpha;
}
