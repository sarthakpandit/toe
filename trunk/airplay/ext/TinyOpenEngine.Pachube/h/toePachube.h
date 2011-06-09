#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoePachubeFeeds
	{
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
	};

	class CtoePachube
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static void ReadFeed(int feedid, const char* apiKey);
	};
}
