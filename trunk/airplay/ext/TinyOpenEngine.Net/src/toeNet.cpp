#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"
#include "toeWebRequest.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	class CtoeHTTPDownloadString: public CtoeBufferedWebRequest
	{
	public:
	};
}


//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeNet::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeNet> d ("CtoeNet",
			ScriptTraits::Method("DownloadString", &CtoeNet::DownloadString),
			0);
	return &d;
}

int32 toeSendHTTPGetComplete(void* systemData, void* userData)
{
	CIwHTTP* http = (CIwHTTP*)userData;
	http->Cancel();
	delete http;
	return 0;
}

std::string CtoeNet::DownloadString(const char* s1)
{
	CtoeHTTPDownloadString http;
	http.SetURL(s1);
	http.Start();
	http.Wait();
	return std::string(http.GetResponseString());
}
