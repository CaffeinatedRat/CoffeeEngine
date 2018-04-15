//--------------------------------------------------------------------------------------
// Description: Provides a common set of utility typedefs and static methods.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _UTIL_TYPES_H_
#define _UTIL_TYPES_H_

#pragma once

//STD libraries.
#include <memory>

namespace CoffeeEngine
{
	namespace Utility
	{
		//Our custom file deleter that simply closes the file stream.
		//We had to construct this as apparently according to the C++ standards, we cannot construct a unique pointer as long as the template argument for the deleter is a pointer or reference type.
		//A good reference article on the issue: https://dev.krzaq.cc/post/you-dont-need-a-stateful-deleter-in-your-unique_ptr-usually/
		struct unique_file_deleter
		{
			void operator()(FILE* ptr) const {
				std::fclose(ptr);
			}
		};

		typedef std::unique_ptr<std::FILE, unique_file_deleter> unique_file_ptr;
		unique_file_ptr make_file_ptr(const char* szFileName, const char* flags);
	};
};

#endif
