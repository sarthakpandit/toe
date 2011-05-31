#include <IwResManager.h>
#include <math.h>
#include "toeOSM.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeOSM::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeOSM> d ("CtoeOSM",
//			ScriptTraits::Method("DownloadString", &CtoeOSM::DownloadString),
			0);
	return &d;
}

int CtoeOSM::GetLongitude(float lon, int zoom)
{
	float z = (float)(1 << zoom);
	return (int)(( (float)((lon + 180.0f) / 360.0f * z) )) ;
}
int CtoeOSM::GetLatitude(float lat, int zoom)
{
	double z = (float)(1 << zoom);
	return (int)( (float)((1.0f - logf(tanf(lat * (float)M_PI / 180.0f) + 1.0f / cosf(lat * (float)M_PI / 180.0f)) / (float)M_PI) / 2.0f * z) );
}
