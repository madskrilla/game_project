#include "stdafx.h"
#include <memory>
#include <iterator>
#include <algorithm>

#include "ObjectPool.h"


template<class t> 
CObjectPool<t>::CObjectPool()
{
}

template<class t> 
CObjectPool<t>::CObjectPool(CObjectPool<t> & copy)
{

}

template<class t> 
CObjectPool<t>::~CObjectPool()
{

}

template<class t>
void CObjectPool<t>::Initialize(int startSize)
{
	m_vecObjects.resize(startSize);
	for (unsigned int i = 0; i < startSize; i++)
	{
		m_vecObjects[i] = std::make_shared<t>();
	}
}

template<class t> 
std::weak_ptr<t> CObjectPool<t>::GetNextObject()
{
	std::shared_ptr<t> newObj;

	if (m_vecObjects.empty())
	{
		m_vecObjects.push_back(std::make_shared<t>());
	}
	std::weak_ptr<t> copy = m_vecObjects.back();
	std::sort(m_vecObjects.begin(), m_vecObjects.end());

	return copy;
}