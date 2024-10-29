//================
// JavaScript.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "Storage/Streams/StreamWriter.h"
#include "Web/WebContext.h"
#include "JavaScript.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Java {


//==================
// Con-/Destructors
//==================

JavaScript::JavaScript()
{}


//========
// Common
//========

VOID JavaScript::Add(LPCSTR global)
{
if(!m_Globals)
	m_Globals=new GlobalsList();
m_Globals->Add(global);
}

VOID JavaScript::Add(JavaFunction func)
{
if(!m_Functions)
	m_Functions=new JavaFunctionList();
m_Functions->Add(func);
}

SIZE_T JavaScript::WriteToStream(OutputStream* stream, WebContext* context)
{
if(!m_Globals&&!m_Functions)
	return 0;
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n<script type=\"text/javascript\">\r\n");
for(auto it=m_Globals->First(); it->HasCurrent(); it->MoveNext())
	{
	auto global=it->GetCurrent();
	size+=writer.Print(global);
	}
for(auto it=m_Functions->First(); it->HasCurrent(); it->MoveNext())
	{
	auto func=it->GetCurrent();
	size+=func(stream, context);
	}
size+=writer.Print("</script>\r\n\r\n");
return size;
}

}
