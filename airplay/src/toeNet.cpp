#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"
#include "toeHTTPRequest.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	class CtoeHTTPDownloadString: public CtoeHTTPRequest
	{
	public:
		void Get(const char* s)
		{
			RawGet(s);
		}
	/*protected:
		virtual void OnResponseComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnResponseComplete();
		}
		virtual void OnHeadersComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnHeadersComplete();
		}
		virtual void OnChunkComplete()
		{
			CtoeLoadingScreen::Render();
			CtoeHTTPRequest::OnChunkComplete();
		}*/
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
	http.Get(s1);
	while (http.IsActive())
	{
		CtoeLoadingScreen::Render();
		s3eDeviceYield(30);
	}
	return std::string(http.GetResponseString());
}
