#include <IwResManager.h>
#include <math.h>
#include "toeXapiResult.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeXapiResult::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeXapiResult> d ("CtoeXapiResult",
			//ScriptTraits::Method("ConvertLongitude", &CtoeOSM::ConvertLongitude),
			0);
	return &d;
}

CtoeXapiResult::CtoeXapiResult()
{
}

CtoeXapiResult::~CtoeXapiResult()
{
}
