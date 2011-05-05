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
	style.Serialise();
}

void CtoeSimpleMenuItem::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CombineStyle(renderContext);
	toeSimpleMenuItemContext context = *renderContext;
	context.parentStyle = &combinedStyle;

	int16 contentWidth = width - GetMarginLeft() - GetMarginRight() - GetPaddingLeft() - GetPaddingRight();
	size.x = width;
	size.y = 0;
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Prepare(&context,contentWidth);
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
	toeSimpleMenuItemContext context = *renderContext;
	context.parentStyle = &combinedStyle;

	combinedStyle.Background.Render(GetOrigin()+CIwSVec2(GetMarginLeft(),GetMarginTop()), GetSize()-CIwSVec2(GetMarginLeft()+GetMarginRight(),GetMarginTop()+GetMarginBottom()));
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Render(&context);
	}
}
void CtoeSimpleMenuItem::CombineStyle(toeSimpleMenuItemContext* renderContext)
{
	InheritStyle(renderContext->parentStyle);
	ApplyStyleSheet(renderContext->styleSheet);
	ApplyStyle(&style);
}
void CtoeSimpleMenuItem::InheritStyle(CtoeSimpleMenuStyleSettings* parentSettings)
{
	combinedStyle.Inherit(parentSettings);
}
void CtoeSimpleMenuItem::ApplyStyleSheet(CtoeSimpleMenuStyleSheet* styleSheet)
{
	if (styleSheet)
		styleSheet->Apply(&combinedStyle,GetElementNameHash(),GetElementClassHash(),GetElementStateHash());
}
void CtoeSimpleMenuItem::ApplyStyle(CtoeSimpleMenuStyle* style)
{
	style->Apply(&combinedStyle);
}
uint32 CtoeSimpleMenuItem::GetElementNameHash() { return TOE_ANYSTYLE; }
uint32 CtoeSimpleMenuItem::GetElementClassHash() { return TOE_ANYSTYLE; }
uint32 CtoeSimpleMenuItem::GetElementStateHash() { return TOE_ANYSTYLE; }

#ifdef IW_BUILD_RESOURCES
//Parses from text file: start block.
void	CtoeSimpleMenuItem::ParseOpen(CIwTextParserITX* pParser)
{
	CIwManaged::ParseOpen(pParser);
}


//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuItem::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("style", pAttrName))
	{
		pParser->PushObject(&style);
		return true;
	}
	return CIwManaged::ParseAttribute(pParser, pAttrName);
}
//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeSimpleMenuItem::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
	//CIwManaged::ParseCloseChild(pParser, pChild);
	if (&style == (CtoeSimpleMenuStyle*)pChild)
		return;
	childItems.Add(pChild);
}
#endif
