//============
// HtmlText.h
//============

#pragma once


//=======
// Using
//=======

#include "Culture/Sentence.h"
#include "HtmlElement.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//===========
// HTML-Text
//===========

class HtmlText: public HtmlElement
{
public:
	// Using
	using Sentence=Culture::Sentence;

	// Con-/Destructors
	static inline Handle<HtmlText> Create(HtmlNode* Parent, Handle<Sentence> Text)
		{
		return new HtmlText(Parent, Text);
		}

	// Common
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

private:
	// Con-/Destructors
	HtmlText(HtmlNode* Parent, Handle<Sentence> Text);

	// Common
	Handle<Sentence> m_Text;
};

}}