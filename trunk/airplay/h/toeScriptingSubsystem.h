#pragma once

#include <IwArray.h>

namespace TinyOpenEngine
{
	class ItoeScriptingSubsystem;
	class CtoeScriptableClassDeclaration;

	class CtoeScriptableMethodDeclaration
	{
		const char* m_name;
	public:
		CtoeScriptableMethodDeclaration(const char* name):m_name(name) {}
		virtual ~CtoeScriptableMethodDeclaration() {};
		inline const char* GetMethodName() {return m_name;};
		virtual void Call(ItoeScriptingSubsystem*,CtoeScriptableClassDeclaration*,void*)=0;
		virtual bool IsStatic() const {return false;}
	};

	template <class T> class TtoeScriptableMethodDeclaration: public CtoeScriptableMethodDeclaration
	{
		void (T::*m_fn) ();
	public:
		TtoeScriptableMethodDeclaration(const char* name,void (T::*fn) ()):CtoeScriptableMethodDeclaration(name),m_fn(fn) {}
		virtual void Call(ItoeScriptingSubsystem* s,CtoeScriptableClassDeclaration*c,void* o) { (((T*)o)->*m_fn)(); }
	};

	template <class T, typename R> class TtoeScriptableMethodDeclarationR: public CtoeScriptableMethodDeclaration
	{
		R (T::*m_fn) ();
	public:
		TtoeScriptableMethodDeclarationR(const char* name,R (T::*fn) ()):CtoeScriptableMethodDeclaration(name),m_fn(fn) {}
		virtual void Call(ItoeScriptingSubsystem* s,CtoeScriptableClassDeclaration*c,void* o) { s->Return( (((T*)o)->*m_fn)() ); }
	};

	class CtoeScriptableClassDeclaration
	{
	protected:
		CIwArray<CtoeScriptableMethodDeclaration*> m_methods;
	public:
		virtual ~CtoeScriptableClassDeclaration() { for (CIwArray<CtoeScriptableMethodDeclaration*>::iterator i=m_methods.begin(); i!=m_methods.end(); ++i) delete *i; };
		virtual const char* GetClassName() =0;
		virtual void* CreateInstance() =0;
		virtual void DestroyInstance(void*) =0;
		virtual const char* ToString(void* t)=0;
		virtual int GetMethodsCount() { return m_methods.size(); }
		virtual CtoeScriptableMethodDeclaration* GetMethod(int i) { return m_methods[i]; }
	};

	class ItoeScriptingSubsystem
	{
	public:
		virtual ~ItoeScriptingSubsystem();

		virtual void Eval(const char*s)=0;

		virtual void RegisterClass(CtoeScriptableClassDeclaration*)=0;
		virtual void Return(int i)=0;
	};

	template <class T> class TtoeScriptableClassDeclaration: public CtoeScriptableClassDeclaration
	{
		const char* m_name;
	public:
		TtoeScriptableClassDeclaration(const char* name, ...);
		virtual ~TtoeScriptableClassDeclaration() {}
		virtual const char* GetClassName() {return m_name;}

		virtual void* CreateInstance() {return new T();}
		virtual void DestroyInstance(void* t) { delete (T*)t;}
		virtual const char* ToString(void* t) { return GetClassName(); }

		//virtual int GetMethodsCount() { return 0; }
		//virtual CtoeScriptableMethodDeclaration* GetMethod(int i) { return 0; }
		//static CtoeScriptableMethodDeclaration* M( void (T::*ptr)() ) { return 0;}
	};

	template <class T> TtoeScriptableClassDeclaration<T>::TtoeScriptableClassDeclaration(const char* name, ...)
	{
		m_name = name;
		va_list vl;
		va_start( vl, name );
		for (;;)
		{
			CtoeScriptableMethodDeclaration* arg = va_arg( vl, CtoeScriptableMethodDeclaration*);
			if (!arg)
				break;
			m_methods.push_back(arg);
		}
		va_end( vl );
	}
}