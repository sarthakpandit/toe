#include <s3e.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "TinyOpenEngine.Net.h"
#include "TinyOpenEngine.Pachube.h"
#include "toePachube.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEnginePachubeInitialized = false;
}
void TinyOpenEngine::toePachubeInit()
{
	if (isTinyOpenEnginePachubeInitialized)
		return;
	isTinyOpenEnginePachubeInitialized = true;

	TinyOpenEngine::toeNetInit();

	toeRegisterClass(CtoePachube::GetClassDescription());
}

void TinyOpenEngine::toePachubeTerminate()
{
	if (!isTinyOpenEnginePachubeInitialized)
		return;
	isTinyOpenEnginePachubeInitialized = false;

	TinyOpenEngine::toeNetTerminate();
}