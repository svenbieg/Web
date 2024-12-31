//===========
// HtmlRow.h
//===========

#pragma once


//=======
// Using
//=======

#include "Html/Elements/HtmlNode.h"
#include "HtmlCell.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//======================
// Forward-Declarations
//======================

class HtmlTable;


//==========
// HTML-Row
//==========

class HtmlRow: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlRow> Create(HtmlTable* Table)
		{
		return new HtmlRow(Table);
		}

	// Common
	Handle<HtmlCell> AddCell(HtmlCellType Type=HtmlCellType::Default);

private:
	// Con-/Destructors
	HtmlRow(HtmlTable* Table);
};

}}}