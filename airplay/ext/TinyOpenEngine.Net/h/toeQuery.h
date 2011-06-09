#pragma once

#include "toeScriptingSubsystem.h"
#include "toeWebRequest.h"

namespace TinyOpenEngine
{
	class CtoeQueryRequest: public CtoeWebRequest
	{
	public:
		void Get(const char*);
		void Post(const char*);
	};
	class CtoeQuery
	{
		CtoeQueryRequest request;
		std::string url;
	public:
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();

		CtoeQuery();

		virtual ~CtoeQuery();

		void AddHeader(const char*,const char*);
		void SetArgument(const char*,const char*);
		void SetUrl(const char*);
		void Get();
		void Post();
		void Wait();
	protected:
		void BuildGetUrl(std::string & s);
		void BuildPostRequestBody();
	};
}
