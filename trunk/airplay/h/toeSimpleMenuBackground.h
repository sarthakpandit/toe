#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include <toeFreeTypeFont.h>

namespace TinyOpenEngine
{
	struct toeSimpleMenuBackgroundGradientPoint
	{
		CIwColour Colour;
		CtoeLength Position;
	};
	class CtoeSimpleMenuBackground: public CIwManaged
	{
	protected:
		uint32 textureHash;
		CIwTexture* texture;
		CIwArray<toeSimpleMenuBackgroundGradientPoint> points;
	public:
		//Constructor
		CtoeSimpleMenuBackground();
		//Desctructor
		virtual ~CtoeSimpleMenuBackground();

		virtual void Serialise();

		void Render(const CIwSVec2& origin, const CIwSVec2& size);
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);

		virtual	void	ParseClose(CIwTextParserITX* pParser);
#endif
	};
}