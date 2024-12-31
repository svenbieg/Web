//================
// WebContext.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "WebContext.h"

using namespace Culture;


//===========
// Namespace
//===========

namespace Web {


//==========================
// Con-/Destructors Private
//==========================

WebContext::WebContext(Web::WebSite* web_site):
Language(LanguageCode::None),
Protocol(nullptr),
TimeStamp(0),
m_WebSite(web_site)
{}

}