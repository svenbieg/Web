//=============
// HtmlImage.h
//=============

#pragma once


//=======
// Using
//=======

#include "HtmlNode.h"


//===========
// Namespace
//===========

namespace Html {
	namespace Elements {


//============
// HTML-Image
//============

class HtmlImage: public HtmlNode
{
public:
	// Con-/Destructors
	static inline Handle<HtmlImage> Create(HtmlNode* Parent, Handle<Sentence> Url)
		{
		return new HtmlImage(Parent, Url);
		}

protected:
	// Common
	SIZE_T WriteAttributesToStream(OutputStream* Stream, WebContext* Context)override;

private:
	// Con-/Destructors
	HtmlImage(HtmlNode* Parent, Handle<Sentence> Url);

	// Common
	Handle<Sentence> m_Url;
};

}}