#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

#include <toeFreeTypeFont.h>
#include <toeSimpleMenuStyle.h>
#include <toeSimpleMenuStyleSheet.h>

namespace TinyOpenEngine
{
	struct toeSimpleMenuItemContext
	{
		CtoeSimpleMenuStyleSettings* parentStyle;
		CtoeSimpleMenuStyleSheet* styleSheet;

		toeSimpleMenuItemContext():parentStyle(0),styleSheet(0){};
	};

	class CtoeSimpleMenuItem : public CIwManaged
	{
	protected:
		CIwManagedList childItems;
		CIwSVec2 origin;
		CIwSVec2 size;
		//CIwSVec4 margin;
		//CIwSVec4 padding;

		CtoeSimpleMenuStyle style;
		CtoeSimpleMenuStyleSettings combinedStyle;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuItem);
		//Constructor
		CtoeSimpleMenuItem();
		//Desctructor
		virtual ~CtoeSimpleMenuItem();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();

		//Evaluates size of item and prepares all nessesary things to render it
		virtual void Prepare(toeSimpleMenuItemContext* renderContext,int16 width);
		//Render image on the screen surface
		virtual void Render(toeSimpleMenuItemContext* renderContext);

		const CIwSVec2& GetOrigin() const {return origin;}
		//Gets size of the item. It's only valid after Prepare method been executed
		const CIwSVec2& GetSize() const {return size;}
		virtual void SetOrigin(const CIwSVec2& v) { if (origin!=v) { origin=v;RearrangeChildItems(); }}

		virtual void RearrangeChildItems();

		inline int16 GetMarginLeft()const {return combinedStyle.Margin.x;}
		inline int16 GetMarginTop()const {return combinedStyle.Margin.y;}
		inline int16 GetMarginRight()const {return combinedStyle.Margin.z;}
		inline int16 GetMarginBottom()const {return combinedStyle.Margin.w;}

		inline int16 GetPaddingLeft()const {return combinedStyle.Padding.x;}
		inline int16 GetPaddingTop()const {return combinedStyle.Padding.y;}
		inline int16 GetPaddingRight()const {return combinedStyle.Padding.z;}
		inline int16 GetPaddingBottom()const {return combinedStyle.Padding.w;}

		void CombineStyle(toeSimpleMenuItemContext* renderContext);
		virtual void InheritStyle(CtoeSimpleMenuStyleSettings* parentSettings);
		virtual void ApplyStyleSheet(CtoeSimpleMenuStyleSheet* styleSheet);
		virtual void ApplyStyle(CtoeSimpleMenuStyle* style);
		virtual uint32 GetElementNameHash();
		virtual uint32 GetElementClassHash();
		virtual uint32 GetElementStateHash();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
		virtual	void	ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild);
#endif
	};
}