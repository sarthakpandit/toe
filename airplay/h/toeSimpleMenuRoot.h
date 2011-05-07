#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuStyleSheet.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuItem;
	class CtoeSimpleMenuRoot : public CIwResource
	{
	protected:
		CIwManagedList childItems;
		uint32 styleSheetHash;
		CtoeSimpleMenuStyleSettings styleSettings;
		CtoeSimpleMenuStyle style;
		CtoeSimpleMenuStyleSheet* styleSheet;
		int16 contentOffset;
		int16 scrollAnimation;
		int16 contentAreaHeight;
		int16 contentAreaOffset;
		int16 scrollAnimationAcc;
		bool isTouched;
		CIwArray<CtoeSimpleMenuItem*> collection;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuRoot);
		//Constructor
		CtoeSimpleMenuRoot();
		//Desctructor
		virtual ~CtoeSimpleMenuRoot();

		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
		//Render image on the screen surface
		void Render();
		//Update
		void Update(iwfixed dt);

		void AlignBlocks();

		//Method walks through child items and collect active ones into plain list
		void CollectActiveItems();

#ifdef IW_BUILD_RESOURCES
		//Parses from text file: start block.
		virtual	void	ParseOpen(CIwTextParserITX* pParser);
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
		//Parses from text file: end block.
		virtual	void	ParseClose(CIwTextParserITX* pParser);
		//Extends CIwParseable interface with this extra function: called on any "parent" object, if the "child" has not implemented ParseClose.
		virtual	void	ParseCloseChild(CIwTextParserITX* pParser, CIwManaged* pChild);
#endif
	};

#ifdef IW_BUILD_RESOURCES
	class CtoeSimpleMenuRootResHandler : public CIwResHandler
	{
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuRootResHandler);

		//Constructor
		CtoeSimpleMenuRootResHandler();
		//Desctructor
		virtual ~CtoeSimpleMenuRootResHandler();

		//Buid resource method
		virtual CIwResource*	Build(const CIwStringL& pathname);
	};
#endif
}