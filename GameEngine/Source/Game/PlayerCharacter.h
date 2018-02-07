#pragma once

#include "MoveableObject.h"

class cInputManager;

class CPlayerCharacter : public cMovableObject
{
public:
	CPlayerCharacter();
	CPlayerCharacter(std::string texture);
	CPlayerCharacter(CPlayerCharacter&) {};
	virtual ~CPlayerCharacter();

	void Update(float deltaTime) override;

private:

	cInputManager* m_pInputManager;
};