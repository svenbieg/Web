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


//========
// Common
//========

VOID JavaScript::Add(LPCSTR global)
{
m_Globals.add(global);
}

VOID JavaScript::Add(JavaFunction func)
{
m_Functions.add(func);
}

SIZE_T JavaScript::WriteToStream(OutputStream* stream, WebContext* context)
{
if(!m_Globals&&!m_Functions)
	return 0;
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n<script type=\"text/javascript\">\r\n");
for(auto global: m_Globals)
	{
	size+=writer.Print(global);
	}
for(auto func: m_Functions)
	{
	size+=func(stream, context);
	}
size+=writer.Print("</script>\r\n\r\n");
return size;
}

}