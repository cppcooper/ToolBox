///this code sets up memory leak detection
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#include <stdlib.h>


#include <GF/GameFramework.h>
using namespace GameAssets;

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

//#define TRIANGLETEST
//#define DUMBSHADER

class RenderTester : public GameModule
{
private:
	glEngine& m_engine = glEngine::Instance();
	Asset_Faculties& m_asset_faculties = Asset_Faculties::Instance();
	Sprite* m_sprite = nullptr;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
protected:
	void InitShader()
	{
		GLSLProgram* shader_2d = m_asset_faculties.GetAsset<GLSLProgram>( "2d_default.glslp" );
		m_engine.SetMode( GL_Engine::graphics::R2D );
		float width = (float)Screen::Width() / 2.f;
		float height = (float)Screen::Height() / 2.f;
		m_engine.projectionMatrix = glm::mat4( 1.f ) * glm::ortho( 0.f, (float)Screen::Width(), 0.f, (float)Screen::Height(), -1.f, 1.f );
		//m_engine.projectionMatrix = glm::mat4( 1.f ) * glm::ortho( -width, width, -height, height, -1.f, 1.f );
		//m_engine.projectionMatrix = glm::perspective( 60.0f, (GLfloat)( Screen::Width() ) / (GLfloat)( Screen::Height() ), -2.0f, 10.0f );
		//m_engine.projectionMatrix[0][0] = 2.f / (float)Screen::Width();
		//m_engine.projectionMatrix[1][1] = 2.f / (float)Screen::Height();
		// 2D Section
		/// Binding Values to Variables within shader
#ifndef DUMBSHADER
		shader_2d->SetUniform( "projectionMatrix", m_engine.projectionMatrix );
		shader_2d->SetUniform( "viewMatrix", glm::mat4( 1.f ) );
		shader_2d->SetUniform( "in_Alpha", 1.0f );
		shader_2d->SetUniform( "in_Scale", 1.0f );
#endif
		shader_2d->SetUniform( "modelMatrix", glm::mat4( 1.f ) );
		shader_2d->BindAttributeLocation( 0, "in_Position" );
		shader_2d->BindAttributeLocation( 1, "in_Texcoord" );
		shader_2d->PrintActiveUniforms();
		shader_2d->PrintActiveAttribs();
		shader_2d->UseProgram();
	}
	void InitTriangle()
	{
		glGenVertexArrays( 1, &VertexArrayID );
		glBindVertexArray( VertexArrayID );
		glGenBuffers( 1, &vertexbuffer );
		glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
		glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, GL_STATIC_DRAW );
		InitShader();
	}
	void DrawTriangle()
	{
		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);
		glDrawArrays( GL_TRIANGLES, 0, 3 ); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray( 0 );
	}
	void InitSprite()
	{
		m_sprite = m_asset_faculties.GetAsset<Sprite>( "invaders.sdat" );
		InitShader();
	}
	void DrawSprite()
	{
		glm::mat4 matrix( 1.f );
		//matrix = glm::translate( matrix, glm::vec3( 200, 200, 0 ) );
		m_sprite->Draw( matrix );
	}
public:
	void Init() final override
	{
#ifdef TRIANGLETEST
		InitTriangle();
#else
		InitSprite();
#endif
	}

	void Draw() final override
	{
#ifdef TRIANGLETEST
		DrawTriangle();
#else
		DrawSprite();
#endif
	}

	void Process() final override {}
	void Update( double& seconds ) final override {}
	void PostProcess() final override {}

	void Buffer() final override {}
	void Deinit() final override {}
};

void main(int argc, char *argv[])
{
	///the line below turns on memory leak detection in debug mode
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 1 );
	RenderTester module1;
	Asset_Faculties::Instance().RegisterAssetPath( "C:\\src\\2015\\Space Invaders\\Assets\\Textures\\" );
	Asset_Faculties::Instance().RegisterAssetPath( "C:\\src\\2015\\Space Invaders\\Assets\\Data\\Sprites\\" );
	Asset_Faculties::Instance().RegisterAssetPath( "C:\\src\\2015\\Space Invaders\\Assets\\Shader\\" );
	Game::Instance().Attach( &module1 );
	Game::Instance().Init();
	Game::Instance().Run();
}
