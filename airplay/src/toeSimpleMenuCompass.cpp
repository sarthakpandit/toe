#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "toeSimpleMenuCompass.h"
#include "toeSimpleMenuRoot.h"
#include "toeFeatures.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuCompass);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuCompass);

//Constructor
CtoeSimpleMenuCompass::CtoeSimpleMenuCompass()
{

}
//Desctructor
CtoeSimpleMenuCompass::~CtoeSimpleMenuCompass()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuCompass::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
uint32 CtoeSimpleMenuCompass::GetElementNameHash()
{
	static uint32 name = IwHashString("Compass");
	return name;
}
//Render image on the screen surface
void CtoeSimpleMenuCompass::Render(toeSimpleMenuItemContext* renderContext)
{
	CIwMat m = renderContext->transformation;
	CIwVec3 forward(0,1000,0);
	if (CtoeCompass::IsAvailable())
	{
		forward.x = CtoeCompass::GetX();
		forward.y = CtoeCompass::GetY();
		forward.z = CtoeCompass::GetZ();
	}
	CIwVec3 down(0,0,1000);
	if (CtoeAccelerometer::IsAvailable())
	{
		down.x = CtoeAccelerometer::GetX();
		down.y = CtoeAccelerometer::GetY();
		down.z = CtoeAccelerometer::GetZ();
	}
	CIwVec3 r = forward.Cross(down);
	if (r != CIwVec3::g_Zero)
	{
		CIwVec3 f = down.Cross(r);
		down.Normalise();
		r.Normalise();
		f.Normalise();
		CIwVec3 center(GetOrigin().x+GetSize().x/2,GetOrigin().y+GetSize().y/2,0);
		CIwMat t1; t1.SetIdentity(); t1.SetTrans(-center);
		CIwMat rot; rot.SetIdentity(); 
		
		//rot.SetRotZ(CtoeCompass::GetHeading()*IW_GEOM_ONE/360);
		down = -down;
		r = -r;
		rot.m[0][0] = r.x; rot.m[1][0] = r.y; rot.m[2][0] = r.z;
		rot.m[0][1] = f.x; rot.m[1][1] = f.y; rot.m[2][1] = f.z;
		rot.m[0][2] = down.x; rot.m[1][2] = down.y; rot.m[2][2] = down.z;
		//rot.Transpose();

		CIwMat t2; t2.SetIdentity(); t2.SetTrans(center);
		renderContext->transformation = t1*rot*t2*m;
	}
	CtoeSimpleMenuItem::Render(renderContext);
	renderContext->transformation = m;
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuCompass::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
