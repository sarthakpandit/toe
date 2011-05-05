#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include <toeFreeTypeFont.h>
#include <toeSimpleMenuBackground.h>

namespace TinyOpenEngine
{
	struct CtoeSimpleMenuStyleSettings
	{
		uint32 FontHash;
		CtoeFreeTypeFont* Font;
		CtoeLength FontSize;
		CIwColour FontColor;
		CtoeSimpleMenuBackground Background;
		CIwSVec4 Margin;
		CIwSVec4 Padding;
		CtoeSimpleMenuStyleSettings():FontHash(0),Font(0),Margin(CIwSVec4::g_Zero),Padding(CIwSVec4::g_Zero){ FontColor.Set(0xFF000000);}
		void Serialise();
		void Inherit(CtoeSimpleMenuStyleSettings* other)
		{
			if (!other)
				return;
			FontHash = other->FontHash;
			Font = other->Font;
			FontSize = other->FontSize;
			FontColor = other->FontColor;
		}
	};

	class CtoeSimpleMenuStyle: public CIwManaged
	{
	public:
		CtoeSimpleMenuStyleSettings settings;
	protected:
		bool isFont;
		bool isFontSize;
		bool isFontColor;
		bool isBackground;
		bool isMargin;
		bool isPadding;
	public:
		CtoeSimpleMenuStyle():isFont(false),isFontSize(false),isFontColor(false),isBackground(false),isMargin(false),isPadding(false){}
		virtual void Serialise();
		void Apply(CtoeSimpleMenuStyleSettings* other)
		{
			if (isFont)
			{
				other->FontHash = settings.FontHash;
				other->Font = settings.Font;
			}
			if (isFontSize)
				other->FontSize = settings.FontSize;
			if (isFontColor)
				other->FontColor = settings.FontColor;
			if (isBackground)
				other->Background = settings.Background;
			if (isMargin)
				other->Margin = settings.Margin;
			if (isPadding)
				other->Padding = settings.Padding;
		}

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}