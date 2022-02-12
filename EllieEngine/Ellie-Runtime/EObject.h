#pragma once
class EObject
{
public:
	EObject();
	~EObject();

public:
	//자신을 해제할 때 호출.
	virtual void Excute() = 0;

	//메모리 관리자에게서 자신을 제거한다.
	virtual void Destroy();

};