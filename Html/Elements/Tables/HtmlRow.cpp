//=============
// HtmlRow.cpp
//=============

#include "pch.h"


//=======
// Using
//=======

#include "HtmlRow.h"
#include "HtmlTable.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//========
// Common
//========

Handle<HtmlCell> HtmlRow::AddCell(HtmlCellType type)
{
return HtmlCell::Create(this, type);
}


//==========================
// Con-/Destructors Private
//==========================

HtmlRow::HtmlRow(HtmlTable* table):
HtmlNode(table, "tr")
{}

}}}