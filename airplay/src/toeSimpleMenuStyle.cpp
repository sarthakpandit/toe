#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuStyle.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuStyleSettings);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
//IW_MANAGED_IMPLEMENT(CtoeSimpleMenuStyleSettings);


//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuStyleSettings::Serialise ()
{
	IwSerialiseUInt32(FontHash);
	if (IwSerialiseIsReading() && FontHash != 0)
		Font = (CtoeFreeTypeFont*)IwGetResManager()->GetResHashed(FontHash,"CtoeFreeTypeFont");
	FontSize.Serialise();
	FontColor.Serialise();
	Background.Serialise();
	Margin.Serialise();
	Padding.Serialise();
	IwSerialiseInt32(HorizontalAlignment);
	IwSerialiseInt32(VerticalAlignment);
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuStyle::Serialise ()
{
	CIwManaged::Serialise();
	settings.Serialise();
	IwSerialiseBool(isFont);
	IwSerialiseBool(isFontSize);
	IwSerialiseBool(isFontColor);
	IwSerialiseBool(isBackground);
	IwSerialiseBool(isMargin);
	IwSerialiseBool(isPadding);
	IwSerialiseBool(isHorizontalAlignment);
	IwSerialiseBool(isVerticalAlignment);
}

#ifdef IW_BUILD_RESOURCES
//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuStyle::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("background",pAttrName))
	{
		pParser->PushObject(&settings.Background);
		isBackground = true;
		return true;
	}
	if (!stricmp("font",pAttrName))
	{
		pParser->ReadStringHash(&settings.FontHash);
		isFont = true;
		return true;
	}
	if (!stricmp("fontSize",pAttrName))
	{
		settings.FontSize.ParseAttribute(pParser);
		isFontSize = true;
		return true;
	}
	if (!stricmp("fontColour",pAttrName) || !stricmp("fontColor",pAttrName))
	{
		uint8 c[4];
		pParser->ReadUInt8Array(c,4);
		settings.FontColor.Set(c[0],c[1],c[2],c[3]);
		isFontColor = true;
		return true;
	}
	if (!stricmp("HorizontalAlignment", pAttrName))
	{
		pParser->ReadFixed(&settings.HorizontalAlignment);
		isHorizontalAlignment = true;
		return true;
	}
	if (!stricmp("VerticalAlignment", pAttrName))
	{
		pParser->ReadFixed(&settings.VerticalAlignment);
		isVerticalAlignment = true;
		return true;
	}
	if (!stricmp("margin", pAttrName))
	{
		settings.Margin.left.ParseAttribute(pParser);
		settings.Margin.top = settings.Margin.right = settings.Margin.bottom = settings.Margin.left;
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-left", pAttrName))
	{
		settings.Margin.left.ParseAttribute(pParser);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-right", pAttrName))
	{
		settings.Margin.right.ParseAttribute(pParser);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-top", pAttrName))
	{
		settings.Margin.top.ParseAttribute(pParser);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-bottom", pAttrName))
	{
		settings.Margin.bottom.ParseAttribute(pParser);
		isMargin = true;
		return true;
	}
	if (!stricmp("padding", pAttrName))
	{
		settings.Padding.left.ParseAttribute(pParser);
		settings.Padding.top = settings.Padding.right = settings.Padding.bottom = settings.Padding.left;
		isPadding = true;
		return true;
	}
	if (!stricmp("padding-left", pAttrName))
	{
		settings.Padding.left.ParseAttribute(pParser);
		isPadding = true;
		return true;
	}
	if (!stricmp("padding-right", pAttrName))
	{
		settings.Padding.right.ParseAttribute(pParser);
		isPadding = true;
		return true;
	}
	if (!stricmp("padding-top", pAttrName))
	{
		settings.Padding.top.ParseAttribute(pParser);
		isPadding = true;
		return true;
	}
	if (!stricmp("padding-bottom", pAttrName))
	{
		settings.Padding.bottom.ParseAttribute(pParser);
		isMargin = true;
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}

#endif