#include <IwResManager.h>
#include "toeUtils.h"
#include "pugixml.hpp"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeUtils::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeUtils> d ("CtoeUtils",
			ScriptTraits::Method("GetResourceByName", &CtoeUtils::GetResourceByName),
			0);
	return &d;
}

CIwManaged* CtoeUtils::GetResourceByName(const char* id,const char* type)
{
	return IwGetResManager()->GetResNamed(id,type,IW_RES_PERMIT_NULL_F);
}
