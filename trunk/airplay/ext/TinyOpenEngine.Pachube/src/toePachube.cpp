#include <IwResManager.h>
#include <sstream>
#include "toePachube.h"
#include "toeQuery.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}


//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoePachube::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoePachube> d ("CtoePachube",
			ScriptTraits::Method("ReadFeed", &CtoePachube::ReadFeed),
			0);
	return &d;
}

void CtoePachube::ReadFeed(int feedid, const char* apiKey)
{
	CtoeQuery q;
	q.AddHeader("X-PachubeApiKey", apiKey);
	std::stringstream out;
	out << "http://api.pachube.com/v2/feeds/";
	out << feedid;
	out << ".xml";
	q.SetUrl(out.str().c_str());
	q.Get();
	q.Wait();
}