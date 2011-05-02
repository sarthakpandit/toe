#include <IwTextParserITX.h>
#include <IwResManager.h>
#include "toeSimpleMenu.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenu);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenu);


namespace TinyOpenEngine
{
}


//Constructor
CtoeSimpleMenu::CtoeSimpleMenu()
{
	menulayout= 0;
	menu= 0;
}

//Desctructor
CtoeSimpleMenu::~CtoeSimpleMenu()
{
}
//Update subsystem state
void CtoeSimpleMenu::Update(iwfixed dt)
{
}
//Find all entities under the pointer
void CtoeSimpleMenu::PointerHitTest(HitTestContext* htc)
{
}

//Render image on the screen surface
void CtoeSimpleMenu::Render()
{
	if (menu)
	{
		menu->Render();
	}
}

//Prepare subsystem
void CtoeSimpleMenu::Initialize(CtoeWorld*w)
{
	CtoeSubsystem::Initialize(w);
	if (menulayout)
	{
		if (!menu)
		{
			menu = (CtoeSimpleMenuRoot*)IwGetResManager()->GetResHashed(menulayout,"CtoeSimpleMenuRoot");
		}
	}
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenu::Serialise ()
{
	CtoeSubsystem::Serialise();
	IwSerialiseUInt32(menulayout);
}


#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool CtoeSimpleMenu::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("menulayout", pAttrName))
	{
		pParser->ReadStringHash(&menulayout);
		return true;
	}
	return CtoeSubsystem::ParseAttribute(pParser,pAttrName);
}
#endif