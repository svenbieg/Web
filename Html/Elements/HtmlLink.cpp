//==============
// HtmlLink.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlLink.h"
#include "HtmlText.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Common Protected
//==================

SIZE_T HtmlLink::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
auto lng=context->Language;
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print(" href=\"");
size+=writer.Print(m_Link->Begin(lng));
size+=writer.Print("\"");
return size;
}


//==========================
// Con-/Destructors Private
//==========================

HtmlLink::HtmlLink(HtmlNode* parent, Handle<Sentence> link, Handle<Sentence> text):
HtmlNode(parent, "a"),
m_Link(link)
{
if(text)
	HtmlText::Create(this, text);
}

}}