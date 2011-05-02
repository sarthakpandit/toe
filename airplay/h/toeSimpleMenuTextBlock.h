#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuTerminalItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuTextBlock : public CtoeSimpleMenuTerminalItem
	{
	private:
		char* utf8string;
		uint32 totalGlyphs;
		CtoeFreeTypeGlyphLayoutData layoutData;
		CIwColour glyphColor[4];
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuTextBlock);
		//Constructor
		CtoeSimpleMenuTextBlock();
		//Desctructor
		virtual ~CtoeSimpleMenuTextBlock();

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