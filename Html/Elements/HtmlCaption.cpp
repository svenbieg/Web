//=================
// HtmlCaption.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "HtmlCaption.h"
#include "HtmlText.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==========================
// Con-/Destructors Private
//==========================

HtmlCaption::HtmlCaption(HtmlNode* parent, Handle<Sentence> text):
HtmlNode(parent, "h1")
{
HtmlText::Create(this, text);
}

}}