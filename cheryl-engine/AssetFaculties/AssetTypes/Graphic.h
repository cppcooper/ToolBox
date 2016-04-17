#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "../Components/AssetAbstract.h"

#include "BasicTypes.h"

namespace GameAssets
{
	class Graphic : public GameObject, public VO_Data, public Drawable
	{
		using ushort = unsigned short;
	protected:
		float m_Scale = 1.0f;
		float m_Alpha = 1.0f;

	public:
		Graphic();
		uint TypeID();
		void Load( std::string file );
		void Reset();

		void Draw() final override { Draw( glm::mat4( 1.f ) ); }
		void Draw( const glm::mat4& matrix ) final override;
		ushort Width() const { return (ushort)( m_Scale * m_Tex->width ); }
		ushort Height() const { return (ushort)( m_Scale * m_Tex->height ); }
		void Scale( float scale );
		void SetAlpha( float alpha );
	};
}

#endif