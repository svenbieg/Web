//==========
// WebLog.h
//==========

#pragma once


//=======
// Using
//=======

#include "Resources/Strings/String.h"


//===========
// Namespace
//===========

namespace Resources {
	namespace Strings {


//=========
// Web-Log
//=========

constexpr STRING STR_WEB_LOG_CLEAR[]=
	{
	{ LNG::DE, L"Löschen" },
	{ LNG::EN, L"Clear" },
	{ LNG::None, nullptr }
	};

constexpr STRING STR_WEB_LOG_CLEARED[]=
	{
	{ LNG::DE, L"Protokoll zurückgesetzt" },
	{ LNG::EN, L"Protocol reset" },
	{ LNG::None, nullptr }
	};

}}