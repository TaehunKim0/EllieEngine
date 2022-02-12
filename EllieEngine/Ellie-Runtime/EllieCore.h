#pragma once

/*
Manager 들을 가지고 있는 Core 클래스
Manager들을 List에 추가하고,
Manager-> Init, Update , Render 수행

WindowsApp의 Tick 안에서 Core Update , Render 수행
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