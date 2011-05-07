#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuButton.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuButton);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuButton);

//Constructor
CtoeSimpleMenuButton::CtoeSimpleMenuButton()
{

}
//Desctructor
CtoeSimpleMenuButton::~CtoeSimpleMenuButton()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuButton::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuButton::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuButton::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}
uint32 CtoeSimpleMenuButton::GetElementNameHash()
{
	static uint32 name = IwHashString("BUTTON");
	return name;
}
//Method walks through child items and collect active ones into plain list
void CtoeSimpleMenuButton::CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection)
{
	CtoeSimpleMenuItem::CollectActiveItems(collection);
	collection.push_back(this);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuButton::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
