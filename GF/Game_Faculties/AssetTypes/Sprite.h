#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../AssetAbstract.h"
#include "BasicTypes.h"


namespace GameAssets
{
	class Sprite : public GameAsset, public VO_Data, public Drawable
	{
		using ushort = unsigned short;
	protected:
		ushort m_Frames = 0;
		ushort m_FrameIndex = 0;
		ushort m_PixelWidth = 0;
		ushort m_PixelHeight = 0;
		float m_Scale = 1.0f;
		float m_Alpha = 1.0f;

	public:
		uint TypeID();
		void Load( std::string file );
		void Reset();

		Sprite& operator[]( ushort frame );
		void Draw();
		void Draw( const glm::mat4& matrix );
		void Scale( float scale );
		void SetAlpha( float alpha );
		ushort Width() const { return m_PixelWidth; }
		ushort Height() const { return m_PixelHeight; }
	};
}

#endif
