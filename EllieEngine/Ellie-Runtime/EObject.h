#pragma once
class EObject
{
public:
	EObject();
	~EObject();

public:
	//�ڽ��� ������ �� ȣ��.
	virtual void Excute() = 0;

	//�޸� �����ڿ��Լ� �ڽ��� �����Ѵ�.
	virtual void Destroy();

};