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
		// push_back -> 객체를 만들어서 넣는 방식
		// emplace_back-> 내부에 객체를 만들어주는 생성자가 있다.
		subsystems.emplace_back(subsystem);
	}

	template <typename T>
	T* GetSubsystem()
	{
		for (auto subsystem : subsystems)
		{
			// 부모클래스의 이름 앞에 *를 붙이면 자식클래스의 이름이 나온다.
			if (typeid(T) == typeid(*subsystem))
				return static_cast<T*>(subsystem);
		}
		return nullptr;
	}

private:
	vector < class ISubsystem* > subsystems;
};