//===============
// HtmlCaption.h
//===============

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


//==============
// HTML-Caption
//==============

class HtmlCaption: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlCaption> Create(HtmlNode* Parent, Handle<Sentence> Text)
		{
		return new HtmlCaption(Parent, Text);
		}

private:
	// Con-/Destructors
	HtmlCaption(HtmlNode* Parent, Handle<Sentence> Text);
};

}}