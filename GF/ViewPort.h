#ifndef GF_VIEWPORT_H
#define GF_VIEWPORT_H

#include <GFX\gl_engine.h>

class ViewPort
{
protected:
	float x1, y1, x2, y2;
	float width, height;
public:
	void Set( float x1 = 0.0f, float y1 = 0.0f, float x2 = (float)Screen::Instance().Width(), float y2 = (float)Screen::Instance().Height() )
	{
		static Screen& s = Screen::Instance();
		float w = x2 - x1;
		float h = y2 - y1;
		assert( w <= s.Width() && h <= s.Height() );
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		width = w;
		height = h;
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