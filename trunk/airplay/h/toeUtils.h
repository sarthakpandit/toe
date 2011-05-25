#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class toeConfig
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
	};
}
