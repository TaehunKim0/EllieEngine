#pragma once

template <typename T>
class Singleton
{
    friend T;
public:
    static T& GetInstance();

private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

template <typename T>
T& Singleton<T>::GetInstance()
{
    static T inst;
    return inst;
}
