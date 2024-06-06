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
	{ LNG::DE, "L�schen" },
	{ LNG::EN, "Clear" },
	{ LNG::None, nullptr }
	};

constexpr STRING STR_WEB_LOG_CLEARED[]=
	{
	{ LNG::DE, "Protokoll zur�ckgesetzt" },
	{ LNG::EN, "Protocol reset" },
	{ LNG::None, nullptr }
	};

}}