#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuTextBlock.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuTextBox : public CtoeSimpleMenuTextBlock
	{
	protected:
		std::string onChanged;
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuTextBox);
		//Get scriptable class declaration
		static CtoeScriptableClassDeclaration* GetClassDescription();
		//Get scriptable class declaration
		virtual CtoeScriptableClassDeclaration* GetInstanceClassDescription() {return GetClassDescription(); };
		//Get tree element name hash
		virtual uint32 GetElementNameHash();
		//Constructor
		CtoeSimpleMenuTextBox();
		//Desctructor
		virtual ~CtoeSimpleMenuTextBox();
		virtual bool IsActive() const {return true;}
		virtual void TouchReleased(TouchContext* touchContext);
		virtual void OnTextChanged();
		//Reads/writes a binary file using @a IwSerialise interface.
		virtual void Serialise ();
#ifdef IW_BUILD_RESOURCES
		//Parses from text file: parses attribute/value pair.
		virtual	bool	ParseAttribute(CIwTextParserITX* pParser, const char* pAttrName);
#endif
	};
}