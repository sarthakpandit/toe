#pragma once

#include <string>
#include <toeIntrusiveList.h>

class CIwTextParserITX;

namespace TinyOpenEngine
{
	class CtoeWorld;
	class ItoeScriptingSubsystem;
	class CtoeScriptableClassDeclaration;
	class CYieldHandler: public TtoeIntrusiveListItem<CYieldHandler> { public: virtual void OnYield() = 0; };

	void toeInit();
	void toeTerminate();
	void toeRunWorld(CtoeWorld*);
	void toeOpenWorld(const char*resource,const char*world);
	void toeOpenGroupWorld(const char*resource);
	void toeCloseWorld();
	void toeTrace(const char*, ...);
	bool toeIsTraceEnabled();
	void toeRegisterClass(CtoeScriptableClassDeclaration*);
	TtoeIntrusiveList<CYieldHandler>* toeGetYieldHandlers();
	void toeDeviceYield(int32 ms);
	void toeRegisterScriptableClasses(ItoeScriptingSubsystem*);

	void toeSerialiseString(std::string & s);
	void toeReadString(CIwTextParserITX* pParser, std::string * s);
}