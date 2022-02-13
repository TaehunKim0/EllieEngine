#pragma once

/*
Manager ���� ������ �ִ� Core Ŭ����
Manager���� List�� �߰��ϰ�,
Manager-> Init, Tick ����

WindowsApp�� Tick �ȿ��� Core Tick ����
*/

#include <vector>
#include "IManager.h"

class EllieCore
{
public:
    EllieCore();
    ~EllieCore();

public:
    void Init();
    void Tick();
    void Excute();

private:
    //Managers
    
public:
    std::vector<IManager*> m_Managers;

};