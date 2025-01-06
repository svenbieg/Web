//===============
// HtmlTable.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Storage/Streams/StreamWriter.h"
#include "HtmlTable.h"

using namespace Culture;
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

VOID HtmlTable::AddColumn(LPCSTR style)
{
HtmlColumn::Create(this, style);
}

Handle<HtmlRow> HtmlTable::AddRow()
{
return HtmlRow::Create(this);
}

SIZE_T HtmlTable::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StreamWriter writer(stream);
size+=WriteTagToStream(stream, level);
size+=WriteAttributesToStream(stream, context);
size+=writer.Print(">");
UINT child_level=level+1;
if(m_Caption)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', child_level*2);
	size+=writer.Print("<caption>");
	size+=writer.Print(m_Caption->Begin(lng));
	size+=writer.Print("</caption>");
	}
if(Columns->GetCount()>0)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', child_level*2);
	size+=writer.Print("<colgroup>");
	for(auto it=Columns->Begin(); it->HasCurrent(); it->MoveNext())
		{
		auto col=it->GetCurrent();
		size+=col->WriteToStream(stream, child_level+1);
		}
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', child_level*2);
	size+=writer.Print("</colgroup>");
	}
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', child_level*2);
size+=writer.Print("<tbody>");
size+=WriteElementsToStream(stream, context, child_level+1);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', child_level*2);
size+=writer.Print("</tbody>");
size+=WriteClosureToStream(stream, level);
return size;
}


//============================
// Con-/Destructors Protected
//============================

HtmlTable::HtmlTable(HtmlNode* parent, Handle<Sentence> caption):
HtmlNode(parent, "table"),
m_Caption(caption)
{
Columns=ColumnList::Create();
SetFlag(HtmlNodeFlags::MultiLine);
}

}}}