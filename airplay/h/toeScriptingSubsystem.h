#pragma once

namespace TinyOpenEngine
{
	class ItoeScriptingSubsystem
	{
	public:
		virtual ~ItoeScriptingSubsystem();

		virtual void Eval(const char*s)=0;
	};
}