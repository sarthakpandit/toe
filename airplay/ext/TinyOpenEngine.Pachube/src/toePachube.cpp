#include <IwResManager.h>
#include "toePachube.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}


//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoePachube::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoePachube> d ("CtoePachube",
//			ScriptTraits::Method("DownloadString", &CtoePachube::DownloadString),
			0);
	return &d;
}
