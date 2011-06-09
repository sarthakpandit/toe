#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
#include <TinyOpenEngine.h>
#include "toeUtils.h"
#include "toeQuery.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{

}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeQuery::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeQuery> d ("CtoeQuery",
			ScriptTraits::Method("DownloadString", &CtoeQuery::AddHeader),
			0);
	return &d;
}

CtoeQuery::CtoeQuery()
{
}

CtoeQuery::~CtoeQuery()
{
}
void CtoeQuery::AddHeader(const char* name,const char* val)
{
	request.AddHeaderValue(name,val);
}
void CtoeQuery::SetUrl(const char* s)
{
	url = s;
}
void CtoeQueryRequest::Get(const char* u)
{
	SetURL(u);
	Start();
}
void CtoeQueryRequest::Post(const char* u)
{
	SetURL(u);
	Start();
}

void CtoeQuery::Get()
{
	std::string u = url;
	BuildGetUrl(u);
	request.Get(u.c_str());
}
void CtoeQuery::Post()
{
	BuildPostRequestBody();
	request.Post(url.c_str());
}
void CtoeQuery::Wait()
{
	request.Wait();
}
void CtoeQuery::BuildGetUrl(std::string & s)
{
}
void CtoeQuery::BuildPostRequestBody()
{
}