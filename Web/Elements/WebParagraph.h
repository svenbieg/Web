//================
// WebParagraph.h
//================

#pragma once


//=======
// Using
//=======

#include "Html/Elements/HtmlNode.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//===============
// Web-Paragraph
//===============

class WebParagraph: public Html::Elements::HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<WebParagraph> Create(HtmlNode* Parent, Handle<Sentence> Caption=nullptr)
		{
		return new WebParagraph(Parent, Caption);
		}

protected:
	// Con-/Destructors
	WebParagraph(HtmlNode* Parent, Handle<Sentence> Caption);
};

}}