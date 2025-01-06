//==============
// HtmlNode.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HtmlNode.h"
#include "HtmlText.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//========
// Common
//========

VOID HtmlNode::Add(Handle<Sentence> element)
{
HtmlText::Create(this, element);
}

VOID HtmlNode::SetFlag(HtmlNodeFlags flag, BOOL set)
{
FlagHelper::Set(m_Flags, flag, set);
}

SIZE_T HtmlNode::WriteToStream(OutputStream* stream, WebContext* context, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=WriteTagToStream(stream, level);
size+=WriteAttributesToStream(stream, context);
size+=writer.Print(">");
size+=WriteElementsToStream(stream, context, level+1);
size+=WriteClosureToStream(stream, level);
return size;
}


//============================
// Con-/Destructors Protected
//============================

HtmlNode::HtmlNode(HtmlDocument* doc, HtmlNode* parent, LPCSTR tag, Handle<String> id):
HtmlElement(doc, parent),
Class(nullptr),
Id(id),
Style(nullptr),
m_Breaks(0),
m_Flags(HtmlNodeFlags::None),
m_Tag(tag)
{
Attributes=AttributeMap::Create();
Elements=ElementList::Create();
}


//==================
// Common Protected
//==================

SIZE_T HtmlNode::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
SIZE_T size=0;
StreamWriter writer(stream);
if(Id)
	{
	size+=writer.Print(" id=\"");
	size+=writer.Print(Id);
	size+=writer.Print("\"");
	}
if(Class)
	{
	size+=writer.Print(" class=\"");
	size+=writer.Print(Class);
	size+=writer.Print("\"");
	}
if(Style)
	{
	size+=writer.Print(" style=\"");
	size+=writer.Print(Style);
	size+=writer.Print("\"");
	}
for(auto it=Attributes->Begin(); it->HasCurrent(); it->MoveNext())
	{
	size+=writer.Print(" ");
	size+=writer.Print(it->GetKey());
	size+=writer.Print("=\"");
	size+=writer.Print(it->GetValue());
	size+=writer.Print("\"");
	}
return size;
}

SIZE_T HtmlNode::WriteClosureToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
if(FlagHelper::Get(m_Flags, HtmlNodeFlags::MultiLine))
	{
	writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	}
size+=writer.Print("</");
size+=writer.Print(m_Tag);
size+=writer.Print(">");
if(m_Breaks>0)
	{
	size+=writer.Print("\r\n");
	size+=writer.PrintChar(' ', level*2);
	for(UINT u=0; u<m_Breaks; u++)
		size+=writer.Print("<br />");
	}
return size;
}

SIZE_T HtmlNode::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
SIZE_T size=0;
for(auto it=Elements->Begin(); it->HasCurrent(); it->MoveNext())
	{
	auto element=it->GetCurrent();
	size+=element->WriteToStream(stream, context, level);
	}
return size;
}

SIZE_T HtmlNode::WriteTagToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar(' ', level*2);
size+=writer.PrintChar('<');
size+=writer.Print(m_Tag);
return size;
}

}}