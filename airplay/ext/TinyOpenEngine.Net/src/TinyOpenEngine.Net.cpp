#include <s3e.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "TinyOpenEngine.Net.h"
#include "toeNet.h"
#include "toeWebRequest.h"



using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineNetInitialized = false;
	TtoeIntrusiveList<CtoeWebRequest>* g_toeActiveWebRequests = 0;
}

TtoeIntrusiveList<CtoeWebRequest>* TinyOpenEngine::toeGetActiveWebRequests()
{
	return g_toeActiveWebRequests;
}

void TinyOpenEngine::toeNetInit()
{
	if (isTinyOpenEngineNetInitialized)
		return;
	isTinyOpenEngineNetInitialized = true;

	g_toeActiveWebRequests = new TtoeIntrusiveList<CtoeWebRequest>();

	curl_global_init(CURL_GLOBAL_ALL);

	toeRegisterClass(CtoeNet::GetClassDescription());
}

void TinyOpenEngine::toeNetTerminate()
{
	if (!isTinyOpenEngineNetInitialized)
		return;
	isTinyOpenEngineNetInitialized = false;

	delete g_toeActiveWebRequests;
	g_toeActiveWebRequests = 0;

	curl_global_cleanup();
}