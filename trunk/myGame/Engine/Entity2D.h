#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "myengine_api.h"
#include "mathjavi.h"
#include "RenderTypes.h"
#include "Renderer.h"
#include <string>
namespace pGr{
	class Timer;
	class MYENGINE_API Entity2D{
	//constructores
	public:
		Entity2D();
		virtual ~Entity2D();

	//transformaciones.
	public:
		void setPos(float fPosX,float fPosY,float fPosZ);
		void setRotation (float fRotation);
		void setScale(float m_fScaleX,float m_fScaleY);
		void setScale(float m_fScaleX,float m_fScaleY, float m_fScaleZ);
		void returnToPos(float fPosX, float fPosY, float fPosZ);
		virtual void Update(Timer& rkTimer){}
		virtual void draw(Renderer& rkRenderer){}
		enum CollisionResult{
			CollisionVertical,
			CollisionHorizontal,
			NoCollision
		};
		CollisionResult checkCollision(Entity2D& rkEntity2D) const;

		float posX();
		float posY();
		float posZ();
		float rotation () const;
		float scaleX () const;
		float scaleY () const;
		float scaleZ () const;
		float prevPosX() const;
		float prevPosY() const;
		float prevPosZ() const;
		void updateLocalTransformation();
		const Matrix transformationMatrix();
	public:
		std::string m_Name;	//nombre del objeto
		bool m_Coll;	//si es o no colisionable.
		void setColl(bool col){
			m_Coll = col;
		}
		void setName(std::string name){
			m_Name = name;
		}
		std::string getName(){
			return m_Name;
		}
	protected:
		float m_fPrevPosX, m_fPrevPosY, m_fPrevPosZ;
		float m_fPosX, m_fPosY, m_fPosZ;
		float m_fRotation;
		float m_fScaleX,m_fScaleY, m_fScaleZ;
		
	protected:
		Matrix m_pkTransformationMatrix;
	};
}
#endif //ENTITY2D_H