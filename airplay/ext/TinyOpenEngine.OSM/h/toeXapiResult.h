#pragma once

#include <toeScriptingSubsystem.h>
#include <pugixml.hpp>

namespace TinyOpenEngine
{
	class CtoeXapiResult
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		CtoeXapiResult();

		virtual ~CtoeXapiResult();
	};
}
