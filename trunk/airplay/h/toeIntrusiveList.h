#pragma once

namespace TinyOpenEngine
{
	template<class T> class TtoeIntrusiveList;

	template<class T> class TtoeIntrusiveListItem
	{
		friend class TtoeIntrusiveList<T>;
	protected:
		TtoeIntrusiveList<T>*	listContainer;
		TtoeIntrusiveListItem<T>* prevSibling;
		TtoeIntrusiveListItem<T>* nextSibling;
	public:
		inline TtoeIntrusiveListItem():listContainer(0),prevSibling(0),nextSibling(0){}
		inline virtual ~TtoeIntrusiveListItem(){Detach();}

		inline T* GetPrevious() const {return static_cast<T*>(prevSibling); }
		inline T* GetNext() const {return static_cast<T*>(nextSibling); }

		void AttachHead(TtoeIntrusiveList<T>* node);
		void AttachTail(TtoeIntrusiveList<T>* node);
		void SwapNext();
		void SwapPrev();
		void InsertBefore(TtoeIntrusiveListItem<T>* node);
		void InsertAfter(TtoeIntrusiveListItem<T>* node);
		void Detach();
	};

	template<class T> class TtoeIntrusiveList
	{
		friend class TtoeIntrusiveListItem<T>;
	protected:
		TtoeIntrusiveListItem<T>* firstChild;
		TtoeIntrusiveListItem<T>* lastChild;
	public:
		inline TtoeIntrusiveList():firstChild(0),lastChild(0){}

		inline T* GetFirstChild() const {return static_cast<T*>(firstChild); }
		inline T* GetLastChild() const {return static_cast<T*>(lastChild); }
	};

	template<class T> inline void TtoeIntrusiveListItem<T>::AttachTail(TtoeIntrusiveList<T>* list)
	{
		Detach();
		listContainer = list;
		if (listContainer)
		{
			prevSibling = listContainer->lastChild;
			nextSibling = 0;
			listContainer->lastChild = this;
			if (!listContainer->firstChild)
				listContainer->firstChild = this;
			else
				prevSibling->nextSibling = this;
		}
	};


	template<class T> inline void TtoeIntrusiveListItem<T>::AttachHead(TtoeIntrusiveList<T>* list)
	{
		Detach();
		listContainer = list;
		if (listContainer)
		{
			prevSibling = 0;
			nextSibling = listContainer->firstChild;
			listContainer->firstChild = this;
			if (!listContainer->lastChild)
				listContainer->lastChild = this;
			else
				nextSibling->prevSibling = this;
		}
	};


	template<class T> inline void TtoeIntrusiveListItem<T>::Detach()
	{
		if (!listContainer) return;
		if (listContainer->lastChild == this) listContainer->lastChild = prevSibling;
		if (listContainer->firstChild == this) listContainer->firstChild = nextSibling;
		if (nextSibling) nextSibling->prevSibling = prevSibling;
		if (prevSibling) prevSibling->nextSibling = nextSibling;
		listContainer = 0;
	};

}