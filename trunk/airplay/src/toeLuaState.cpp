#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeLuaState.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeLuaState);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeLuaState);


namespace TinyOpenEngine
{
	void toeRegisterLua(lua_State*);
}


//Constructor
CtoeLuaState::CtoeLuaState()
{
	L = 0;
}

//Desctructor
CtoeLuaState::~CtoeLuaState()
{
	if (L)
	{
		lua_close(L);
		L = 0;
	}
}
//Update subsystem state
void CtoeLuaState::Update(iwfixed dt)
{

}


//Render image on the screen surface
void CtoeLuaState::Render()
{
}

//Prepare subsystem
void CtoeLuaState::Initialize(CtoeWorld*w)
{
	CtoeSubsystem::Initialize(w);
	L = lua_open();
	luaopen_base(L);
	luaopen_table(L);
	//luaopen_io(L);
	luaopen_string(L);
	//luaopen_math(L);
	toeRegisterLua(L);
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeLuaState::Serialise ()
{
	CtoeSubsystem::Serialise();
}

void CtoeLuaState::Eval(const char*s)
{
	luaL_dostring(L,s);
	
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeLuaState::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("open", pAttrName))
	{
		uint32 openScript;
		pParser->ReadStringHash(&openScript);
		return true;
	}
	return CtoeSubsystem::ParseAttribute(pParser,pAttrName);
}
#endif