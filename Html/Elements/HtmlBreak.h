//=============
// HtmlBreak.h
//=============

#pragma once


//=======
// Using
//=======

#include "HtmlElement.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============
// HTML-Break
//============

class HtmlBreak: public HtmlElement
{
public:
	// Con-/Destructors
	static inline Handle<HtmlBreak> Create(HtmlNode* Parent, UINT Count=1)
		{
		return new HtmlBreak(Parent, Count);
		}

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Con-/Destructors
	HtmlBreak(HtmlNode* Parent, UINT Count);

	// Common
	UINT m_Count;
};

}}