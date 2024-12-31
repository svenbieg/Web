//==============
// HtmlCell.cpp
//==============

#include "pch.h"


//=======
// Using
//=======

#include "HtmlCell.h"
#include "HtmlRow.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//=======
// Types
//=======

constexpr LPCSTR STR_TYPES[]={ "td", "th" };


//==========================
// Con-/Destructors Private
//==========================

HtmlCell::HtmlCell(HtmlRow* row, HtmlCellType type):
HtmlNode(row, STR_TYPES[(UINT)type])
{}

}}}