//================
// HtmlColumn.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlTable.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//========
// Common
//========

SIZE_T HtmlColumn::WriteToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', level*2);
size+=writer.Print("<col ");
if(m_Style)
	{
	size+=writer.Print("style=\"");
	size+=writer.Print(m_Style);
	size+=writer.Print("\"");
	}
size+=writer.Print("/>");
return size;
}


//==========================
// Con-/Destructors Private
//==========================

HtmlColumn::HtmlColumn(HtmlTable* table, LPCSTR style):
m_Style(style)
{
table->Columns->Add(this);
}

}}}