#include <IwTextParserITX.h>
#include <IwResManager.h>
#include <IwGx.h>
#include "TinyOpenEngine.h"
#include "toeSimpleMenuTextBox.h"
#include "toeSimpleMenuRoot.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	
}

//Instantiate the default factory function for a named class 
IW_CLASS_FACTORY(CtoeSimpleMenuTextBox);
//This macro is required within some source file for every class derived from CIwManaged. It implements essential functionality
IW_MANAGED_IMPLEMENT(CtoeSimpleMenuTextBox);

//Get scriptable class declaration
CtoeScriptableClassDeclaration* CtoeSimpleMenuTextBox::GetClassDescription()
{
	static  TtoeScriptableClassDeclaration<CtoeSimpleMenuTextBox> d ("CtoeSimpleMenuTextBox",
			ScriptTraits::Method("GetRoot", &CtoeSimpleMenuTextBox::GetRoot),
			ScriptTraits::Method("GetText", &CtoeSimpleMenuTextBox::GetText),
			ScriptTraits::Method("SetText", &CtoeSimpleMenuTextBox::SetText),
			0);
	return &d;
}

//Constructor
CtoeSimpleMenuTextBox::CtoeSimpleMenuTextBox()
{
}
//Desctructor
CtoeSimpleMenuTextBox::~CtoeSimpleMenuTextBox()
{
}
//Reads/writes a binary file using @a IwSerialise interface.
void CtoeSimpleMenuTextBox::Serialise ()
{
	CtoeSimpleMenuTextBlock::Serialise();
	toeSerialiseString(onChanged);
}

#ifdef IW_BUILD_RESOURCES

//Parses from text file: parses attribute/value pair.
bool	CtoeSimpleMenuTextBox::ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName)
{
	if (!stricmp("onchange",pAttrName))
	{
		toeReadString(pParser, &onChanged);
		return true;
	}
	return CtoeSimpleMenuTextBlock::ParseAttribute(pParser, pAttrName);
}

#endif