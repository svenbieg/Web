//============
// HtmlCell.h
//============

#pragma once


//=======
// Using
//=======

#include "Html/Elements/HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//======================
// Forward-Declarations
//======================

class HtmlRow;


//======
// Type
//======

enum class HtmlCellType
{
Default,
Header
};


//===========
// HTML-Cell
//===========

class HtmlCell: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlCell> Create(HtmlRow* Row, HtmlCellType Type=HtmlCellType::Default)
		{
		return new HtmlCell(Row, Type);
		}

private:
	// Con-/Destructors
	HtmlCell(HtmlRow* Row, HtmlCellType Type);
};

}}}