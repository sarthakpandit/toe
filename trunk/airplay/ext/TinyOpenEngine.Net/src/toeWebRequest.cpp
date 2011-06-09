#include "toeNet.h"
#include "toeWebRequest.h"
#include "TinyOpenEngine.Net.h"
#include "TinyOpenEngine.h"
#include "toeLoadingScreen.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
}

CtoeWebRequest::CtoeWebRequest()
{
	m_headerlist = 0;
	m_curl = curl_easy_init();
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 60L));

	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, WriteFunction));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)this));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, ReadFunction));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_READDATA, (void *)this));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, HeaderFunction));
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, (void *)this));

	
	multi_handle = curl_multi_init();
	curl_multi_add_handle(multi_handle, m_curl);

	
}
CtoeWebRequest::~CtoeWebRequest()
{
	curl_easy_cleanup(m_curl);
	curl_multi_cleanup(multi_handle);
	curl_slist_free_all (m_headerlist);
}
size_t CtoeWebRequest::OnWriteFunction(void *ptr, size_t size, size_t nmemb)
{
	return nmemb * size;
}
size_t CtoeWebRequest::OnHeaderFunction(void *ptr, size_t size, size_t nmemb)
{
	return nmemb * size;
}
size_t CtoeWebRequest::OnReadFunction(void *ptr, size_t size, size_t nmemb)
{
	return 0;
}
size_t CtoeWebRequest::WriteFunction(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	return ((CtoeWebRequest*)userdata)->OnWriteFunction(ptr,size,nmemb);
}
size_t CtoeWebRequest::HeaderFunction(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	return ((CtoeWebRequest*)userdata)->OnHeaderFunction(ptr,size,nmemb);
}

size_t CtoeWebRequest::ReadFunction(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	return ((CtoeWebRequest*)userdata)->OnReadFunction(ptr,size,nmemb);
}
void  CtoeWebRequest::AddHeaderValue(const char* buf,const char* v)
{
	AddHeader((std::string(buf)+":"+v).c_str());
}
void  CtoeWebRequest::AddHeader(const char* buf)
{
	m_headerlist = curl_slist_append(m_headerlist, buf);
}
void CtoeWebRequest::SetURL(const char * s)
{
	CurlAssert(curl_easy_setopt(m_curl, CURLOPT_URL, s));
}
int CtoeWebRequest::GetHTTPCode() const
{
	long retcode;
	curl_easy_getinfo (m_curl, CURLINFO_HTTP_CODE, &retcode);
	return (int)retcode;
}
void CtoeWebRequest::Start()
{
	curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);
	AttachTail(toeGetActiveWebRequests());
}
bool CtoeWebRequest::IsActive() const
{
	return listContainer != 0;
}
void CtoeWebRequest::Update()
{
	int still_running = 0;

	//CurlAssert(curl_easy_perform(m_curl));
	CurlAssert(curl_multi_perform(multi_handle, &still_running));

	if (!still_running)
		Detach();
}
void CtoeWebRequest::Wait()
{
	while (IsActive())
	{
		Update();
		toeDeviceYield(30);
		CtoeLoadingScreen::Render();
	}
}
void CtoeWebRequest::CurlAssert(int curlRes)
{
	if (CURLE_OK == curlRes)
		return;
	switch (curlRes)
	{
	case 0:
		IwAssertMsg(TOE, false, ("All fine. Proceed as usual."));
		break;
	case CURLE_UNSUPPORTED_PROTOCOL  :
		IwAssertMsg(TOE, false, ("The URL you passed to libcurl used a protocol that this libcurl does not support. The support might be a compile-time option that you didn't use, it can be a misspelled protocol string or just a protocol libcurl has no code for."));
		break;
	case CURLE_FAILED_INIT   :
		IwAssertMsg(TOE, false, ("Very early initialization code failed. This is likely to be an internal error or problem, or a resource problem where something fundamental couldn't get done at init time."));
		break;
	case CURLE_COULDNT_RESOLVE_HOST :
		IwAssertMsg(TOE, false, ("Couldn't resolve host. The given remote host was not resolved."));
		break;
	case CURLE_WRITE_ERROR :
		IwAssertMsg(TOE, false, ("An error occurred when writing received data to a local file, or an error was returned to libcurl from a write callback."));
		break;
		
	default:
		IwAssertMsg(TOE, false, ("cURL error %d",curlRes));
		break;
	}
}

const char* CtoeBufferedWebRequest::GetResponseString() const
{
	if (response.size() == 0)
		return "";
	return (const char*)&response[0];
}
CtoeBufferedWebRequest::CtoeBufferedWebRequest()
{
	responseSize = 0;
}
CtoeBufferedWebRequest::~CtoeBufferedWebRequest()
{
}
size_t CtoeBufferedWebRequest::OnWriteFunction(void *ptr, size_t size, size_t nmemb)
{
	size_t total = size*nmemb;
	response.resize(responseSize + total + 1);
	memcpy(&response[responseSize], ptr, total);
	responseSize += total;
	response[responseSize] = 0;
	return total;
}
size_t CtoeBufferedWebRequest::OnReadFunction(void *ptr, size_t size, size_t nmemb)
{
	return 0;
}
size_t CtoeBufferedWebRequest::OnHeaderFunction(void *ptr, size_t size, size_t nmemb)
{
	size_t total = size*nmemb;
	return total;
}
