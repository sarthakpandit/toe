#include <s3e.h>
#include "TinyOpenEngine.FreeType.h"
#include "TinyOpenEngine.SimpleMenu.h"
#include "toeSimpleMenu.h"
#include "toeSimpleMenuInputComponent.h"
#include "toeSimpleMenuItem.h"
#include "toeSimpleMenuRoot.h"
#include "toeSimpleMenuTextBlock.h"
#include "toeSimpleMenuImage.h"
#include "toeSimpleMenuBackground.h"
#include "toeSimpleMenuStyle.h"

using namespace TinyOpenEngine;

namespace TinyOpenEngine
{
	bool isTinyOpenEngineSimpleMenuInitialized = false;
}

void TinyOpenEngine::toeSimpleMenuInit()
{
	if (isTinyOpenEngineSimpleMenuInitialized)
		return;
	isTinyOpenEngineSimpleMenuInitialized = true;

	toeFreeTypeInit();

	#ifdef IW_BUILD_RESOURCES
	IwGetResManager()->AddHandler(new CtoeSimpleMenuRootResHandler);
	IwGetResManager()->AddHandler(new CtoeSimpleMenuStyleSheetResHandler);
	#endif

	IW_CLASS_REGISTER(CtoeSimpleMenu);
	IW_CLASS_REGISTER(CtoeSimpleMenuBackground);
	IW_CLASS_REGISTER(CtoeSimpleMenuRoot);
	IW_CLASS_REGISTER(CtoeSimpleMenuImage);
	IW_CLASS_REGISTER(CtoeSimpleMenuInputComponent);
	IW_CLASS_REGISTER(CtoeSimpleMenuItem);
	IW_CLASS_REGISTER(CtoeSimpleMenuTextBlock);
	IW_CLASS_REGISTER(CtoeSimpleMenuStyleSheet);
}

void TinyOpenEngine::toeSimpleMenuTerminate()
{
	if (!isTinyOpenEngineSimpleMenuInitialized)
		return;
	isTinyOpenEngineSimpleMenuInitialized = false;

	toeFreeTypeTerminate();
}