#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "toeSimpleMenuImageCarousel.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuImageCarousel);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuImageCarousel);

//Constructor
CtoeSimpleMenuImageCarousel::CtoeSimpleMenuImageCarousel()
{

}
//Desctructor
CtoeSimpleMenuImageCarousel::~CtoeSimpleMenuImageCarousel()
{
}

//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuImageCarousel::Serialise ()
{
	CtoeSimpleMenuItem::Serialise();
}
void CtoeSimpleMenuImageCarousel::Prepare(toeSimpleMenuItemContext* renderContext,int16 width)
{
	CtoeSimpleMenuItem::Prepare(renderContext,width);
}

//Render image on the screen surface
void CtoeSimpleMenuImageCarousel::Render(toeSimpleMenuItemContext* renderContext)
{
	CtoeSimpleMenuItem::Render(renderContext);
}
//Method walks through child items and collect active ones into plain list
void CtoeSimpleMenuImageCarousel::CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection)
{
	CtoeSimpleMenuItem::CollectActiveItems(collection);
	collection.push_back(this);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuImageCarousel::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	return CtoeSimpleMenuItem::ParseAttribute(pParser, pAttrName);
}

#endif
