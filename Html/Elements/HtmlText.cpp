//==============
// HtmlText.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlText.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Con-/Destructors
//==================

HtmlText::HtmlText(HtmlNode* parent, Handle<Sentence> text):
HtmlElement(parent),
m_Text(text)
{}


//========
// Common
//========

SIZE_T HtmlText::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
StreamWriter writer(stream);
return writer.Print(m_Text->Begin(context->Language));
}

}}