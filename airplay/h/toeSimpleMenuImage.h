#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuTerminalItem.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuImage : public CtoeSimpleMenuTerminalItem
	{
	private:
		uint32 textureHash;
		CIwTexture* texture;
		CIwMaterial* material;
		CIwSVec2 rectPos;
		CIwSVec2 rectSize;
		CIwSVec2 rectUV;
		CIwSVec2 rectUVSize;
		CIwColour rectColour[4];
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuImage);
		//Constructor
		CtoeSimpleMenuImage();
		//Desctructor
		virtual ~CtoeSimpleMenuImage();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);

		virtual void RearrangeChildItems();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}