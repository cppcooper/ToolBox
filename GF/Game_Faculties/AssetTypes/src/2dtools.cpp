#include "2dtools.h"

void AnchorBottomLeft( float* vertices, ushort Tex_width, ushort Tex_height, ushort width, ushort height, ushort x, ushort y )
{
	///Bottom Left
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;
	vertices[3] = (float)x / (float)Tex_width;	
	vertices[4] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );

	///Bottom Right
	vertices[5] = (float)width;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;
	vertices[8] = ( (float)x + (float)width ) / (float)Tex_width;
	vertices[9] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );

	///Top Right
	vertices[10] = (float)width;
	vertices[11] = (float)height;
	vertices[12] = 0.0f;
	vertices[13] = ( (float)x + (float)width ) / (float)Tex_width;
	vertices[14] = 1.0f - ( (float)y / (float)Tex_height );

	///Top Left
	vertices[15] = 0.0f;
	vertices[16] = (float)height;
	vertices[17] = 0.0f;
	vertices[18] = (float)x / (float)Tex_width;
	vertices[19] = 1.0f - ( (float)y / (float)Tex_height );
}


void AnchorCenter( float* vertices, ushort Tex_width, ushort Tex_height, ushort width, ushort height, ushort x, ushort y )
{
	///Bottom Left
	vertices[0] = width / 2.0f;																		/// X
	vertices[1] = height / 2.0f;																		/// Y
	vertices[2] = 0.0f;																						/// Z
	vertices[3] = (float)x / (float)Tex_width;													/// U - Texture mapping
	vertices[4] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );		/// V - Texture mapping (Inverted Axis?)

	///Bottom Right
	vertices[5] = (float)width - ( width / 2.0f );
	vertices[6] = height / 2.0f;
	vertices[7] = 0.0f;
	vertices[8] = ( (float)x + (float)width ) / (float)Tex_width;
	vertices[9] = 1.0f - ( ( (float)y + (float)height ) / (float)Tex_height );

	///Top Right
	vertices[10] = (float)width - ( width / 2.0f );
	vertices[11] = (float)height - ( height / 2.0f );
	vertices[12] = 0.0f;
	vertices[13] = ( (float)x + (float)width ) / (float)Tex_width;
	vertices[14] = 1.0f - ( (float)y / (float)Tex_height );

	///Top Left
	vertices[15] = width / 2.0f;
	vertices[16] = (float)height - ( height / 2.0f );
	vertices[17] = 0.0f;
	vertices[18] = (float)x / (float)Tex_width;
	vertices[19] = 1.0f - ( (float)y / (float)Tex_height );
}