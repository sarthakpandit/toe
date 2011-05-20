#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuImage.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuImage);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuImage);

//Constructor
CtoeSimpleMenuImage::CtoeSimpleMenuImage()
{
	InitImage();
}
//Constructor
CtoeSimpleMenuImage::CtoeSimpleMenuImage(uint32 t)
{
	InitImage();
	textureHash = t;
}
//Desctructor
CtoeSimpleMenuImage::~CtoeSimpleMenuImage()
{
	if (material)
		delete material;
}
void CtoeSimpleMenuImage::InitImage()
{
	textureHash = 0;
	texture = 0;
	material = 0;
	rectPos = CIwSVec2::g_Zero;
	rectUV = CIwSVec2::g_Zero;
	rectUVSize.x = IW_GEOM_ONE;
	rectUVSize.y = IW_GEOM_ONE;
	rectColour[0].Set(0xFFFFFFFF);
	rectColour[1].Set(0xFFFFFFFF);
	rectColour[2].Set(0xFFFFFFFF);
	rectColour[3].Set(0xFFFFFFFF);

	styleSheetHash = 0;
	styleSheet = 0;

}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuImage::Serialise ()
{
	CtoeSimpleMenuTerminalItem::Serialise();
	IwSerialiseUInt32(textureHash);
}
void CtoeSimpleMenuImage::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	if (textureHash == 0)
		return;
	CombineStyle(renderContext);
	if (!material)
	{
		texture = (CIwTexture*)IwGetResManager()->GetResHashed(textureHash, IW_GX_RESTYPE_TEXTURE);
		//CIwImage::Format f = texture->GetFormat();
		material = new CIwMaterial();
		material->SetTexture(texture);
	}
	rectSize = CIwSVec2::g_Zero;
	if (texture)
	{
		rectSize.x = texture->GetWidth();
		rectSize.y = texture->GetHeight();
		int16 contentWidth = width-(GetMarginLeft()+GetPaddingLeft()+GetMarginRight()+GetPaddingRight());
		if (rectSize.x > contentWidth)
		{
			rectSize.y = (int16)((int32)rectSize.y*(int32)width/(int32)rectSize.x);
			rectSize.x = contentWidth;
		}
		size.y = rectSize.y;
		size.x = contentWidth;
	}
	RearrangeChildItems();
}
void CtoeSimpleMenuImage::RearrangeChildItems()
{
	rectPos = GetOrigin();
	rectPos.y += GetMarginTop()+GetPaddingTop();
	int16 width = GetSize().x;
	rectPos.x += GetMarginLeft()+GetPaddingLeft();
	int16 contentWidth = width-(GetMarginLeft()+GetPaddingLeft()+GetMarginRight()+GetPaddingRight());
	rectPos.x += (contentWidth-rectSize.x)*combinedStyle.HorizontalAlignment/IW_GEOM_ONE;
}
//Render image on the screen surface
void CtoeSimpleMenuImage::Render(toeSimpleMenuItemContext* renderContext)
{
	if (textureHash == 0)
		return;

	IwGxSetMaterial(material);

	IwGxDrawRectScreenSpace (&rectPos,&rectSize,&rectUV,&rectUVSize,rectColour);
}
uint32 CtoeSimpleMenuImage::GetElementNameHash()
{
	static uint32 name = IwHashString("IMAGE");
	return name;
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuImage::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("texture",pAttrName))
	{
		pParser->ReadStringHash(&textureHash);
		return true;
	}
	if (!stricmp("styleSheet",pAttrName))
	{
		pParser->ReadStringHash(&styleSheetHash);
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
