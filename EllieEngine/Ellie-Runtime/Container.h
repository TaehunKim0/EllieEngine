#pragma once

#include <list>

template<class T>
class Container
{
public:
	std::list<T> _Objects;
    int _Size = 0;

public:
    Container() = default;
    ~Container() {}

    virtual void Register(T object) {
        _Objects.push_back(object);
        _Size++;
    }

  /*  virtual void Remove(T object) {
        _Objects.remove(object);
        _Size--;
    }*/

    int GetSize() {
        return _Size;
    }
};