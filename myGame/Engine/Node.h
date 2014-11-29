#pragma once
//-----------------------
#include "myEngine_API.h"
#include "Entity3D.h"
//-----------------------
#include <string>
#include <vector>

namespace pGr
{
	class MYENGINE_API Node : public Entity3D
	{

		public:

			Node();
			~Node();

			void draw();
			Entity3D* getEntityFromName(std::string name);
			void updateTransformation();
			void addChild (Entity3D* pkChild);
			void removeChild(Entity3D* pkChild);
			const std::vector<Entity3D*>& childs () const{ return m_pkChilds; }
	
		private:
			std::vector<Entity3D*> m_pkChilds;
	};
}