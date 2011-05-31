#pragma once

#include <IwHTTP.h>
#include "toeScriptingSubsystem.h"

namespace TinyOpenEngine
{
	class CtoeHTTPRequest
	{
	protected:
		bool isActive;
		CIwHTTP transport;
		CIwArray<char> response;
		uint32 responseSize;
	public:
		CtoeHTTPRequest();
		virtual ~CtoeHTTPRequest();
		bool IsActive() const;
		const char* GetResponseString() const;
		void Cancel();

		CIwHTTP& GetTransport();

	protected:
		virtual void OnError();
		virtual void OnResponseComplete();
		virtual void OnHeadersComplete();
		virtual void OnChunkComplete();
		void RawDownloadResponse();
		static int RawChunkComplete(void*sys,void*http);
		static int RawHeadersComplete(void*sys,void*http);
		void RawGet(const char* gUrl);
	};
}
