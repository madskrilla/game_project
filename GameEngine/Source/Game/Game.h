#pragma once


class CGameObject;

class CGame
{
public:

	static CGame* GetInstance();

	void Initialize();
	void Update(float deltaTime);
	void Destroy();

	void AddObject(CGameObject* newobj);

private:

	CGame();
	CGame(CGame& copy);
	~CGame();

	static CGame* m_pInst;

	std::vector<CGameObject*> m_vecGameObjects;
};
