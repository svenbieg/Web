//===============
// WebButton.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "Html/Elements/HtmlText.h"
#include "Html/HtmlDocument.h"
#include "Web/WebPage.h"
#include "WebButton.h"

using namespace Html::Elements;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//=========
// Scripts
//=========

constexpr CHAR STR_BUTTON_SCRIPT[]=
"\r\n"
"function webButtonClick(id)\r\n"
"{\r\n"
"var request=new XMLHttpRequest();\r\n"
"request.open('NOTIFY', '?id='+id);\r\n"
"request.send();\r\n"
"}\r\n";


//========
// Common
//========

VOID WebButton::OnNotified(Handle<WebContext> context)
{
Clicked(this, context);
}


//==================
// Common Protected
//==================

SIZE_T WebButton::WriteAttributesToStream(OutputStream* stream, WebContext* context)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=WebControl::WriteAttributesToStream(stream, context);
size+=writer.Print(" onclick=\"webButtonClick('");
size+=writer.Print(Id);
size+=writer.Print("')");
if(Script)
	{
	size+=writer.Print("; ");
	size+=writer.Print(Script);
	}
size+=writer.Print("\" type=\"button\"");
return size;
}


//==========================
// Con-/Destructors Private
//==========================

WebButton::WebButton(HtmlNode* parent, Handle<String> id, Handle<Sentence> text):
WebControl(parent, "button", id),
Script(nullptr)
{
if(text)
	HtmlText::Create(this, text);
Document->AddScript(STR_BUTTON_SCRIPT);
}

}}