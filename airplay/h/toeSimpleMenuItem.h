#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

#include <toeInput.h>
#include <toeFreeTypeFont.h>
#include <toeSimpleMenuStyle.h>
#include <toeSimpleMenuStyleSheet.h>
#include <toeScriptingSubsystem.h>

namespace TinyOpenEngine
{
	struct toeSimpleMenuItemContext
	{
		CtoeSimpleMenuStyleSettings* parentStyle;
		CtoeSimpleMenuStyleSheet* styleSheet;
		CIwSVec2 viewportPos;
		CIwSVec2 viewportSize;
		toeSimpleMenuItemContext():parentStyle(0),styleSheet(0){};
	};
	class CtoeSimpleMenuRoot;
	class CtoeSimpleMenuItem : public CIwManaged
	{
	protected:
		CIwManagedList childItems;
		CIwSVec2 origin;
		CIwSVec2 size;
		uint32 styleClass;
		uint32 state;
		//CIwSVec4 margin;
		//CIwSVec4 padding;
		CtoeSimpleMenuRoot*root;
		CtoeSimpleMenuItem*parent;
		CtoeSimpleMenuStyle style;
		CtoeSimpleMenuStyleSettings combinedStyle;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuItem);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
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
		bool IsVisible(toeSimpleMenuItemContext* renderContext);
		const CIwSVec2& GetOrigin() const {return origin;}
		//Gets size of the item. It's only valid after Prepare method been executed
		const CIwSVec2& GetSize() const {return size;}
		virtual void SetOrigin(const CIwSVec2& v) { if (origin!=v) { origin=v;RearrangeChildItems(); }}

		//Method walks through child items and collect active ones into plain list
		//virtual void CollectActiveItems(CIwArray<CtoeSimpleMenuItem*>& collection);

		virtual void RearrangeChildItems();

		inline int16 GetMarginLeft()const {return combinedStyle.GetMarginLeft(1);}
		inline int16 GetMarginTop()const {return combinedStyle.GetMarginTop(1);}
		inline int16 GetMarginRight()const {return combinedStyle.GetMarginRight(1);}
		inline int16 GetMarginBottom()const {return combinedStyle.GetMarginBottom(1);}

		inline int16 GetPaddingLeft()const {return combinedStyle.GetPaddingLeft(1);}
		inline int16 GetPaddingTop()const {return combinedStyle.GetPaddingTop(1);}
		inline int16 GetPaddingRight()const {return combinedStyle.GetPaddingRight(1);}
		inline int16 GetPaddingBottom()const {return combinedStyle.GetPaddingBottom(1);}
		inline CtoeSimpleMenuRoot*GetRoot()const{return root;}
		inline CtoeSimpleMenuItem*GetParent()const{return parent;}

		void CombineStyle(toeSimpleMenuItemContext* renderContext);
		virtual void InheritStyle(CtoeSimpleMenuStyleSettings* parentSettings);
		virtual void ApplyStyleSheet(CtoeSimpleMenuStyleSheet* styleSheet);
		virtual void ApplyStyle(CtoeSimpleMenuStyle* style);
		virtual uint32 GetElementNameHash();
		virtual uint32 GetElementClassHash();
		virtual uint32 GetElementStateHash();
		//Finds an active item in children
		virtual CtoeSimpleMenuItem* FindActiveItemAt(const CIwVec2 & item);
		virtual void SetFocus(bool f);
		virtual void Touch(TouchContext* touchContext);
		virtual void TouchReleased(TouchContext* touchContext);
		virtual void TouchMotion(TouchContext* touchContext);
		virtual bool IsActive() const {return false;}
		virtual CtoeSimpleMenuItem* FindActiveItemForward(CtoeSimpleMenuItem* &skipItem, int & toSkip);
		virtual CtoeSimpleMenuItem* FindActiveItemBackward(CtoeSimpleMenuItem* &skipItem,int & toSkip);
		void InitTree(CtoeSimpleMenuRoot*,CtoeSimpleMenuItem*);

		void Test();
		int TestInt();
		void TestA(int a);
		int TestIntA(int a);
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