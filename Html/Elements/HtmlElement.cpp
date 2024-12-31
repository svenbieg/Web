//=================
// HtmlElement.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============================
// Con-/Destructors Protected
//============================

HtmlElement::HtmlElement(HtmlNode* Parent):
HtmlElement(Parent->Document, Parent)
{}

HtmlElement::HtmlElement(HtmlDocument* Document):
HtmlElement(Document, nullptr)
{}

HtmlElement::HtmlElement(HtmlDocument* doc, HtmlNode* parent):
Document(doc),
Parent(parent)
{
if(Parent)
	{
	Parent->Elements->Append(this);
	Parent->SetFlag(HtmlNodeFlags::MultiLine);
	}
}

}}