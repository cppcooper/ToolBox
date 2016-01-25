#ifndef GF_VIEWPORT_H
#define GF_VIEWPORT_H

#include <GFX\gl_engine.h>

class ViewPort
{
protected:
	float x1, y1, x2, y2;
	float width, height;
public:
	void Set( float x1 = 0.0f, float y1 = 0.0f, float w = (float)Screen::Width(), float h = (float)Screen::Height() )
	{
		assert( w <= Screen::Width() && h <= Screen::Height() );
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x1 + w;
		this->y2 = y1 + h;
		width = w;
		height = h;
	}
	void Scroll( glm::vec2 dir )
	{
		x1 += dir.x;
		y1 += dir.y;
		x2 = x1 + width;
		y2 = y1 + height;
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