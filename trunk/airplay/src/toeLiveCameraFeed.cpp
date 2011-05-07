#include <IwGx.h>
#include <s3eCamera.h>
#include <IwGxDebug.h>
#include <IwTextParserITX.h>
#include "toeLiveCameraFeed.h"
#include "toeEntity.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeLiveCameraFeed);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeLiveCameraFeed);

namespace TinyOpenEngine
{
	
	


}

//Constructor
CtoeLiveCameraFeed::CtoeLiveCameraFeed()
{
	//IwDebugTraceLinePrintf("CtoeBox2DCircle(0x%08X)",this);
	//m_FrameData = 0;
	//m_FrameWidth = 0;
	//m_FrameHeight = 0;
	//m_FramePitch = 0;
	image = 0;
	texture = 0;
	activeBuffer= 0;
	completeBuffer = 0;
	feedUpdated = false;
	started = false;
}

//Desctructor
CtoeLiveCameraFeed::~CtoeLiveCameraFeed()
{
	//IwDebugTraceLinePrintf("~CtoeBox2DCircle(0x%08X)",this);
	//if (m_FrameData)
	//	s3eFree(m_FrameData);
	if (image)
		delete image;
	if (activeBuffer) delete []activeBuffer;
	if (completeBuffer) delete []completeBuffer;
	if (texture)
		delete texture;
}

void CtoeLiveCameraFeed::BeforeDestruction(CtoeEntity* e)
{
	if (started)
	{
		s3eCameraStop();
		s3eCameraUnRegister(S3E_CAMERA_UPDATE_STREAMING, CameraUpdate);
		started = false;
	}
	CtoeSelfRenderedComponent::BeforeDestruction(e);
}

