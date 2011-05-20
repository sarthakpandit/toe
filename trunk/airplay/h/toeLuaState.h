#pragma once

#include <IwGeom.h>
#include <toeSubsystem.h>
#include <toeSubsystemItems.h>
#include "toeLua.h"
#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeLuaStateRoot;

	class CtoeLuaState : public CtoeSubsystem, public ItoeScriptingSubsystem
	{
	protected:
		lua_State *L;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaState);
		//Constructor
		CtoeLuaState();
		//Desctructor
		virtual ~CtoeLuaState();

		//Prepare subsystem
		virtual void Initialize(CtoeWorld*);
		//Update subsystem state
		virtual void Update(iwfixed dt);
		//Render image on the screen surface
		virtual void Render();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
		virtual void Eval(const char*s);
#ifdef IW_BUILD_RESOURCES

		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}