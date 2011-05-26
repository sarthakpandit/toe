#include "toeFeatures.h"
#include "s3eAccelerometer.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	CtoeAccelerometer* g_toeAccelerometer = 0;
}

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeAccelerometer::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeAccelerometer> d ("CtoeAccelerometer",
		ScriptTraits::Method("IsAvailable", &CtoeAccelerometer::IsAvailable),
		ScriptTraits::Method("GetX", &CtoeAccelerometer::GetX),
		ScriptTraits::Method("GetY", &CtoeAccelerometer::GetY),
		ScriptTraits::Method("GetZ", &CtoeAccelerometer::GetZ),
			0);
	return &d;
}

bool CtoeAccelerometer::IsAvailable()
{
	return s3eAccelerometerGetInt( S3E_ACCELEROMETER_AVAILABLE ) != 0;
}
CtoeAccelerometer::~CtoeAccelerometer()
{
	g_toeAccelerometer = 0;
}
CtoeAccelerometer* CtoeAccelerometer::RequestFeature()
{
	if (g_toeAccelerometer)
		return g_toeAccelerometer;
	g_toeAccelerometer = new CtoeAccelerometer();
	g_toeAccelerometer->Start();
	return g_toeAccelerometer;
}
void CtoeAccelerometer::StartFeature()
{
	s3eAccelerometerStart();
}
void CtoeAccelerometer::StopFeature()
{
	s3eAccelerometerStop();
}
int CtoeAccelerometer::GetX()
{
	RequestFeature();
	return s3eAccelerometerGetX();
}
int CtoeAccelerometer::GetY()
{
	RequestFeature();
	return s3eAccelerometerGetY();
}
int CtoeAccelerometer::GetZ()
{
	RequestFeature();
	return s3eAccelerometerGetZ();
}
