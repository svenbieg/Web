//===============
// HtmlImage.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlImage.h"

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

SIZE_T HtmlImage::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
auto lng=context->Language;
SIZE_T size=HtmlNode::WriteAttributesToStream(stream, context);
StreamWriter writer(stream);
size+=writer.Print(" src=\"");
size+=writer.Print(m_Url->Begin(lng));
size+=writer.Print("\"");
return size;
}


//==========================
// Con-/Destructors Private
//==========================

HtmlImage::HtmlImage(HtmlNode* parent, Handle<Sentence> url):
HtmlNode(parent, "img"),
m_Url(url)
{}

}}