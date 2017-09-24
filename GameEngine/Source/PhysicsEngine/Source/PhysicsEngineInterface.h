#pragma once

class IPhysicsEngine
{
private:
	IPhysicsEngine() {};
	IPhysicsEngine(IPhysicsEngine&) {};
	~IPhysicsEngine() {};

	static IPhysicsEngine* m_pInst;
public:
	void Initialize();
	void Destroy();
	void Update(float deltaTime);

	static IPhysicsEngine* GetInstance();
private:
};