//--------------------------------------------------------------------------------------
// Description: The operating system listener interface.
// Used to provide a light-weight skeleton of a set of methods that a listener is prepared to handle.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _ISYSTEMLISTENER_INTERFACE_H_
#define _ISYSTEMLISTENER_INTERFACE_H_

#pragma once

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ISystemListener
		{
		public:

			ISystemListener() = default;
			//NOTE: Very important, otherwise if we don't add a virtual destructor all of our inherited classes will never have their destructor invoked.
			virtual ~ISystemListener() = default;

			/// <summary>
			/// This event is usually triggered when the OS's message loop is idling and no events are occuring.
			/// </summary>
			virtual void OnIdle(bool) = 0;
		};
	};
};

#endif