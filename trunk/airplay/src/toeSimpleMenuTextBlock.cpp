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
	textAlignment = 0;
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
	IwSerialiseInt32(textAlignment);
	style.Serialise();
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
	CombineStyle(renderContext);
	CtoeFreeTypeFont* f = combinedStyle.Font;
	if (!f)
		return;
	int16 contentWidth = width - GetMarginLeft() - GetMarginRight() - GetPaddingLeft() - GetPaddingRight();
	CIwArray<CtoeFreeTypeGlyphLayout> layout;
	layoutData.origin = CIwSVec2::g_Zero;
	layoutData.size.x = contentWidth;
	layoutData.size.y = combinedStyle.FontSize.GetPx(width);
	layoutData.textAlignment = textAlignment;//IW_GEOM_ONE/3;
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
	combinedStyle.Background.Render(GetOrigin()+CIwSVec2(GetMarginLeft(),GetMarginTop()), GetSize()-CIwSVec2(GetMarginLeft()+GetMarginRight(),GetMarginTop()+GetMarginBottom()));
	CIwSVec2 p = GetOrigin()+CIwSVec2(GetMarginLeft()+GetPaddingLeft(),GetMarginTop()+GetPaddingTop());
	layoutData.RenderAt(p,combinedStyle.FontColor);
	
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
	if (!stricmp("textAlignment",pAttrName))
	{
		pParser->ReadFixed(&textAlignment);
		return true;
	}
	return CtoeSimpleMenuTerminalItem::ParseAttribute(pParser, pAttrName);
}

#endif
