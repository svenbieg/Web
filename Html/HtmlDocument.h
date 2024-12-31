//================
// HtmlDocument.h
//================

#pragma once


//=======
// Using
//=======

#include "Elements/HtmlHead.h"


//===========
// Namespace
//===========

namespace Html {


//===============
// HTML-Document
//===============

class HtmlDocument: public Elements::HtmlElement
{
public:
	// Using
	using HtmlHead=Elements::HtmlHead;
	using HtmlNode=Elements::HtmlNode;

	// Con-/Destructors
	static inline Handle<HtmlDocument> Create() { return new HtmlDocument(); }

	// Common
	inline VOID AddScript(LPCSTR Script) { Head->Script->Add(Script); }
	template <class _owner_t> VOID AddScript(_owner_t* Owner, SIZE_T (_owner_t::*Procedure)(OutputStream*, WebContext*))
		{
		Handle<_owner_t> owner=Owner;
		Head->Script->Add([owner, Procedure](OutputStream* stream, WebContext* context)
			{
			return (owner->*Procedure)(stream, context);
			});
		}
	inline VOID AddStyle(Handle<String> Class, LPCSTR Style) { Head->Styles->Add(Class, Style); }
	Handle<HtmlNode> Body;
	Handle<HtmlHead> Head;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level=0)override;

protected:
	// Con-/Destructors
	HtmlDocument();
};

}