#include "../Sprite.h"

#include "../../InterAccess.h"
#include "../../Factory.h"
#include "../../AssetMgr.h"
#include "2dtools.h"
using namespace GameAssets;

using uint = unsigned int;

SpriteFrame::SpriteFrame( GLSLProgram* &glslp, Texture* &tex, GLuint &vao, GLuint &vbo, float& global_scale, float& global_alpha, 
						  uint frame, uint width, uint height, uint x_offset, uint y_offset, float scale, float alpha ) :
m_Shader( glslp ),
m_Tex( tex ),
m_VAO( vao ),
m_VBO( vbo ),
p_Scale( global_scale ),
p_Alpha( global_alpha ),
m_FrameIndex( frame )
{
	m_Width = width;
	m_Height = height;
	m_Offset.x = (float)x_offset;
	m_Offset.y = (float)y_offset;
	m_Scale = scale;
	m_Alpha = alpha;
}

void SpriteFrame::Draw( const glm::mat4& matrix )
{
	glm::mat4 model_matrix = glm::translate( matrix, m_Offset );
	glBindVertexArray( m_VAO );
	m_Tex->Bind();
	m_Shader->UseProgram();

	m_Shader->SetUniform( "in_Scale", m_Scale * p_Scale );
	m_Shader->SetUniform( "in_Alpha", m_Alpha * p_Alpha );
	m_Shader->SetUniform( "modelMatrix", model_matrix );

	glDrawArrays( GL_QUADS, m_FrameIndex * 4, 4 );
}

TYPE_ID_IMPL( Sprite )
void Sprite::Load( std::string file )
{
	assert( !m_Initialized );
	std::ifstream Data;
	Data.open( file );
	if ( Data.is_open() )
	{
		ushort Sections = 0;
		ushort TexLength = 0;

		Data >> Sections;
		Data >> TexLength;
		char* TexFile = new char[TexLength + 1];
		memset( TexFile, 0, TexLength + 1 );
		Data.read( TexFile, 1 );
		Data.read( TexFile, TexLength );
		m_Tex = Asset_Factory<Texture>::Instance().GetAsset( TexFile );
		delete[] TexFile;
		m_Shader = Asset_Factory<GLSLProgram>::Instance().GetAsset( "2d_default.glslp" );
		assert( m_Tex != nullptr );
		assert( m_Shader != nullptr );


		uint& Tex_width = m_Tex->width;
		uint& Tex_height = m_Tex->height;
		ushort Frames = 0, width = 0, height = 0, x_offset = 0, y_offset = 0;
		float scale = 0.0f, alpha = 0.0f;
		std::vector<std::pair<ushort, ushort>> texcoords;

		m_FrameIndex = 0;
		for ( int i = 0; i < Sections; ++i )
		{
			Data >> Frames;
			Data >> width;
			Data >> height;
			Data >> scale;
			Data >> alpha;
			Data >> x_offset;
			Data >> y_offset;
			for ( int f = 0; f < Frames; ++f )
			{
				ushort x, y;
				Data >> x;
				Data >> y;
				texcoords.emplace_back( x, y );
				SpriteFrame frame( m_Shader, m_Tex,
								   m_VAO, m_VBO,
								   m_Scale, m_Alpha,
								   m_FrameIndex++,
								   width, height,
								   x_offset, y_offset,
								   scale, alpha );
				m_Frames.push_back( frame );
			}
		}

		assert( texcoords.size() == m_Frames.size() );
		m_vCount = 4 * m_Frames.size();
		m_vLength = 5;
		m_Vertices = new float[m_vCount * m_vLength];
		memset( m_Vertices, 0, m_vCount * m_vLength );
		for ( uint f = 0; f < m_Frames.size(); ++f )
		{
			std::pair<ushort, ushort> value = texcoords.at( f );
			ushort x = value.first;
			ushort y = value.second;

			AnchorCenter( &m_Vertices[f * 20], Tex_width, Tex_height, width, height, x, y );
		}
		texcoords.resize( 0 );
	}
	else
	{
		assert( 0 ); //Couldn't open file
	}
	assert( !Data.fail() );
	Data.close();

	Init();
	m_FrameIndex = 0;
}

void Sprite::Reset()
{
	m_FrameIndex = 0;
	m_Scale = 1.0f;
	m_Alpha = 1.0f;
	Deinit();
}

SpriteFrame& Sprite::operator[]( ushort frame )
{
	m_FrameIndex = frame % m_Frames.size();
	return m_Frames.at( m_FrameIndex );
}

void Sprite::Draw( const glm::mat4& matrix )
{
	assert( !m_Frames.empty() );

	m_Frames[m_FrameIndex].Draw( matrix );
}

void Sprite::Scale( float scale )
{
	m_Scale = scale; //Apply to Model Matrix
}

void Sprite::SetAlpha( float alpha )
{
	m_Alpha = alpha;
}
