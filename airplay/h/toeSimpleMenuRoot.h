#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>

namespace TinyOpenEngine
{
	class CtoeSimpleMenuRoot : public CIwResource
	{
	protected:
		CIwManagedList childItems;

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

		void AlignBlocks();
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