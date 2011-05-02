#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuTextBlock.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuTextBlock);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuTextBlock);

//Constructor
CtoeSimpleMenuTextBlock::CtoeSimpleMenuTextBlock()
{
	utf8string = 0;
	glyphColor[0].Set(0xFFFFFFFF);
	glyphColor[1].Set(0xFFFFFFFF);
	glyphColor[2].Set(0xFFFFFFFF);
	glyphColor[3].Set(0xFFFFFFFF);
}
//Desctructor
CtoeSimpleMenuTextBlock::~CtoeSimpleMenuTextBlock()
{
	if (utf8string)
	{
		delete [] utf8string;
		utf8string= 0;
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuTextBlock::Serialise ()
{
	CtoeSimpleMenuTerminalItem::Serialise();
	size_t len = 0;
	if (IwSerialiseIsReading())
	{
		IwSerialiseUInt32(len);
		if (len)
		{
			utf8string = new char[len+1];
			IwSerialiseString(utf8string);
		}
	}
	else
	{
		if (utf8string)
		{
			len = strlen(utf8string);
			IwSerialiseUInt32(len);
			IwSerialiseString(utf8string);
		}
		else
		{
			IwSerialiseUInt32(len);
		}
	}
}
void CtoeSimpleMenuTextBlock::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	int16 contentWidth = width - GetMarginLeft() - GetMarginRight() - GetPaddingLeft() - GetPaddingRight();
	CtoeFreeTypeFont* f = renderContext->font;
	CIwArray<CtoeFreeTypeGlyphLayout> layout;
	layoutData.origin = CIwSVec2::g_Zero;
	layoutData.size.x = contentWidth;
	layoutData.size.y = renderContext->fontSize;
	layoutData.textAlignment = 0;//IW_GEOM_ONE/3;
	layoutData.isRightToLeft = false;//CtoeFreeTypeFont::IsRightToLeft();
	if (utf8string)
	{
		f->LayoutGlyphs(utf8string, layoutData);
	}

	size.x = width;
	size.y = layoutData.actualSize.y + GetMarginTop()+GetMarginBottom()+GetPaddingTop()+GetPaddingBottom();
}
//Render image on the screen surface
void CtoeSimpleMenuTextBlock::Render(toeSimpleMenuItemContext* renderContext)
{
	if (totalGlyphs == 0)
		return;

	CIwSVec2 p = GetOrigin()+CIwSVec2(GetMarginLeft()+GetPaddingLeft(),GetMarginTop()+GetPaddingTop());
	layoutData.RenderAt(p);
	
}
#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuTextBlock::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("text",pAttrName))
	{
		utf8string = pParser->ReadString();
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
