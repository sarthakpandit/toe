#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include "toeUtils.h"
#include "toeHTTPRequest.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{

}

CtoeHTTPRequest::CtoeHTTPRequest()
{
	responseSize = 0;
	isActive = false;
}
CtoeHTTPRequest::~CtoeHTTPRequest()
{
	Cancel();
}
bool CtoeHTTPRequest::IsActive() const { return isActive;}
const char* CtoeHTTPRequest::GetResponseString() const { if (response.size() == 0) return ""; return &*response.begin();}
void CtoeHTTPRequest::Cancel()
{
	if (isActive)
	{
		transport.Cancel();
		isActive = false;
	}
}

CIwHTTP& CtoeHTTPRequest::GetTransport() {return transport;}

void CtoeHTTPRequest::OnError()
{
	isActive = false;
}
void CtoeHTTPRequest::OnResponseComplete()
{
	isActive = false;
}
void CtoeHTTPRequest::OnHeadersComplete()
{
	if (transport.GetStatus() == S3E_RESULT_ERROR)
	{
		OnError();
		return;
	}
	RawDownloadResponse();
}
void CtoeHTTPRequest::OnChunkComplete()
{
	if (transport.GetStatus() == S3E_RESULT_ERROR)
	{
		OnError();
		return;
	}
	response[transport.ContentReceived()] = 0;
	if (transport.ContentReceived() != transport.ContentLength())
	{
		uint32 oldLen = responseSize;
		if (responseSize < transport.ContentExpected())
			responseSize = transport.ContentExpected();
		else
			responseSize += 1024;

		response.resize(responseSize+1);
		transport.ReadDataAsync(&*response.begin(), responseSize - oldLen, 10000, RawChunkComplete, this);
	}
	else
	{
		OnResponseComplete();
	}
}
void CtoeHTTPRequest::RawDownloadResponse()
{
	responseSize = transport.ContentExpected();
	if (!responseSize) responseSize = 1024;
	response.resize(responseSize);
	response[0] = 0;
	transport.ReadDataAsync(&*response.begin(), 
									responseSize,
									10000,
									RawChunkComplete, this);

}
int CtoeHTTPRequest::RawChunkComplete(void*sys,void*http)
{
	((CtoeHTTPRequest*)http)->OnChunkComplete();
	return 0;
}
int CtoeHTTPRequest::RawHeadersComplete(void*sys,void*http)
{
	((CtoeHTTPRequest*)http)->OnHeadersComplete();
	return 0;
}
void CtoeHTTPRequest::RawGet(const char* gUrl)
{
	if (isActive)
	{
		IwAssertMsg(TOE,false,("Another request isn't complete yet"));
		OnError();
		return;
	}
	isActive = true;
	if (S3E_RESULT_SUCCESS != transport.Get(gUrl, RawHeadersComplete, this))
	{
		OnError();
	}
}