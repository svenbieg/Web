//===========
// WebGrid.h
//===========

#pragma once


//=======
// Using
//=======

#include "Html/Elements/Tables/HtmlTable.h"
#include "WebButton.h"


//===========
// Namespace
//===========

namespace Web {
	namespace Elements {


//==========
// Web-Grid
//==========

class WebGrid: public Html::Elements::Tables::HtmlTable
{
public:
	// Con-/Destructors
	static inline Handle<WebGrid> Create(HtmlNode* Parent) { return new WebGrid(Parent); }

	// Common
	Handle<WebButton> AddButton(Handle<String> Id, Handle<Sentence> Text);

private:
	// Con-/Destructors
	WebGrid(HtmlNode* Parent);
};

}}