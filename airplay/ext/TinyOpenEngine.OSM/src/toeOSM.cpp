#include <IwResManager.h>
#include <math.h>
#include "toeOSM.h"
#include "toeFeatures.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeOSM::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeOSM> d ("CtoeOSM",
			ScriptTraits::Method("ConvertLongitude", &CtoeOSM::ConvertLongitude),
			ScriptTraits::Method("ConvertLatitude", &CtoeOSM::ConvertLatitude),
			ScriptTraits::Method("GetLongitudeAt", &CtoeOSM::GetLongitudeAt),
			ScriptTraits::Method("GetLatitudeAt", &CtoeOSM::GetLatitudeAt),
			ScriptTraits::Method("GetLongitude", &CtoeOSM::GetLongitude),
			ScriptTraits::Method("GetLatitude", &CtoeOSM::GetLatitude),
			0);
	return &d;
}

int CtoeOSM::ConvertLongitude(float lon, int zoom)
{
	float z = (float)(1 << zoom);
	return (int)(( (float)((lon + 180.0f) / 360.0f * z) )) ;
}
int CtoeOSM::ConvertLatitude(float lat, int zoom)
{
	double z = (float)(1 << zoom);
	return (int)( (float)((1.0f - logf(tanf(lat * (float)M_PI / 180.0f) + 1.0f / cosf(lat * (float)M_PI / 180.0f)) / (float)M_PI) / 2.0f * z) );
}
int CtoeOSM::GetLongitudeAt(int zoom)
{
	return ConvertLongitude(CtoeLocation::GetLongitude(),zoom);
}
int CtoeOSM::GetLatitudeAt(int zoom)
{
	return ConvertLongitude(CtoeLocation::GetLatitude(),zoom);
}
int CtoeOSM::GetLongitude()
{
	return ConvertLongitude(CtoeLocation::GetLongitude(),18+8);
}
int CtoeOSM::GetLatitude()
{
	return ConvertLongitude(CtoeLocation::GetLatitude(),18+8);
}
