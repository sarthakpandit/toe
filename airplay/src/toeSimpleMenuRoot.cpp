#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "TinyOpenEngine.SimpleMenu.h"
#include "toeSimpleMenuRoot.h"
#include "toeSimpleMenuItem.h"
#include "toeSimpleMenu.h"

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
	activeTouch = 0;
	activeItem = 0;
	isVerticalScrolled = false;
	simpleMenu= 0;
}
//Desctructor
CtoeSimpleMenuRoot::~CtoeSimpleMenuRoot()
{
	childItems.Delete();
}
//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeSimpleMenuRoot::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeSimpleMenuRoot> d ("CtoeSimpleMenuRoot",
//			ScriptTraits::Method("GetRoot", &CtoeSimpleMenuRoot::GetRoot),
			0);
	return &d;
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuRoot::Serialise ()
{
	CIwResource::Serialise();
	childItems.Serialise();
	style.Serialise();
	IwSerialiseUInt32(styleSheetHash);
	if (IwSerialiseIsReading())
	{
		if (styleSheetHash)
		{
			styleSheet = (CtoeSimpleMenuStyleSheet*)IwGetResManager()->GetResHashed(styleSheetHash,"CtoeSimpleMenuStyleSheet");
		}
		for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
		{
			CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
			item->InitTree(this,0);
		}
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
	renderContext.viewportPos = CIwSVec2::g_Zero;
	//renderContext.font = (CtoeFreeTypeFont*)IwGetResManager()->GetResNamed("Steinerlight","CtoeFreeTypeFont");
	//renderContext.font = (CtoeFreeTypeFont*)IwGetResManager()->GetResNamed("font","CtoeFreeTypeFont");
	int16 w = IwGxGetScreenWidth();
	int16 h = IwGxGetScreenHeight();
	renderContext.viewportSize = CIwSVec2(w,h);
	//renderContext.transformation.SetRot(IW_GEOM_ONE/8, CIwVec2(w/2,h/2));
	styleSettings.Background.Render(CIwSVec2::g_Zero,CIwSVec2(w,h), renderContext.transformation);
	
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

	CtoeSimpleMenuItem* content=GetContent();
	if (activeTouch && content)
	{
		int16 contentHeight = content->GetSize().y;
		if (contentHeight)
		{
			int16 contentVisibleTop = -contentOffset;
			
			int16 contentVisibleBottom = contentVisibleTop + contentAreaHeight;
			if (contentVisibleTop < 0)
				contentVisibleTop = 0;
			if (contentVisibleTop > contentHeight)
				contentVisibleTop = contentHeight;
			if (contentVisibleBottom < 0)
				contentVisibleBottom = 0;
			if (contentVisibleBottom > contentHeight)
				contentVisibleBottom = contentHeight;
			if (contentVisibleTop <  contentVisibleBottom)
			{
				int16 stop = contentVisibleTop*contentAreaHeight/contentHeight;
				int16 sbottom = contentVisibleBottom*contentAreaHeight/contentHeight;
				toeDrawSimpleMenuScrollbar(CIwSVec2(renderContext.viewportSize.x-4,contentAreaOffset-1),CIwSVec2(4,contentAreaHeight+2),
					CIwSVec2(renderContext.viewportSize.x-3,contentAreaOffset+stop),CIwSVec2(2,sbottom-stop));
			}
		}
	}
}
void CtoeSimpleMenuRoot::Update(iwfixed dt)
{
	CtoeSimpleMenuItem* content=GetContent();

	if (!activeTouch)
	{
		if (content)
		{
			int16 contentHeight = content->GetSize().y;
			int16 minContent = 0;
			int16 maxContent = 0;
			if (contentHeight > contentAreaHeight)
			{
				minContent = contentAreaHeight-contentHeight;
			}
			else
			{
				maxContent = minContent = (contentAreaHeight-contentHeight)/2;
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
		content->SetOrigin(CIwSVec2(0,contentAreaOffset+contentOffset));
	}
}
void CtoeSimpleMenuRoot::AlignBlocks()
{
	//CtoeSimpleMenuItem* content=GetContent();
	CtoeSimpleMenuItem* header=GetHeader();
	CtoeSimpleMenuItem* footer=GetFooter();

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
CtoeSimpleMenuItem* CtoeSimpleMenuRoot::FindActiveItemForward(CtoeSimpleMenuItem* &skipItem, int & toSkip)
{
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		CtoeSimpleMenuItem* foundItem = item->FindActiveItemForward(skipItem,toSkip);
		if (foundItem)
			return foundItem;
	}
	return 0;
}
CtoeSimpleMenuItem* CtoeSimpleMenuRoot::FindActiveItemBackward(CtoeSimpleMenuItem* &skipItem,int & toSkip)
{
	CIwManaged** i = childItems.GetEnd();
	for (; i!=childItems.GetBegin(); )
	{
		--i;
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		CtoeSimpleMenuItem* foundItem = item->FindActiveItemBackward(skipItem,toSkip);
		if (foundItem)
			return foundItem;
	}
	return 0;
}

CtoeSimpleMenuItem* CtoeSimpleMenuRoot::FindActiveItemAt(const CIwVec2 & coord)
{
	for (CIwManaged** i = childItems.GetBegin(); i!=childItems.GetEnd(); ++i)
	{
		CtoeSimpleMenuItem* item = static_cast<CtoeSimpleMenuItem*>(*i);
		CtoeSimpleMenuItem* foundItem = item->FindActiveItemAt(coord);
		if (foundItem)
			return foundItem;
	}
	return 0;
}
bool CtoeSimpleMenuRoot::KeyEvent(KeyContext* keyContext)
{
	if (keyContext->pressed)
	{
		switch (keyContext->key)
		{
		case s3eKeyUp:
			{
				CtoeSimpleMenuItem* skip = activeItem;
				int toSkip = 0;
				skip = FindActiveItemBackward(skip,toSkip);
				if (skip)
				{
					SetFocusTo(skip);
					ScrollToItem(skip);
				}
			}
			break;
		case s3eKeyDown:
			{
				CtoeSimpleMenuItem* skip = activeItem;
				int toSkip = 0;
				skip = FindActiveItemForward(skip,toSkip);
				if (skip)
				{
					SetFocusTo(skip);
					ScrollToItem(skip);
				}
			}
			break;
		case s3eKeyEnter:
		case s3eKeyOk:
			{
				CtoeSimpleMenuItem* skip = activeItem;
				if (skip)
				{
					TouchContext c;
					c.touchID = 0;
					c.lastKnownPoistion = c.firstKnownPoistion = c.currentPoistion = CIwSVec2::g_Zero;
					skip->Touch(&c);
					skip->TouchReleased(&c);
				}
			}
			break;
		default:
			break;
		}
	}
	return true;
}
void CtoeSimpleMenuRoot::ScrollToItem(CtoeSimpleMenuItem*i)
{
	CtoeSimpleMenuItem*p=i;
	while(p->GetParent()) p = p->GetParent();
	CtoeSimpleMenuItem*content=GetContent();
	if (p == content)
	{
		int16 contentHeight = content->GetSize().y;
		if (contentHeight > contentAreaHeight)
		{
			int16 minContent = contentAreaHeight-contentHeight;
			int16 curY = i->GetSize().y/2 + i->GetOrigin().y-contentAreaOffset;
			contentOffset = -curY+contentAreaHeight/2;
			if (contentOffset > 0)
				contentOffset = 0;
			else if (contentOffset < minContent)
				contentOffset = minContent;
		}
	}
}
void CtoeSimpleMenuRoot::Initialize(CtoeSimpleMenu*simpleMenuInstance)
{
	simpleMenu = simpleMenuInstance;
}
void CtoeSimpleMenuRoot::Eval(CtoeSimpleMenuItem*item, const char*s)
{
	if (!s || !*s)
		return;
	if (simpleMenu)
		simpleMenu->Eval(item,s);
}
void CtoeSimpleMenuRoot::SetFocusTo(CtoeSimpleMenuItem* i)
{
	if (activeItem == i)
		return;
	if (activeItem)
		activeItem->SetFocus(false);
	activeItem = i;
	if (activeItem)
		activeItem->SetFocus(true);
}
bool CtoeSimpleMenuRoot::TouchEvent(TouchContext* touchContext)
{
	activeTouch = touchContext;
	if (scrollAnimation != 0)
	{
		isVerticalScrolled = true;
		if (activeItem)
		{
			SetFocusTo(0);
			activeItem = 0;
		}
	}
	else
	{
		CtoeSimpleMenuItem* i = FindActiveItemAt(touchContext->currentPoistion);
		if (i)
		{
			if (activeItem != i)
			{
				SetFocusTo(i);
				i->Touch(touchContext);
			}
		}
	}
	return true;
}
bool CtoeSimpleMenuRoot::TouchReleaseEvent(TouchContext* touchContext)
{
	if (activeTouch == touchContext)
		activeTouch = 0;
	if (activeItem)
	{
		activeItem->TouchReleased(touchContext);
		activeItem->SetFocus(false);
		activeItem = 0;
	}
	isVerticalScrolled = false;
	return true;
}
bool CtoeSimpleMenuRoot::TouchMotionEvent(TouchContext* touchContext)
{
	if (activeTouch != touchContext)
		return false;
	CIwVec2 shift = touchContext->currentPoistion-touchContext->lastKnownPoistion;
	if (isVerticalScrolled || abs(touchContext->firstKnownPoistion.y - touchContext->currentPoistion.y) > 10)
	{
		isVerticalScrolled = true;
		if (activeItem)
		{
			SetFocusTo(0);
			activeItem = 0;
		}
		scrollAnimationAcc += shift.y;
		contentOffset += shift.y;
	}
	else
	{
		if (activeItem)
			activeItem->TouchMotion(touchContext);
	}
	return true;
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