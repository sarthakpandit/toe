#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"
#include "toeQuery.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{

}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeQuery::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeQuery> d ("CtoeQuery",
			//ScriptTraits::Method("DownloadString", &CtoeQuery::DownloadString),
			0);
	return &d;
}

CtoeQuery::CtoeQuery()
{
}

CtoeQuery::~CtoeQuery()
{
}
