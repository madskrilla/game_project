#pragma once

class CGameObject;

class CRenderNode
{
public:

	CRenderNode();
	CRenderNode(CRenderNode&);
	~CRenderNode();

	std::vector<unsigned int> GetIndexArray() { return m_vecIndicies; }
	unsigned int GetTexture() { return m_nTexture; }
	glm::mat4 GetTransform();

	void AddIndex(int index);
	void SetTexture(unsigned int texture) { m_nTexture = texture; }

	void UpdateNode(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale);

private:

	std::vector<unsigned int> m_vecIndicies;
	unsigned int m_nTexture;
	glm::mat4 m_matTransform;
};
