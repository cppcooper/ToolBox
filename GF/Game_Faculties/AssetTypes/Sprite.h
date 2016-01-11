#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../AssetAbstract.h"
#include "BasicTypes.h"

namespace GameAssets
{
	class SpriteFrame
	{
		using uint = unsigned int;
	private:
		const uint m_FrameIndex;
		const GLuint &m_VAO;
		const GLuint &m_VBO;
		GLSLProgram* &m_Shader;
		Texture* &m_Tex;
		uint m_Width;
		uint m_Height;
		const float& p_Scale;
		const float& p_Alpha;

	public:
		float m_Scale = 1.0f;
		float m_Alpha = 1.0f;
		glm::vec2 m_Offset;

		SpriteFrame( uint frame, uint width, uint height, float scale, float alpha, GLSLProgram* &glslp, Texture* &tex, GLuint& vao, GLuint& vbo, float& global_scale, float& global_alpha );
		uint Width() const { return m_Width; }
		uint Height() const { return m_Height; }
		void Draw( const glm::mat4& matrix );
	};

	class Sprite : public GameAsset, public VO_Data, public Drawable
	{
		using ushort = unsigned short;
	protected:
		std::vector<SpriteFrame> m_Frames;
		ushort m_FrameIndex = 0;
		float m_Scale = 1.0f;
		float m_Alpha = 1.0f;

	public:
		uint TypeID();
		void Load( std::string file );
		void Reset();

		SpriteFrame& operator[]( ushort frame );
		void Draw( const glm::mat4& matrix ) final override;
		void Scale( float scale );
		void SetAlpha( float alpha );
	};
}

#endif
