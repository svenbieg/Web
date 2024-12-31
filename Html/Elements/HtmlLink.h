//============
// HtmlLink.h
//============

#pragma once


//=======
// Using
//=======

#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//===========
// HTML-Link
//===========

class HtmlLink: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlLink> Create(HtmlNode* Parent, Handle<Sentence> Link, Handle<Sentence> Text=nullptr)
		{
		return new HtmlLink(Parent, Link, Text);
		}

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Con-/Destructors
	HtmlLink(HtmlNode* Parent, Handle<Sentence> Link, Handle<Sentence> Text);

	// Common
	Handle<Sentence> m_Link;
};

}}