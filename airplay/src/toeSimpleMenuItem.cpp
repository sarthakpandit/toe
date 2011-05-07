#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuItem.h"
#include "toeSimpleMenuTextBlock.h"
#include "toeSimpleMenuImage.h"

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
	styleClass = TOE_ANYSTYLE;
	state = TOE_ANYSTYLE;
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
	IwSerialiseUInt32(styleClass);
	IwSerialiseUInt32(state);
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
	size.y += GetMarginTop()+GetPaddingTop()+GetMarginBottom()+GetPaddingBottom();
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
uint32 CtoeSimpleMenuItem::GetElementClassHash() { return styleClass; }
uint32 CtoeSimpleMenuItem::GetElementStateHash() { return state; }
void CtoeSimpleMenuItem::CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection)
{
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->CollectActiveItems(collection);
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
	if (!stricmp("style", pAttrName))
	{
		pParser->PushObject(&style);
		return true;
	}
	if (!stricmp("styleClass", pAttrName))
	{
		pParser->ReadStringHash(&styleClass);
		return true;
	}
	if (!stricmp("state", pAttrName))
	{
		pParser->ReadStringHash(&state);
		return true;
	}
	if (!stricmp("text", pAttrName))
	{
		CtoeSimpleMenuTextBlock* tb = new CtoeSimpleMenuTextBlock(pParser->ReadString());
		childItems.Add(tb);
		return true;
	}
	if (!stricmp("image", pAttrName))
	{
		uint32 t;
		pParser->ReadStringHash(&t);
		CtoeSimpleMenuImage* ti = new CtoeSimpleMenuImage(t);
		childItems.Add(ti);
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
