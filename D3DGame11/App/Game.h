#pragma once
#include "App.h"

// ������ �θ� Ŭ�������� ���ǵ� ���������Լ����� ���������ִ� ���
// �ڽ� Ŭ������ �̸� ������ ���콺�� Ŭ���Ѵ�.
// ���� �۾� �� �����͸��� Ŭ���Ѵ�.
// '�ڽ� Ŭ���� �̸�' Ŭ������ ��� ���� ���� �Լ� ������ Ŭ���Ѵ�.

class Game : public App
{
public:
	Game() {}
	virtual ~Game() {}

	// ���������Լ��� �����Լ��� �������ϴ� ��찡 ������ override�� �ٿ�����

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destory() override;

private:

};
