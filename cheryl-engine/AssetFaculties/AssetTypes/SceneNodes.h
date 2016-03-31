#ifndef SCENENODES_H_
#define SCENENODES_H_

#include "BasicTypes.h"
#include "../STL.h"
#include <mutex>
using namespace GameAssets;
///enum NODE_TYPE { SCENE, ROOT, TRAN, ROT, SCALE, TIMER, DYNA, STATIC, ANIM };


#pragma region "Base Node"
class BaseNode
{
	friend class SceneNode;
public:
	virtual void Draw() = 0;
	virtual void Update( double& seconds ) = 0;
	void Adopt( SceneNode* child );
	void OrphanSelf();

protected:
	virtual void Cascade_Data() = 0;
	void Flatten_SubGraph();
	void Kill_SubGraph();

protected:
	BaseNode* m_Parent = nullptr;
	std::vector<SceneNode*> m_Children;
	glm::mat4 m_ModelMatrix;
};
#pragma endregion



#pragma region "Root Node"
class RootNode : public BaseNode
{
private:
	std::mutex m_Mutex;

protected:
	void Cascade_Data() override;

public:
	void Draw() override;
	void Update( double& seconds ) override;
	~RootNode();
};
#pragma endregion



#pragma region "Scene Node"
class SceneNode : public BaseNode
{
	friend class BaseNode;
	friend class RootNode;
protected:
	Drawable* m_Drawable = nullptr;

protected:
	void Cascade_Data() final override;
	void Copy_ParentMatrix();
	virtual void Update_ModelMatrix();

public:
	void Draw() final override;
	void Update( double& minutes ) override;
	void SetDrawable( Drawable* drawable ) { m_Drawable = drawable; }

	SceneNode(){}
	SceneNode( BaseNode* parent );
	~SceneNode();
};
#pragma endregion



#pragma region "Translation Node"
class TranNode : public virtual SceneNode
{
protected:
	glm::mat4 m_TMatrix;
	glm::vec3 m_Axis;
	float m_Speed = 0.0f;

protected:
	void Update_ModelMatrix() override;
	void CheapMove( glm::vec3& displacement );

public:
	TranNode(){}
	TranNode( BaseNode* parent );
	TranNode( BaseNode* parent, glm::vec3& axis );
	
	void Update( double& minutes ) override;
	void Move( float& distance );
	void Move( glm::vec3& displacement );
	void SetAxis( glm::vec3& axis );
	void SetSpeed( float& speed );
	void SetVelocity( glm::vec3& velocity );
};
#pragma endregion



#pragma region "Rotation Node"
class RotNode : public virtual SceneNode
{
protected:
	glm::mat4 m_RMatrix;
	glm::quat m_RPM;

protected:
	void Update_ModelMatrix() override;
	void CheapRotate( glm::quat& rot );

public:
	RotNode(){}
	RotNode( BaseNode* parent );
	RotNode( BaseNode* parent, glm::quat& rpm );

	void Update( double& minutes ) override;
	void Rotate( glm::quat& rot );
	void Rotate( glm::vec3& axis, float& rot );
	void SetRPM( glm::quat& rpm );
	void SetRPM( glm::vec3& axis, float& rpm );
};
#pragma endregion



#pragma region "Scaler Node"
class ScalerNode : public virtual SceneNode
{
protected:
	glm::mat4 m_SMatrix;
	glm::vec3 m_SPM;

protected:
	void Update_ModelMatrix() override;
	void CheapScale( glm::vec3& scale );

public:
	ScalerNode(){}
	ScalerNode( BaseNode* parent );
	ScalerNode( BaseNode* parent, glm::vec3& spm );

	void Update( double& minutes ) override;
	void Scale( glm::vec3& scale );
	void SetSPM( glm::vec3& spm );
};
#pragma endregion


#endif
