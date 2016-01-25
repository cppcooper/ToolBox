#ifndef TILESET_H
#define TILESET_H

#include "../AssetAbstract.h"
#include "BasicTypes.h"

namespace GameAssets
{
	class TileSet : public GameAsset, public VO_Data, public Drawable
	{
		using ushort = unsigned short;
	protected:
		ushort m_TileCount = 0;
		ushort m_FrameIndex = 0;
		ushort m_Width = 0;
		ushort m_Height = 0;
		float m_Scale = 1.0f;
		float m_Alpha = 1.0f;

	public:
		uint TypeID();
		void Load( std::string file );
		void Reset();

		TileSet& operator[]( ushort frame );
		void Draw( const glm::mat4& matrix );
		void Scale( float scale );
		void SetAlpha( float alpha );

		ushort Width() const { return m_Width; }
		ushort Height() const { return m_Height; }
	};
}

#endif
