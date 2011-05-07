#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuRoot.h"
#include "toeSimpleMenuItem.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuRoot);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuRoot);

//Constructor
CtoeSimpleMenuRoot::CtoeSimpleMenuRoot()
{
	styleSheet= 0;
	styleSheetHash = 0;
	contentOffset = 0;
	contentAreaHeight = 100;
	contentAreaOffset = 0;
	scrollAnimationAcc = 0;
	isTouched = false;
}
//Desctructor
CtoeSimpleMenuRoot::~CtoeSimpleMenuRoot()
{
	childItems.Delete();
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuRoot::Serialise ()
{
	CIwResource::Serialise();
	childItems.Serialise();
	style.Serialise();
	IwSerialiseUInt32(styleSheetHash);
	if (IwSerialiseIsReading() && styleSheetHash)
	{
		styleSheet = (CtoeSimpleMenuStyleSheet*)IwGetResManager()->GetResHashed(styleSheetHash,"CtoeSimpleMenuStyleSheet");
	}
	if (IwSerialiseIsReading())
	{
		CollectActiveItems();
	}
}
//Render image on the screen surface
void CtoeSimpleMenuRoot::Render()
{
	toeSimpleMenuItemContext renderContext;
	if (styleSheet)
		styleSheet->Apply(&styleSettings, IwHashString("SIMPLEMENU"), TOE_ANYSTYLE, TOE_ANYSTYLE);
	style.Apply(&styleSettings);
	renderContext.parentStyle = &styleSettings;
	renderContext.styleSheet = styleSheet;
	//renderContext.font = (CtoeFreeTypeFont*)IwGetResManager()->GetResNamed("Steinerlight","CtoeFreeTypeFont");
	//renderContext.font = (CtoeFreeTypeFont*)IwGetResManager()->GetResNamed("font","CtoeFreeTypeFont");
	int16 w = IwGxGetScreenWidth();
	int16 h = IwGxGetScreenHeight();
	styleSettings.Background.Render(CIwSVec2::g_Zero,CIwSVec2(w,h));
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Prepare(&renderContext,w);
	}
	AlignBlocks();
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->Render(&renderContext);
	}
}
void CtoeSimpleMenuRoot::Update(iwfixed dt)
{
	CtoeSimpleMenuItem* content=0;
		if (childItems.GetSize() > 0)
		content = static_cast<CtoeSimpleMenuItem*>(childItems[0]);

	if (!isTouched)
	{
		if (content)
		{
			int16 contentHeight = content->GetSize().y;
			int16 minContent = 0;
			int16 maxContent = 0;
			if (contentHeight <= contentAreaHeight)
			{
				maxContent = contentHeight-contentAreaHeight;
			}
			else
			{
				maxContent = minContent = (contentHeight-contentAreaHeight)/2;
			}
			if (contentOffset < minContent)
			{
				contentOffset = minContent+(contentOffset-minContent)/2;
				scrollAnimation = 0;
			}
			else if (contentOffset > maxContent)
			{
				contentOffset = maxContent+(contentOffset-maxContent)/2;
				scrollAnimation = 0;
			}
			else
			{
				contentOffset += scrollAnimation;
				scrollAnimation = scrollAnimation*8/10;
			}
			content->SetOrigin(CIwSVec2(0,contentAreaOffset+contentOffset));
		}
	}
	else
	{
		scrollAnimation = scrollAnimationAcc;
		scrollAnimationAcc = 0;
	}
}
void CtoeSimpleMenuRoot::AlignBlocks()
{
	CtoeSimpleMenuItem* content=0;
	CtoeSimpleMenuItem* header=0;
	CtoeSimpleMenuItem* footer=0;
	if (childItems.GetSize() > 0)
		content = static_cast<CtoeSimpleMenuItem*>(childItems[0]);
	if (childItems.GetSize() > 1)
		header = static_cast<CtoeSimpleMenuItem*>(childItems[1]);
	if (childItems.GetSize() > 2)
		footer = static_cast<CtoeSimpleMenuItem*>(childItems[2]);
	contentAreaHeight = (int16)IwGxGetScreenHeight();
	contentAreaOffset =0;
	if (header)
	{
		header->SetOrigin(CIwSVec2(0,0));
		contentAreaOffset += header->GetSize().y;
		contentAreaHeight -= header->GetSize().y;
	}
	if (footer)
	{
		footer->SetOrigin(CIwSVec2(0,contentAreaOffset+contentAreaHeight-footer->GetSize().y));
		contentAreaHeight -= footer->GetSize().y;
	}

}
void CtoeSimpleMenuRoot::CollectActiveItems()
{
	collection.clear();
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		item->CollectActiveItems(collection);
	}
}
#ifdef IW_BUILD_RESOURCES
//Parses from text file: start block.
void	CtoeSimpleMenuRoot::ParseOpen(CIwTextParserITX* pParser)
{
	CIwResource::ParseOpen(pParser);
}
//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuRoot::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("styleSheet",pAttrName))
	{
		pParser->ReadStringHash(&styleSheetHash);
		return true;
	}
	if (!stricmp("style",pAttrName))
	{
		pParser->PushObject(&style);
		return true;
	}
	return CIwResource::ParseAttribute(pParser, pAttrName);
}
//Parses from text file: end block.
void	CtoeSimpleMenuRoot::ParseClose(CIwTextParserITX* pParser)
{
	IwGetResManager()->GetCurrentGroup()->AddRes(IwHashString("CtoeSimpleMenuRoot"), this);
}
//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
void	CtoeSimpleMenuRoot::ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild)
{
	if (&style == (CtoeSimpleMenuStyle*)pChild)
		return;
	//CIwResource::ParseCloseChild(pParser, pChild);
	childItems.Add(pChild);
}

IW_MANAGED_IMPLEMENT(CtoeSimpleMenuRootResHandler)

//Constructor
CtoeSimpleMenuRootResHandler::CtoeSimpleMenuRootResHandler(): CIwResHandler("simplemenu", "CtoeSimpleMenuRoot")
{
	SetName("TOESIMPLEMENU");
}
//Desctructor
CtoeSimpleMenuRootResHandler::~CtoeSimpleMenuRootResHandler()
{
}

//Buid resource method
CIwResource*	CtoeSimpleMenuRootResHandler::Build(const CIwStringL& pathname)
{
	IwGetTextParserITX()->ParseFile(pathname.c_str());
	return NULL;
}

#endif