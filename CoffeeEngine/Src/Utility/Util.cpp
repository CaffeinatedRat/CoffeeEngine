//--------------------------------------------------------------------------------------
// Description: Provides a common set of helper functions.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

//Disable the security warnings created by Windows, so that we can increase portability.
#define _CRT_SECURE_NO_WARNINGS

#include "UtilTypes.hpp"

using namespace CoffeeEngine::Utility;

unique_file_ptr CoffeeEngine::Utility::make_file_ptr(const char* szFileName, const char* flags) {
	return unique_file_ptr(std::fopen(szFileName, flags));
}