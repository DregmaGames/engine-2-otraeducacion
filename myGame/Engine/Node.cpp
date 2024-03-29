#define NOMINMAX
#include "Node.h"
#include <algorithm>

using namespace pGr;

Node::Node() : Entity3D()
{

}

Node::~Node()
{
	while (!m_pkChilds.empty())
	{
		Entity3D* pkChild = m_pkChilds.back();
		m_pkChilds.pop_back();
		delete pkChild;
		pkChild = NULL;
	}
}

void Node::addChild(Entity3D* pkChild)
{
	m_pkChilds.push_back(pkChild);
}

void Node::removeChild(Entity3D* pkChild){
	m_pkChilds.erase(std::find(m_pkChilds.begin(), m_pkChilds.end(), pkChild));
}

void Node::updateTransformation()
{
	Entity3D::updateTransformation();
	for (std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); it++)
	{
		(*it)->updateTransformation();
	}
}

void Node::draw()
{
	for (std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it)
	{
		(*it)->draw();
	}
}

Entity3D* Node::getEntityFromName(std::string name)
{
	for (std::vector<Entity3D*>::iterator it = m_pkChilds.begin(); it != m_pkChilds.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			return (*it);
		}
	}
}

void Node::LookingBox(Entity3D& pkEntity)
{
	int Result = pGr::Renderer::getCamera()->AABBwithFrustum(pkEntity);
	switch (Result)
	{
	case Camera::INSIDE:
		pkEntity.draw();
		break;
	case Camera::OUTSIDE:
		//std::cout << "Outside: Dont need to draw" << std::endl;
		//pkEntity.draw();
		break;
	case Camera::INTERSECT:
		pGr::Node* pkChild = dynamic_cast<pGr::Node*>(&pkEntity);
		if (pkChild)
		{
			for (std::vector<Entity3D*>::const_iterator it = pkChild->childs().begin(); it != pkChild->childs().end(); it++){
				LookingBox(*(*it));
			}
		}
		else{
			pkEntity.draw();
		}
	}
}