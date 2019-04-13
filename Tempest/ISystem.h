#pragma once

#include <vector>

template <class T>
class ISystem {
public:

	virtual void run() = 0;
	virtual void addComponent() = 0;
	virtual void removeComponent() = 0;
	std::vector<T> m_components;

};