#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeOSM
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		static int ConvertLongitude(float l, int z);
		static int ConvertLatitude(float l, int z);
		static int GetLongitudeAt(int z);
		static int GetLatitudeAt(int z);
		static int GetLongitude();
		static int GetLatitude();
	};
}
