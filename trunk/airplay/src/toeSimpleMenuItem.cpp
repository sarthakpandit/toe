#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuItem.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuItem);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuItem);

//Constructor
CtoeSimpleMenuItem::CtoeSimpleMenuItem()
{
	origin = CIwSVec2::g_Zero;
	size = CIwSVec2::g_Zero;
	margin= CIwSVec4::g_Zero;
	padding= CIwSVec4::g_Zero;
}
//Desctructor
CtoeSimpleMenuItem::~CtoeSimpleMenuItem()
{
	childItems.Delete();
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuItem::Serialise ()
{
	CIwManaged::Serialise();
	childItems.Serialise();
	origin.Serialise();
	size.Serialise();
	margin.Serialise();
	padding.Serialise();
}

void CtoeSimpleMenuItem::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	int16 contentWidth = width - GetMarginLeft() - GetMarginRight() - GetPaddingLeft() - GetPaddingRight();
	size.x = width;
	size.y = 0;
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Prepare(renderContext,contentWidth);
		size.y += item->GetSize().y;
	}
	RearrangeChildItems();
}
void CtoeSimpleMenuItem::RearrangeChildItems()
{
	CIwSVec2 topLeft = GetOrigin();
	topLeft.x += GetMarginLeft()+GetPaddingLeft();
	topLeft.y += GetMarginTop()+GetPaddingTop();
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->SetOrigin(topLeft);
		topLeft.y += item->GetSize().y;
	}
}
//Render image on the screen surface
void CtoeSimpleMenuItem::Render(toeSimpleMenuItemContext* renderContext)
{
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Render(renderContext);
	}
}

#ifdef IW_BUILD_RESOURCES
//Parses from text file: start block.
void	CtoeSimpleMenuItem::ParseOpen(CIwTextParserITX* pParser)
{
	CIwManaged::ParseOpen(pParser);
}


//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuItem::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("margin", pAttrName))
	{
		pParser->ReadInt16(&margin.x);
		margin.y = margin.z = margin.w = margin.x;
		return true;
	}
	if (!stricmp("margin-left", pAttrName))
	{
		pParser->ReadInt16(&margin.x);
		return true;
	}
	if (!stricmp("margin-right", pAttrName))
	{
		pParser->ReadInt16(&margin.z);
		return true;
	}
	if (!stricmp("margin-top", pAttrName))
	{
		pParser->ReadInt16(&margin.y);
		return true;
	}
	if (!stricmp("margin-bottom", pAttrName))
	{
		pParser->ReadInt16(&margin.w);
		return true;
	}
	if (!stricmp("padding", pAttrName))
	{
		pParser->ReadInt16(&padding.x);
		padding.y = padding.z = padding.w = padding.x;
		return true;
	}
	if (!stricmp("padding-left", pAttrName))
	{
		pParser->ReadInt16(&padding.x);
		return true;
	}
	if (!stricmp("padding-right", pAttrName))
	{
		pParser->ReadInt16(&padding.z);
		return true;
	}
	if (!stricmp("padding-top", pAttrName))
	{
		pParser->ReadInt16(&padding.y);
		return true;
	}
	if (!stricmp("padding-bottom", pAttrName))
	{
		pParser->ReadInt16(&padding.w);
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}
//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeSimpleMenuItem::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
	//CIwManaged::ParseCloseChild(pParser, pChild);
	childItems.Add(pChild);
}
#endif
