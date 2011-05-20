#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "string"
#include "toeSimpleMenuItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuClickable : public CtoeSimpleMenuItem
	{
	private:
		std::string onClick;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuClickable);
		//Constructor
		CtoeSimpleMenuClickable();
		//Desctructor
		virtual ~CtoeSimpleMenuClickable();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);
		virtual uint32 GetElementNameHash();
		virtual bool IsActive() const {return true;}
		virtual void TouchReleased(TouchContext* touchContext);
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}