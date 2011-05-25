#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwHTTP.h>
#include "TinyOpenEngine.h"
#include "toeLuaState.h"
#include "s3eOSReadString.h"

using namespace TinyOpenEngine;


namespace TinyOpenEngine
{
	void toeExitApplication();
	int toeLuaExit(lua_State* L)
	{
		toeExitApplication();
		return 0;
	}
	int toeLuaCloseWorld(lua_State* L)
	{
		toeCloseWorld();
		return 0;
	}
	int toeLuaOpenWorld(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		const char* s2 = luaL_checkstring(L,2);
		toeOpenWorld(s1,s2);
		return 0;
	}
	int toeLuaOpenGroupWorld(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		toeOpenGroupWorld(s1);
		return 0;
	}
	int toeLuaAssertMsg(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		IwDebugAssertShow(s1,"",0,true);
		//IwAssertMsg(TOE,false,(s1));
		return 0;
	}
	int toeLuaDeviceCheckPauseRequest(lua_State* L)
	{
		lua_pushboolean(L,s3eDeviceCheckPauseRequest());
		return 0;
	}
	int32 toeSendHTTPGetComplete(void* systemData, void* userData)
	{
		CIwHTTP* http = (CIwHTTP*)userData;
		http->Cancel();
		delete http;
		return 0;
	}
	int toeSendHTTPGet(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		CIwHTTP* http = new CIwHTTP();
		http->Get(s1, toeSendHTTPGetComplete, http);
		return 0;
	}


	int toeUrlEncode(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		std::string s2;
		while (*s1)
		{
			if (*s1 == ' ')
				s2+=('+');
			else
				s2+=(*s1);
			++s1;
		}
		lua_pushstring(L,s2.c_str());
		return 1;
	}
	int toeLuaGetDeviceID(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_ID)); return 1; }
	int toeLuaGetDevicePhone(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_PHONE_NUMBER)); return 1; }
	int toeLuaGetDeviceOS(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_OS)); return 1; }
	int toeLuaGetDeviceClass(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_CLASS)); return 1; }
	int toeLuaGetDeviceArchitecture(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_ARCHITECTURE)); return 1; }
	int toeLuaGetDeviceS3eVersion(lua_State* L) { lua_pushstring(L,s3eDeviceGetString(S3E_DEVICE_S3E_VERSION)); return 1; }
	int toeLuaGetDeviceTotalRam(lua_State* L) { lua_pushinteger(L,s3eDeviceGetInt(S3E_DEVICE_TOTAL_RAM)); return 1; }
	int toeLuaGetDeviceFreeRam(lua_State* L) { lua_pushinteger(L,s3eDeviceGetInt(S3E_DEVICE_FREE_RAM)); return 1; }
	 
	int toeLuaReadString(lua_State* L)
	{
		const char* s1 = luaL_checkstring(L,1);
		const char* s = s3eOSReadStringUTF8(s1);
		if (s)
		{
			lua_pushstring(L,s);
		}
		else
		{
			lua_pushstring(L,"");
		}
		return 1;
	}
	luaL_Reg toeModule[] = {
	  {"toeCloseWorld", toeLuaCloseWorld},
	  {"toeOpenWorld", toeLuaOpenWorld},
	  {"toeOpenGroupWorld", toeLuaOpenGroupWorld},
	  {"toeReadString", toeLuaReadString},
	  {"toeExit", toeLuaExit},
	  {"toeDeviceCheckPauseRequest", toeLuaDeviceCheckPauseRequest},
	  {0, 0}
	};

	void toeRegisterLua(lua_State* state)
	{
		lua_register(state,"toeCloseWorld",toeLuaCloseWorld);
		lua_register(state,"toeOpenWorld",toeLuaOpenWorld);
		lua_register(state,"toeOpenGroupWorld",toeLuaOpenGroupWorld);
		lua_register(state,"toeReadString",toeLuaReadString);
		lua_register(state,"toeAssertMsg",toeLuaAssertMsg);

		lua_register(state,"toeGetDeviceID",toeLuaGetDeviceID);
		lua_register(state,"toeGetDevicePhone",toeLuaGetDevicePhone);
		lua_register(state,"toeGetDeviceOS",toeLuaGetDeviceOS);
		lua_register(state,"toeGetDeviceClass",toeLuaGetDeviceClass);
		lua_register(state,"toeGetDeviceArchitecture",toeLuaGetDeviceArchitecture);
		lua_register(state,"toeGetDeviceS3eVersion",toeLuaGetDeviceS3eVersion);
		lua_register(state,"toeGetDeviceTotalRam",toeLuaGetDeviceTotalRam);
		lua_register(state,"toeGetDeviceFreeRam",toeLuaGetDeviceFreeRam);

		lua_register(state,"toeUrlEncode",toeUrlEncode);
		lua_register(state,"toeSendHTTPGet",toeSendHTTPGet);
		lua_register(state,"toeExit",toeLuaExit);
		lua_register(state,"toeDeviceCheckPauseRequest",toeLuaDeviceCheckPauseRequest);
		//luaL_register(state,0, toeModule);
	}
}

