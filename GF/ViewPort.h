#ifndef GF_VIEWPORT_H
#define GF_VIEWPORT_H

#include <GFX\gl_engine.h>

class ViewPort
{
protected:
	float x1, y1, x2, y2;
	int width, height;
public:
	void Set( float x, float y, int w, int h )
	{
		static glEngine& engine = glEngine::Instance();
		assert( w <= engine.get_ScreenWidth() && h <= engine.get_ScreenHeight() );
		x1 = x;
		y1 = y;
		width = w;
		height = h;
	}
	void Scroll( const glm::vec2& dir )
	{
		x1 += dir.x;
		x2 += dir.x;
		y1 += dir.y;
		y2 += dir.y;
	}
	float CenterX()
	{
		return x1 + ( width / 2 );
	}
	float CenterY()
	{
		return y1 + ( height / 2 );
	}
	float X1() const { return x1; }
	float Y1() const { return y1; }
	float X2() const { return x2; }
	float Y2() const { return y2; }
	float Width() const { return width; }
	float Height() const { return height; }
};

#endif