//===============
// HtmlBreak.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlBreak.h"
#include "HtmlNode.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//==================
// Con-/Destructors
//==================

HtmlBreak::HtmlBreak(HtmlNode* parent, UINT count):
HtmlElement(parent),
m_Count(count)
{
parent->SetFlag(HtmlNodeFlags::MultiLine);
}


//========
// Common
//========

SIZE_T HtmlBreak::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', level*2);
for(UINT u=0; u<m_Count; u++)
	size+=writer.Print("<br />");
return size;
}

}}