void CtoeLiveCameraFeed::BeforeInitialization(CtoeEntity* e)
{
	CtoeSelfRenderedComponent::BeforeInitialization(e);
	if (!started)
	{
		if (s3eCameraAvailable())
		{
			if (S3E_RESULT_ERROR == s3eCameraRegister(S3E_CAMERA_UPDATE_STREAMING, CameraUpdate, this))
	        {
				return;
			}

			if (s3eCameraStart(S3E_CAMERA_STREAMING_SIZE_HINT_SMALLEST, S3E_CAMERA_PIXEL_TYPE_RGB565_CONVERTED) == S3E_RESULT_SUCCESS)
			{
				started = true;
			}
		}
	}
}
// Callback that gets filled with camera buffer data
int32 CtoeLiveCameraFeed::CameraUpdate(void* systemData, void* userData)
{
	CtoeLiveCameraFeed* g_currentFeed = (CtoeLiveCameraFeed*)userData;
	if (!g_currentFeed)
		return 0;
	if (g_currentFeed->feedUpdated)
		return 0;
	// Frame data is no longer valid once s3eCameraStop is called

	s3eCameraFrameData* m_Frame = (s3eCameraFrameData*)systemData;

	if (!g_currentFeed->image)
	{
		int w = 1; while (w < m_Frame->m_Width) w = w<<1;
		int h = 1; while (h < m_Frame->m_Height) h = h<<1;
		CIwImage* image;
		image = new CIwImage();
		g_currentFeed->image = image;
		image->SetFormat(CIwImage::RGB_565);
		image->SetWidth(w);
		image->SetHeight(h);
		image->SetBuffers();
		g_currentFeed->completeBuffer = new int16[image->GetPitch()/2*image->GetHeight()];
		g_currentFeed->activeBuffer = new int16[image->GetPitch()/2*image->GetHeight()];
		g_currentFeed->texture = new CIwTexture();
		g_currentFeed->texture->SetModifiable(true);
		//g_currentFeed->texture->SetMipMapping(false);
		g_currentFeed->texture->SetImage(g_currentFeed->image);
	}

	// Copying frame data since it is not guaranteed to persist and will be
	// overwritten with next buffer. Using the data directly will increase
	// tearing but improve responsiveness. Note that s3eCamera beta does not
	// lock the frame buffer so cannot guarantee no tearing. This will be
	// addressed in the final version.
	/*if (!g_currentFeed->m_FrameData ||
			m_Frame->m_Width != g_currentFeed->m_FrameWidth ||
			m_Frame->m_Height != g_currentFeed->m_FrameHeight)
	{
		g_currentFeed->m_FrameWidth = m_Frame->m_Width;
		g_currentFeed->m_FrameHeight = m_Frame->m_Height;
		g_currentFeed->m_FramePitch = m_Frame->m_Pitch;

		g_currentFeed->m_FrameData = (uint16*)
			s3eRealloc(g_currentFeed->m_FrameData, g_currentFeed->m_FrameHeight * m_Frame->m_Pitch);
	}

	if (g_currentFeed->m_FrameData)
		memcpy(g_currentFeed->m_FrameData, m_Frame->m_Data, m_Frame->m_Pitch * m_Frame->m_Height);*/

	int16*texels;

	texels = g_currentFeed->completeBuffer; g_currentFeed->completeBuffer=g_currentFeed->activeBuffer; g_currentFeed->activeBuffer = texels;

	for (int yy=0; yy<m_Frame->m_Height && yy<(int)g_currentFeed->image->GetHeight();++yy)
		for (int xx=0; xx<m_Frame->m_Width && xx<(int)g_currentFeed->image->GetWidth();++xx)
			*(int16*)(texels+g_currentFeed->image->GetPitch()/2*yy+xx) = *(int16*)((uint8*)m_Frame->m_Data+xx*2+yy*m_Frame->m_Pitch);
	g_currentFeed->feedWidth = m_Frame->m_Width;
	g_currentFeed->feedHeight = m_Frame->m_Height;
	//g_currentFeed->texture->ChangeTexels(texels, CIwImage::RGB_565);
	g_currentFeed->feedUpdated = true;

	return 0;
}
void CtoeLiveCameraFeed::Render()
{
	// Display status info
    //int32 camStatus;
    //const int textHeight = s3eDebugGetInt(S3E_DEBUG_FONT_SIZE_HEIGHT);

  
    // Copy frame data to screen
//    if (m_FrameData)
//    {
//        uint8* screen = (uint8*)s3eSurfacePtr();
//        uint8* buffer = (uint8*)m_FrameData;
//
//#define min(a,b) a < b ? a : b
//
//        const int screen_height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
//        const int screen_pitch  = s3eSurfaceGetInt(S3E_SURFACE_PITCH);
//
//        const int height = min(m_FrameHeight, screen_height);
//        const int pitch  = min(m_FramePitch,  screen_pitch);
//
//		//IwGxFlush();
//
//        for (int y = 0; y < height-1; y++)
//        {
//            memcpy(&screen[y * screen_pitch], 
//                   &buffer[y * m_FramePitch], pitch);
//        }
//    }

	if (texture)
	{
		if (feedUpdated)
		{
			texture->ChangeTexels((uint8*)completeBuffer, CIwImage::RGB_565);
			texture->Upload();
			feedUpdated = false;
		}

		CIwMaterial* m = IW_GX_ALLOC_MATERIAL();
		m->SetTexture(texture);
		m->SetColAmbient(255,255,255,255);
		IwGxSetMaterial(m);
		static CIwSVec2 pos = CIwSVec2::g_Zero;
		int32 w = (int32)IwGxGetScreenWidth();
		int32 h = (int32)IwGxGetScreenHeight();
		static CIwSVec2 dx = CIwSVec2(w,h);
		static CIwSVec2 uv = CIwSVec2::g_Zero;
		static CIwSVec2 uvSize;
		uvSize = CIwSVec2((int16)(feedWidth*IW_GEOM_ONE/texture->GetWidth()), (int16)(feedHeight*IW_GEOM_ONE/texture->GetHeight()));
		IwGxDrawRectScreenSpace(&pos, &dx,&uv,&uvSize);
	}

}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeLiveCameraFeed::Serialise ()
{
	CtoeSelfRenderedComponent::Serialise();
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeLiveCameraFeed::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	
	return CtoeSelfRenderedComponent::ParseAttribute(pParser,pAttrName);
}
#endif