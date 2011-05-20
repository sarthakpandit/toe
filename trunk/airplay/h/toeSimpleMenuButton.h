#pragma once

#include <IwResManager.h>
#include <IwManagedList.h>
#include "toeSimpleMenuClickable.h"

namespace TinyOpenEngine
{
	class CtoeSimpleMenuButton : public CtoeSimpleMenuClickable
	{
	private:
	public:
		//Declare managed class
		IW_MANAGED_DECLARE(CtoeSimpleMenuButton);
		//Constructor
		CtoeSimpleMenuButton();
		//Desctructor
		virtual ~CtoeSimpleMenuButton();

		virtual uint32 GetElementNameHash();
	};
}