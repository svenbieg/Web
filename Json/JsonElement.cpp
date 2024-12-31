//=================
// JsonElement.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Storage/Streams/StreamReader.h"
#include "Storage/Streams/StreamWriter.h"
#include "Storage/Buffer.h"
#include "JsonElement.h"

using namespace Storage;
using namespace Storage::Streams;


//===========
// Namespace
//===========

namespace Json {


//========
// Common
//========

Handle<JsonElement> JsonElement::FromStream(InputStream* stream)
{
auto json=JsonElement::Create();
json->ReadFromStream(stream);
return json;
}

Handle<JsonElement> JsonElement::FromString(Handle<String> str)
{
if(!str)
	return nullptr;
auto buf=Buffer::Create(str->Begin(), 0, BufferOptions::Static);
return FromStream(buf);
}

Handle<JsonList> JsonElement::GetList(Handle<String> key)
{
auto list=Elements->Get(key);
return list.As<JsonList>();
}

Handle<String> JsonElement::GetString(Handle<String> key)
{
auto str=Elements->Get(key);
return str.As<String>();
}

SIZE_T JsonElement::ReadFromStream(InputStream* stream)
{
SIZE_T size=0;
StreamReader reader(stream);
while(1)
	{
	size+=reader.FindChar("\"}");
	if(reader.LastChar=='}')
		break;
	Handle<String> key=reader.ReadString(&size, "\"");
	size+=reader.FindChar("\"[-.0123456789nft}");
	if(reader.LastChar=='\"')
		{
		Handle<String> value=reader.ReadString(&size, "\"");
		Elements->Set(key, value);
		continue;
		}
	if(reader.LastChar=='[')
		{
		auto list=JsonList::Create();
		while(1)
			{
			size+=reader.FindChar("\"{]");
			if(reader.LastChar=='\"')
				{
				Handle<String> value=reader.ReadString(&size, "\"");
				list->Append(value);
				continue;
				}
			if(reader.LastChar=='{')
				{
				Handle<JsonElement> json=new JsonElement();
				size+=json->ReadFromStream(stream);
				list->Append(json);
				continue;
				}
			if(reader.LastChar==']')
				break;
			}
		Elements->Set(key, list);
		continue;
		}
	if(reader.LastChar=='}')
		break;
	TCHAR str[32];
	str[0]=reader.LastChar;
	UINT len=reader.ReadString(&str[1], 31, " ,\r\n}");
	size+=len;
	str[len+1]=0;
	auto value=String::Create(str);
	Elements->Set(key, value);
	if(reader.LastChar=='}')
		break;
	}
return size;
}

SIZE_T JsonElement::WriteToStream(OutputStream* stream, UINT level)
{
SIZE_T size=0;
StreamWriter writer(stream);
size+=writer.Print("\r\n");
size+=writer.PrintChar('\t', level);
size+=writer.Print("{");
UINT pos=0;
for(auto it=Elements->First(); it->HasCurrent(); it->MoveNext())
	{
	if(pos++>0)
		size+=writer.Print(",");
	size+=writer.Print("\r\n");
	size+=writer.PrintChar('\t', level);
	auto key=it->GetKey();
	size+=writer.Print("\"");
	size+=writer.Print(key);
	size+=writer.Print("\": ");
	auto value=it->GetValue();
	auto str=value.As<String>();
	if(str)
		{
		size+=writer.Print("\"");
		size+=writer.Print(str);
		size+=writer.Print("\"");
		continue;
		}
	auto list=value.As<JsonList>();
	if(list)
		{
		UINT list_pos=0;
		size+=writer.Print("[");
		for(auto it_list=list->First(); it->HasCurrent(); it->MoveNext())
			{
			auto list_item=it_list->GetCurrent();
			auto list_str=list_item.As<String>();
			if(list_str)
				{
				if(list_pos>0)
					size+=writer.Print(", ");
				size+=writer.Print("\"");
				size+=writer.Print(list_str);
				size+=writer.Print("\"");
				continue;
				}
			auto list_json=list_item.As<JsonElement>();
			if(list_json)
				{
				if(list_pos>0)
					size+=writer.Print(",");
				size+=list_json->WriteToStream(stream, level+1);
				continue;
				}
			}
		}
	}
size+=writer.Print("\r\n");
size+=writer.PrintChar('\t', level);
size+=writer.Print("}");
return size;
}


//==========================
// Con-/Destructors Private
//==========================

JsonElement::JsonElement()
{
Elements=ElementMap::Create();
}

}