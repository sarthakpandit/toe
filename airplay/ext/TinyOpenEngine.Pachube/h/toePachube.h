#pragma once

#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoePachubeFeeds
	{
	};

	class CtoePachube
	{
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		static void ReadFeed(int feedid, const char* apiKey);
	};
}
