#include "math.h"
#include "toeFeatures.h"
#include "s3eLocation.h"
#include "toeConfig.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	CtoeLocation* g_toeLocation = 0;
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeLocation::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeLocation> d ("CtoeLocation",
		ScriptTraits::Method("IsAvailable", &CtoeLocation::IsAvailable),
		ScriptTraits::Method("GetLatitude", &CtoeLocation::GetLatitude),
		ScriptTraits::Method("GetLongitude", &CtoeLocation::GetLongitude),
		ScriptTraits::Method("GetAltitude", &CtoeLocation::GetAltitude),
		ScriptTraits::Method("GetHorizontalAccuracy", &CtoeLocation::GetHorizontalAccuracy),
		ScriptTraits::Method("GetVerticalAccuracy", &CtoeLocation::GetVerticalAccuracy),
		ScriptTraits::Method("EvalDistance", &CtoeLocation::EvalDistance),
		ScriptTraits::Method("EvalDistance", &CtoeLocation::EvalDistance),
			0);
	return &d;
}
bool CtoeLocation::IsAvailable()
{
	return s3eLocationAvailable() != 0;
}
CtoeLocation::CtoeLocation()
{
	m_timestamp = 0;
}
CtoeLocation::~CtoeLocation()
{
	g_toeLocation = 0;
}
CtoeLocation* CtoeLocation::RequestFeature()
{
	if (g_toeLocation)
		return g_toeLocation;
	if (!IsAvailable())
		return 0;
	g_toeLocation = new CtoeLocation();
	g_toeLocation->Start();
	return g_toeLocation;
}
void CtoeLocation::SaveToConfig()
{
		CtoeConfig::SetFloat("toe-location-latitude", (float)l.m_Latitude);
		CtoeConfig::SetFloat("toe-location-longitude", (float)l.m_Longitude);
		CtoeConfig::SetFloat("toe-location-altitude", (float)l.m_Altitude);
		CtoeConfig::SetFloat("toe-location-vertical-accuracy", (float)l.m_VerticalAccuracy);
		CtoeConfig::SetFloat("toe-location-horizontal-accuracy", (float)l.m_HorizontalAccuracy);
		CtoeConfig::SetInteger("toe-location-timestamp",m_timestamp);
}
void CtoeLocation::LoadFromConfig()
{
		l.m_Latitude = CtoeConfig::GetFloat("toe-location-latitude");
		l.m_Longitude = CtoeConfig::GetFloat("toe-location-longitude");
		l.m_Altitude = CtoeConfig::GetFloat("toe-location-altitude");
		l.m_VerticalAccuracy = CtoeConfig::GetFloat("toe-location-vertical-accuracy");
		l.m_HorizontalAccuracy = CtoeConfig::GetFloat("toe-location-horizontal-accuracy");
		m_timestamp = CtoeConfig::GetInteger("toe-location-timestamp");
		
}
void CtoeLocation::StartFeature()
{
	m_timestamp = 0;
	s3eLocationStart();
	if (CtoeConfig::IsExist("toe-location-latitude"))
	{
		g_toeLocation->LoadFromConfig();
	}
	else
	{
		s3eLocationGet(&l);
		SaveToConfig();
	}
	s3eLocationRegister(S3E_LOCATION_CALLBACK_LOCATION_UPDATED, Callback, this);
}
int32 CtoeLocation::Callback (void* systemData, void* userData)
{
	if (g_toeLocation)
	{
		g_toeLocation->l = *((s3eLocation*)systemData);
		g_toeLocation->m_timestamp = time(0);
		g_toeLocation->SaveToConfig();
	}
	return 0;
}
void CtoeLocation::StopFeature()
{
	s3eLocationStop();
	s3eLocationUnRegister(S3E_LOCATION_CALLBACK_LOCATION_UPDATED, Callback);
}
int CtoeLocation::GetTimeStamp()
{
	if (RequestFeature())
		return (int)g_toeLocation->m_timestamp;
	return 0;
}
float CtoeLocation::GetLatitude()
{
	if (RequestFeature())
		return (float)g_toeLocation->l.m_Latitude;
	return 0;
}
float CtoeLocation::GetLongitude()
{
	if (RequestFeature())
		return (float)g_toeLocation->l.m_Latitude;
	return 0;
}
float CtoeLocation::EvalDistance(float lon1, float lat1, float lon2, float lat2)
{
	float llon1 = lon1*0.01745329251994329576923690768489f;
	float llat1 = lat1*0.01745329251994329576923690768489f;
	float llon2 = lon2*0.01745329251994329576923690768489f;
	float llat2 = lat2*0.01745329251994329576923690768489f;

	float R = 6371; // km
	float dLat = (llat2-llat1);
	float dLon = (llon2-llon1); 
	float a = sinf(dLat/2) * sinf(dLat/2) +
			cosf(llat1) * cosf(llat2) * 
			sinf(dLon/2) * sinf(dLon/2); 
	float c = 2 * atan2f(sqrtf(a), sqrtf(1-a)); 
	float d = R * c;
	return d;
}
float CtoeLocation::GetAltitude()
{
	if (RequestFeature())
		return (float)g_toeLocation->l.m_Altitude;
	return 0;
}
float CtoeLocation::GetHorizontalAccuracy()
{
	if (RequestFeature())
		return (float)g_toeLocation->l.m_HorizontalAccuracy;
	return -1;
}
float CtoeLocation::GetVerticalAccuracy()
{
	if (RequestFeature())
		return (float)g_toeLocation->l.m_VerticalAccuracy;
	return -1;
}
