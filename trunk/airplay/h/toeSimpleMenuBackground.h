#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuTerminalItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuBackground : public CtoeSimpleMenuTerminalItem
	{
	private:
		CIwColour colour;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuBackground);
		//Constructor
		CtoeSimpleMenuBackground();
		//Desctructor
		virtual ~CtoeSimpleMenuBackground();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}