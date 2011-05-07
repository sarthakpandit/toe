#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuImageCarousel : public CtoeSimpleMenuItem
	{
	private:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuImageCarousel);
		//Constructor
		CtoeSimpleMenuImageCarousel();
		//Desctructor
		virtual ~CtoeSimpleMenuImageCarousel();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);
		//Method walks through child items and collect active ones into plain list
		virtual void CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection);
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}