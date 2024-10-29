//==============
// WebLabel.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "Web/WebPage.h"
#include "WebLabel.h"

using namespace Culture;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==================
// Con-/Destructors
//==================

WebLabel::WebLabel(HtmlNode* parent, Handle<Variable> var, Handle<String> id):
WebVariable(parent, "label", id? id: var->Name),
m_Variable(var),
m_TimeChanged(0)
{
m_Variable->Changed.Add(this, &WebLabel::OnVariableChanged);
}

WebLabel::~WebLabel()
{
m_Variable->Changed.Remove(this);
}


//========
// Common
//========

SIZE_T WebLabel::UpdateToStream(OutputStream* stream, WebContext* context)
{
if(context->TimeStamp>m_TimeChanged)
	return 0;
auto lng=context->Language;
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print(Id);
size+=writer.Print("=");
size+=writer.Print(m_Variable->ToString(lng));
size+=writer.Print(";");
return size;
}


//==================
// Common Protected
//==================

SIZE_T WebLabel::WriteElementsToStream(OutputStream* stream, WebContext* context, UINT level)
{
auto lng=context->Language;
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print(m_Variable->ToString(lng));
size+=WebVariable::WriteElementsToStream(stream, context, level);
return size;
}


//================
// Common Private
//================

VOID WebLabel::OnVariableChanged()
{
m_TimeChanged=GetTickCount64();
Page->Changed(Page);
}

}}