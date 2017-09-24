#include "stdafx.h"
#include "RenderIncludes.h"

#include "RenderNode.h"

CRenderNode::CRenderNode()
{
}

CRenderNode::CRenderNode(CRenderNode & copy)
{
}

CRenderNode::~CRenderNode()
{
}

void CRenderNode::AddIndex(int index)
{
	m_vecIndicies.push_back(index);
}

glm::mat4 CRenderNode::GetTransform()
{
	return m_matTransform;
}

void CRenderNode::UpdateNode(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 trans;

	trans = glm::translate(trans, pos);

	trans = glm::rotate(trans, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

	trans = glm::scale(trans, scale);

	m_matTransform = trans;
}