#pragma once

#include <vector>

template <class T>
class ISystem {
public:

	virtual void run(float deltaTime) = 0;

	std::vector<T> m_components;

};