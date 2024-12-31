//=============
// WebGrid.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "Html/HtmlDocument.h"
#include "WebGrid.h"

using namespace Html::Elements::Tables;


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//========
// Common
//========

Handle<WebButton> WebGrid::AddButton(Handle<String> id, Handle<Sentence> text)
{
Document->AddStyle("table.grid button", "margin-right:8px; margin-top:8px;");
if(Elements->GetCount()==0)
	HtmlRow::Create(this);
auto row=Elements->GetAt(0).As<HtmlRow>();
auto cell=HtmlCell::Create(row);
return WebButton::Create(cell, id, text);
}


//==========================
// Con-/Destructors Private
//==========================

WebGrid::WebGrid(HtmlNode* parent):
HtmlTable(parent)
{
Document->AddStyle("table.grid", "border:0; border-collapse:collapse;");
Document->AddStyle("table.grid td", "padding:0;");
Class="grid";
}

}}