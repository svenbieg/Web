//====================
// HttpParameters.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamWriter.h"
#include "HttpParameters.h"

using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Network {
	namespace Http {


//========
// Common
//========

VOID HttpParameters::Set(LPCTSTR params)
{
m_Map.clear();
LPCTSTR str=params;
while(1)
	{
	while(str[0]==' ')
		str++;
	UINT pos=0;
	if(!StringHelper::FindChar(str, '=', &pos))
		break;
	auto key=String::Create(pos, str);
	str+=pos+1;
	if(StringHelper::FindChar(str, '&', &pos))
		{
		auto value=String::Create(pos, str);
		str+=pos+1;
		m_Map.set(key, value);
		continue;
		}
	auto value=String::Create(str);
	m_Map.set(key, value);
	break;
	}
}

VOID HttpParameters::Set(Handle<String> key, Handle<String> value)
{
Map::Set(key, value);
}

SIZE_T HttpParameters::WriteToStream(OutputStream* stream)
{
SIZE_T size=0;
StreamWriter writer(stream);
UINT pos=0;
for(auto it=Begin(); it->HasCurrent(); it->MoveNext())
	{
	if(pos>0)
		size+=writer.PrintChar('&');
	auto key=it->GetKey();
	auto value=it->GetValue();
	size+=writer.Print(key);
	size+=writer.PrintChar('=');
	size+=writer.Print(value);
	pos++;
	}
return size;
}

}}