#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeUtils
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static CIwManaged* GetResourceByName(const char* id,const char* type);
	};
}
