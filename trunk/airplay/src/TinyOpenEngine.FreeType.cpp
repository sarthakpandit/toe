#include "TinyOpenEngine.FreeType.h"
#include "toeFreeTypeFont.h"


using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineFreeTypeInitialized = false;
	FT_Error  error;
    FT_Library  library=0;      /* the FreeType library */

	FT_Library toeGetFreeTypeLibrary()
	{
		return library;
	}

	int32 toeGetScreenDPI_iOS()
	{
		//const char* deviceID = s3eDeviceGetString(S3E_DEVICE_ID);
		return 163;
		//return 326; //Retina display
		//return 132; //iPad
		//return 163; //old ipod/iphone;
	}
}


void TinyOpenEngine::toeFreeTypeInit()
{
	if (isTinyOpenEngineFreeTypeInitialized)
		return;
	isTinyOpenEngineFreeTypeInitialized = true;

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeFreeTypeFontResHandler("ttf","toeFreeTypeTTF"));
	#endif

	IW_CLASS_REGISTER(CtoeFreeTypeFont);

	error = FT_Init_FreeType( &library );
	IwAssertMsg(FT, !error, ("Could not initialize FreeType library") );


}

void TinyOpenEngine::toeFreeTypeTerminate()
{
	if (!isTinyOpenEngineFreeTypeInitialized)
		return;
	isTinyOpenEngineFreeTypeInitialized = false;

	FT_Done_FreeType( library );
}

int32 TinyOpenEngine::toeGetScreenDPI()
{
	int32 os = s3eDeviceGetInt(S3E_DEVICE_OS);
	switch (os)
	{
	case S3E_OS_ID_IPHONE:
		return toeGetScreenDPI_iOS();
	default:
		break;
	}
	return 120;
}