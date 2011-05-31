#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeOSM
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		static int GetLongitude(float l, int z);
		static int GetLatitude(float l, int z);
	};
}
