#include <s3e.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "TinyOpenEngine.OSM.h"
#include "toeOSM.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineOSMInitialized = false;
}
void TinyOpenEngine::toeOSMInit()
{
	if (isTinyOpenEngineOSMInitialized)
		return;
	isTinyOpenEngineOSMInitialized = true;

	toeRegisterClass(CtoeOSM::GetClassDescription());
}

void TinyOpenEngine::toeOSMTerminate()
{
	if (!isTinyOpenEngineOSMInitialized)
		return;
	isTinyOpenEngineOSMInitialized = false;
}