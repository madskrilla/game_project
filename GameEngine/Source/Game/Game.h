#pragma once


class CGameObject;
template<class t>
class CObjectPool;

class CGame
{
public:

	static CGame* GetInstance();

	void Initialize();
	void Update(float deltaTime);
	void Destroy();

private:

	CGame();
	CGame(CGame& copy);
	~CGame();

	static CGame* m_pInst;

	std::vector<CGameObject*> m_vecGameObjects;
};
