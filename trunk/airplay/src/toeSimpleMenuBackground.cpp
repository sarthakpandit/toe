#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuBackground.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuBackground);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuBackground);

//Constructor
CtoeSimpleMenuBackground::CtoeSimpleMenuBackground()
{
	colour.Set(0x000000FF);
}
//Desctructor
CtoeSimpleMenuBackground::~CtoeSimpleMenuBackground()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuBackground::Serialise ()
{
	CtoeSimpleMenuTerminalItem::Serialise();
	colour.Serialise();
	
}
void CtoeSimpleMenuBackground::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuTerminalItem::Prepare(renderContext,width);
}
//Render image on the screen surface
void CtoeSimpleMenuBackground::Render(toeSimpleMenuItemContext* renderContext)
{
	CIwSVec2* vec = IW_GX_ALLOC(CIwSVec2, 4);
	CIwSVec2 s = GetSize();
	vec[0] = GetOrigin()+CIwSVec2(GetMarginLeft(),GetMarginTop());
	vec[1] = GetOrigin()+CIwSVec2(GetMarginLeft(),s.y-GetMarginTop()-GetMarginBottom());
	vec[2] = GetOrigin()+CIwSVec2(s.x-GetMarginLeft()-GetMarginRight(),s.y-GetMarginTop()-GetMarginBottom());
	vec[3] = GetOrigin()+CIwSVec2(s.x-GetMarginLeft()-GetMarginRight(),GetMarginTop());
	IwGxSetVertStreamScreenSpace(vec,4);
	IwGxSetColStream(0);
	CIwMaterial * m = IW_GX_ALLOC_MATERIAL();
	m->SetColEmissive(255,255,255,255);
	m->SetColDiffuse(255,255,255,255);
	m->SetColAmbient(colour.r,colour.g,colour.b,colour.a);
	if (colour != 255)
		m->SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	IwGxSetMaterial(m);
	IwGxDrawPrims(IW_GX_QUAD_LIST,0,4);
	CtoeSimpleMenuTerminalItem::Render(renderContext);
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuBackground::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("colour",pAttrName))
	{
		uint8 c[4];
		pParser->ReadUInt8Array(c,4);
		colour.Set(c[0],c[1],c[2],c[3]);
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
