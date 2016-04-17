#ifndef S3DMESH_H_
#define S3DMESH_H_

#include "../Components/AssetAbstract.h"

#include "BasicTypes.h"

using std::string;
using std::ifstream;

namespace GameAssets
{
	class Mesh : public GameObject, public VO_Data, public Drawable
	{
	protected:
		bool m_TriStrip = true;

	public:
		uint TypeID();
		void Load( std::string file );
		void Reset();

		void Draw();
		void Draw( const glm::mat4& matrix );
	};
}
#endif
