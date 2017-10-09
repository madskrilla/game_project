#pragma once


template <class t> 
class CObjectPool
{
public:

	CObjectPool();
	CObjectPool(CObjectPool & copy);
	~CObjectPool();

	std::weak_ptr<t> GetNextObject();
	void Initialize(int startSize);
	void Update();
private:

	std::vector<std::shared_ptr<t>> m_vecObjects;
};
