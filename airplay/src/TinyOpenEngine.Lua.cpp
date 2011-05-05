#include "TinyOpenEngine.Lua.h"
#include "toeLuaScript.h"

#define lua_c
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineLuaInitialized = false;
}

void TinyOpenEngine::toeLuaInit()
{
	if (isTinyOpenEngineLuaInitialized)
		return;
	isTinyOpenEngineLuaInitialized = true;

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeLuaScriptResHandler);
	#endif

	IW_CLASS_REGISTER(CtoeLuaScript);
}

void TinyOpenEngine::toeLuaTerminate()
{
	if (!isTinyOpenEngineLuaInitialized)
		return;
	isTinyOpenEngineLuaInitialized = false;
}