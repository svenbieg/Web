//===============
// HtmlLabel.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlLabel.h"

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

SIZE_T HtmlLabel::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StreamWriter writer(stream);
if(m_Label)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	size+=writer.Print(m_Label->Begin(lng));
	}
size+=HtmlNode::WriteElementsToStream(stream, context, level);
if(m_Unit)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	size+=writer.Print(m_Unit->Begin(lng));
	}
return size;
}


//==========================
// Con-/Destructors Private
//==========================

HtmlLabel::HtmlLabel(HtmlNode* parent, Handle<Sentence> label, Handle<Sentence> unit):
HtmlNode(parent, "label"),
m_Label(label),
m_Unit(unit)
{}

}}