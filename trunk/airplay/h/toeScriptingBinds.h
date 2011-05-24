#pragma once

namespace TinyOpenEngine
{
	namespace ScriptTraits
	{
		template <class T> inline T FetchArgument()
		{
		};
		template <class T> inline void PushResult(ItoeScriptingSubsystem* system, T t)
		{
			system->Return(t);
		};
		template <> inline void PushResult<const char*>(ItoeScriptingSubsystem* system, const char* t)
		{
			system->Return(t);
		};
		template <class PTR> inline void PushResult(ItoeScriptingSubsystem* system, PTR* t)
		{
			system->Return(t, PTR::GetClassDescription());
		};

		template <class T, class R, typename mmm> class NoArgsMethod: public CtoeScriptableMethodDeclaration
		{
		public:
			typedef mmm METHOD;
			//typedef R (T::* METHOD)();
		protected:
			METHOD m;
		public:
			NoArgsMethod(const char* name, METHOD mm):CtoeScriptableMethodDeclaration(name),m(mm) {}
			R MakeCall(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				T* i = ((T*)instance);
				return (i->*m)();
			}
		};

		template <class R, class Caller> class MethodBase: public Caller
		{
		public:
			MethodBase(const char* name, typename Caller::METHOD m):Caller(name,m) {}
			virtual void Call(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				PushResult(system, Caller::MakeCall(system,cls,instance));
			}
		};
		template <class Caller> class MethodBase<void,Caller>: public Caller
		{
		public:
			MethodBase(const char* name, typename Caller::METHOD m):Caller(name,m) {}
			virtual void Call(ItoeScriptingSubsystem* system, CtoeScriptableClassDeclaration* cls, void* instance)
			{
				Caller::MakeCall(system,cls,instance);
				system->Return();
			}
		};
		inline CtoeScriptableMethodDeclaration* Method(const char* name, void (*fn) ())
		{
			return 0;
		};
		template <typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (*fn) ())
		{
			return 0;
		};
		template <typename R,typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (*fn) (A))
		{
			return 0;
		};
		template <typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, void (*fn) (A))
		{
			return 0;
		};
		template <class T, typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn) ())
		{
			return new MethodBase<R,NoArgsMethod<T,R,R (T::*) ()> >(name,fn);
		};
		template <class T, typename R> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn)  () const)
		{
			return new MethodBase<R,NoArgsMethod<T,R,R (T::*)  () const> >(name,fn);
		};
		template <class T, typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, void (T::*fn) (A))
		{
			return 0;
		};
		template <class T, typename R, typename A> inline CtoeScriptableMethodDeclaration* Method(const char* name, R (T::*fn) (A))
		{
			return 0;
		};
	}
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