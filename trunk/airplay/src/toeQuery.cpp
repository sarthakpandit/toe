#include <IwResManager.h>
#include <IwHTTP.h>
#include "toeNet.h"
#include "toeLoadingScreen.h"
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
	request.AddHeader(name,val);
}
void CtoeQuery::SetUrl(const char* s)
{
	url = s;
}
void CtoeQueryRequest::Get(const char* u)
{
	RawGet(u);
}
void CtoeQueryRequest::Post(const char* u)
{
	RawPost(u);
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
	while (request.IsActive())
	{
		CtoeLoadingScreen::Render();
		s3eDeviceYield(30);
	}
}
void CtoeQuery::BuildGetUrl(std::string & s)
{
}
void CtoeQuery::BuildPostRequestBody()
{
}