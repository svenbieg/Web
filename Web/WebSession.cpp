//================
// WebSession.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include "WebSession.h"


//===========
// Namespace
//===========

namespace Web {


//==========================
// Con-/Destructors Private
//==========================

WebSession::WebSession(Handle<String> id):
Id(id),
TimeOut(0)
{}

}