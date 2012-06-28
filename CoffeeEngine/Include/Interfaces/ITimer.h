//--------------------------------------------------------------------------------------
// Description: The system timer.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ITIMER_INTERFACE_H_
#define _ITIMER_INTERFACE_H_

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ITimer
		{
		public:
		
			/// <summary>
			/// Starts the timer.
			/// </summary>
			virtual bool Start() = 0;
			
			/// <summary>
			/// Pauses the timer so that it can resume with another call to Start.
			/// </summary>
			virtual void Pause() = 0;

			/// <summary>
			/// Runs the timer and calculates the frame rate.
			/// This must be called at least once before GetFrameRate().
			/// </summary>
			virtual void Run() = 0;

			/// <summary>
			/// Stops and resets the timer.
			/// </summary>
			virtual void Stop() = 0;

			/// <summary>
			/// Returns the elasped time in milliseconds.
			/// TimeComplexity: O(1) for all operations.
			/// </summary>
			virtual float GetElaspedTime() = 0;
		};
	};
};

#endif