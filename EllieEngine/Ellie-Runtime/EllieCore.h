#pragma once

/*
Manager ���� ������ �ִ� Core Ŭ����
Manager���� List�� �߰��ϰ�,
Manager-> Init, Update , Render ����

WindowsApp�� Tick �ȿ��� Core Update , Render ����
*/

#include <vector>
#include "CoreBase.h"

class EllieCore
{
public:
    EllieCore();
    ~EllieCore();


public:
    void Init();
    void Update();
    void Render();
    void Excute();

private:
    //Managers
    
public:
    std::vector<CoreBase*> m_Cores;

};