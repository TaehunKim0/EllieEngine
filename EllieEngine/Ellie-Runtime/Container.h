#pragma once

#include <list>

template<class T>
class Container
{
public:
	std::list<T> m_Objects;
    int m_Size = 0;

public:
    Container() = default;
    ~Container() {}

    virtual void Register(T object) {
        m_Objects.push_back(object);
        m_Size++;
    }

  /*  virtual void Remove(T object) {
        m_Objects.remove(object);
        m_Size--;
    }*/

    int GetSize() {
        return m_Size;
    }
};