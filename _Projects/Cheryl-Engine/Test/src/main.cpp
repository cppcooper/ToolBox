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

class RenderTester : public GameModule
{
private:
	glEngine& m_engine = glEngine::Instance();
	Asset_Faculties& m_asset_faculties = Asset_Faculties::Instance();
	Sprite* m_sprite = nullptr;
public:
	void Init() final override
	{
		m_sprite = m_asset_faculties.GetAsset<Sprite>( "invaders.sdat" );
		GLSLProgram* shader_2d = m_asset_faculties.GetAsset<GLSLProgram>( "2d_default.glslp" );
		m_engine.SetMode( GL_Engine::graphics::R2D );
		m_engine.projectionMatrix = glm::mat4( 1.f ) * glm::ortho( 0.f, (float)Screen::Width(), 0.f, (float)Screen::Height(), 0.f, 1.f );
		// 2D Section
		/// Binding Values to Variables within shader
		shader_2d->SetUniform( "projectionMatrix", m_engine.projectionMatrix );
		shader_2d->SetUniform( "viewMatrix", glm::mat4( 1.f ) );
		shader_2d->SetUniform( "in_Alpha", 1.0f );
		shader_2d->SetUniform( "in_Scale", 1.0f );
		shader_2d->BindAttributeLocation( 0, "in_Position" );
		shader_2d->BindAttributeLocation( 1, "in_Texcoord" );
		shader_2d->PrintActiveUniforms();
		shader_2d->PrintActiveAttribs();
	}
	void Draw() final override
	{
		glm::mat4 matrix;
		matrix = glm::translate( matrix, glm::vec3( 200, 200, 0 ) );
		m_sprite->Draw( matrix );
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
