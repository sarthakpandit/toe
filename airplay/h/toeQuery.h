#pragma once

#include "toeScriptingSubsystem.h"
#include "toeHTTPRequest.h"

namespace TinyOpenEngine
{
	class CtoeQuery
	{
		CtoeHTTPRequest request;
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		CtoeQuery();

		virtual ~CtoeQuery();
	};
}
