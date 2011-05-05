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
	if (!stricmp("margin", pAttrName))
	{
		pParser->ReadInt16(&settings.Margin.x);
		settings.Margin.y = settings.Margin.z = settings.Margin.w = settings.Margin.x;
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-left", pAttrName))
	{
		pParser->ReadInt16(&settings.Margin.x);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-right", pAttrName))
	{
		pParser->ReadInt16(&settings.Margin.z);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-top", pAttrName))
	{
		pParser->ReadInt16(&settings.Margin.y);
		isMargin = true;
		return true;
	}
	if (!stricmp("margin-bottom", pAttrName))
	{
		pParser->ReadInt16(&settings.Margin.w);
		isMargin = true;
		return true;
	}
	if (!stricmp("padding", pAttrName))
	{
		pParser->ReadInt16(&settings.Padding.x);
		settings.Padding.y = settings.Padding.z = settings.Padding.w = settings.Padding.x;
		isMargin = true;
		return true;
	}
	if (!stricmp("padding-left", pAttrName))
	{
		pParser->ReadInt16(&settings.Padding.x);
		isMargin = true;
		return true;
	}
	if (!stricmp("padding-right", pAttrName))
	{
		pParser->ReadInt16(&settings.Padding.z);
		isMargin = true;
		return true;
	}
	if (!stricmp("padding-top", pAttrName))
	{
		pParser->ReadInt16(&settings.Padding.y);
		isMargin = true;
		return true;
	}
	if (!stricmp("padding-bottom", pAttrName))
	{
		pParser->ReadInt16(&settings.Padding.w);
		isMargin = true;
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}

#endif