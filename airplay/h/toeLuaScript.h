#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

namespace TinyOpenEngine
{
	class CtoeLuaScript : public CIwResource
	{
	private:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaScript);
		//Constructor
		CtoeLuaScript();
		//Desctructor
		virtual ~CtoeLuaScript();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();


	};

#ifdef IW_BUILD_RESOURCES
	class CtoeLuaScriptResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeLuaScriptResHandler);

		//Constructor
		CtoeLuaScriptResHandler();
		//Desctructor
		virtual ~CtoeLuaScriptResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
}