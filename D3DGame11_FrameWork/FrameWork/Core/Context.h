#pragma once
#include "stdafx.h"
#include "./Subsystem/ISubSystem.h"

class Context
{
public:
	Context() {}
	virtual ~Context()
	{
		for (auto subsystem : subsystems)
			SAFE_DELETE(subsystem);
	}

	void RegistSubsystem(class ISubsystem* subsystem)
	{
		if (!subsystem)
			assert(false);

		subsystem->Initialize();
		// push_back -> ��ü�� ���� �ִ� ���
		// emplace_back-> ���ο� ��ü�� ������ִ� �����ڰ� �ִ�.
		subsystems.emplace_back(subsystem);
	}

	template <typename T>
	T* GetSubsystem()
	{
		for (auto subsystem : subsystems)
		{
			// �θ�Ŭ������ �̸� �տ� *�� ���̸� �ڽ�Ŭ������ �̸��� ���´�.
			if (typeid(T) == typeid(*subsystem))
				return static_cast<T*>(subsystem);
		}
		return nullptr;
	}

private:
	vector < class ISubsystem* > subsystems;
};