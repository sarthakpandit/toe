#pragma once

#include <toeIntrusiveList.h>
extern "C"
{
#include <curl/curl.h>
}

namespace TinyOpenEngine
{
	class CtoeWebRequest: public TtoeIntrusiveListItem<CtoeWebRequest>
	{
	protected:
		CURL * m_curl;
		CURLM *multi_handle;
		curl_slist *m_headerlist;
	public:
		CtoeWebRequest();
		virtual ~CtoeWebRequest();

		void SetURL(const char *);
		virtual void Start();
		virtual bool IsActive() const;
		int GetHTTPCode() const;

		virtual void Update();
		virtual void Wait();
		void AddHeader(const char*);
		void AddHeaderValue(const char*,const char*);
	protected:
		// This function gets called by libcurl as soon as there is data received that needs to be saved. 
		// The size of the data pointed to by ptr is size multiplied with nmemb, it will not be zero terminated. 
		// Return the number of bytes actually taken care of. If that amount differs from the amount passed to your function, it'll signal an error to the library.
		virtual size_t OnWriteFunction(void *ptr, size_t size, size_t nmemb);

		// This function gets called by libcurl as soon as it needs to read data in order to send it to the peer. 
		// The data area pointed at by the pointer ptr may be filled with at most size multiplied with nmemb number of bytes. 
		// Your function must return the actual number of bytes that you stored in that memory area. 
		// Returning 0 will signal end-of-file to the library and cause it to stop the current transfer.
		virtual size_t OnReadFunction(void *ptr, size_t size, size_t nmemb);

		//  This function gets called by libcurl as soon as it has received header data. 
		// The header callback will be called once for each header and only complete header lines are passed on to the callback. 
		// Parsing headers should be easy enough using this. The size of the data pointed to by ptr is size multiplied with nmemb. 
		// Do not assume that the header line is zero terminated! The pointer named userdata is the one you set with the CURLOPT_WRITEHEADER option. 
		// The callback function must return the number of bytes actually taken care of. 
		// If that amount differs from the amount passed to your function, it'll signal an error to the library. 
		// This will abort the transfer and return CURL_WRITE_ERROR.
		virtual size_t OnHeaderFunction(void *ptr, size_t size, size_t nmemb);

		static size_t WriteFunction(void *ptr, size_t size, size_t nmemb, void *userdata);
		static size_t ReadFunction(void *ptr, size_t size, size_t nmemb, void *userdata);
		static size_t HeaderFunction(void *ptr, size_t size, size_t nmemb, void *userdata);

		void CurlAssert(int);
	};

	class CtoeBufferedWebRequest: public CtoeWebRequest
	{
		int responseSize;
		CIwArray<char> request;
		CIwArray<char> response;
	public:
		CtoeBufferedWebRequest();
		~CtoeBufferedWebRequest();
		const char* GetResponseString() const;
	protected:
		virtual size_t OnWriteFunction(void *ptr, size_t size, size_t nmemb);

		virtual size_t OnReadFunction(void *ptr, size_t size, size_t nmemb);

		virtual size_t OnHeaderFunction(void *ptr, size_t size, size_t nmemb);
	};

	TtoeIntrusiveList<CtoeWebRequest>* toeGetActiveWebRequests();
}
