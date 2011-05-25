#include "toeConfig.h"
#include "pugixml.hpp"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{

}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeConfig::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeConfig> d ("CtoeConfig",
			ScriptTraits::Method("GetInteger", &CtoeConfig::GetInteger),
			ScriptTraits::Method("GetFloat", &CtoeConfig::GetFloat),
			ScriptTraits::Method("GetString", &CtoeConfig::GetString),
			ScriptTraits::Method("SetInteger", &CtoeConfig::SetInteger),
			ScriptTraits::Method("SetFloat", &CtoeConfig::SetFloat),
			ScriptTraits::Method("SetString", &CtoeConfig::SetString),
			0);
	return &d;
}
void CtoeConfig::SetInteger(const char* name, int val)
{
}
void CtoeConfig::SetFloat(const char* name, float val)
{
}
void CtoeConfig::SetString(const char* name, const char* val)
{
}

int CtoeConfig::GetInteger(const char* name)
{
	return 0;
}
float CtoeConfig::GetFloat(const char* name)
{
	return 0.0f;
}
const char* CtoeConfig::GetString(const char* name)
{
	return "";
}
