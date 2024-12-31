//=============
// HtmlTable.h
//=============

#pragma once


//=======
// Using
//=======

#include "Collections/List.h"
#include "Html/Elements/HtmlNode.h"
#include "HtmlCell.h"
#include "HtmlColumn.h"
#include "HtmlRow.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {
		namespace Tables {


//============
// HTML-Table
//============

class HtmlTable: public HtmlNode
{
public:
	// Using
	using ColumnList=Collections::List<Handle<HtmlColumn>>;

	// Con-/Destructors
	static inline Handle<HtmlTable> Create(HtmlNode* Parent, Handle<Sentence> Caption=nullptr)
		{
		return new HtmlTable(Parent, Caption);
		}

	// Common
	VOID AddColumn(LPCSTR Style=nullptr);
	Handle<HtmlRow> AddRow();
	Handle<ColumnList> Columns;
	SIZE_T WriteToStream(OutputStream* Stream, WebContext* Context, UINT Level)override;

protected:
	// Con-/Destructors
	HtmlTable(HtmlNode* Parent, Handle<Sentence> Caption=nullptr);

private:
	// Common
	Handle<Sentence> m_Caption;
};

}}}