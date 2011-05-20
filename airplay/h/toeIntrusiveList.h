#pragma once

namespace TinyOpenEngine
{
	template<class T> class TtoeIntrusiveList;

	template<class T> class TtoeIntrusiveListItem
	{
	protected:
		TtoeIntrusiveList*	listContainer;
		TtoeIntrusiveListItem* prevSibling;
		TtoeIntrusiveListItem* nextSibling;
	public:
		inline TtoeIntrusiveListItem():listContainer(0){}
	};

	template<class T> class TtoeIntrusiveList
	{
	protected:
		TtoeIntrusiveListItem* firstChild;
		TtoeIntrusiveListItem* lastChild;
	public:
		inline TtoeIntrusiveList():firstChild(0),lastChild(0){}
	};
}