//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _WINDOWS_TIMER_CLASS_H_
#define _WINDOWS_TIMER_CLASS_H_

#include "stdafx.h"
#include "Common.h"
#include "Interfaces\ITimer.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace System
	{
		class TimerClass : public ITimer
		{
		private:
			INT64 m_nFrequency;
			INT64 m_nTickStart;
			float m_fTicksPerMilliseconds;
			float m_fElapsedTimeInMilliseconds;
			bool m_bRun;

		public:
		
			TimerClass();
			TimerClass(const TimerClass&);
			~TimerClass();

			/// <summary>
			/// Starts the timer.
			/// </summary>
			bool Start();
			
			/// <summary>
			/// Pauses the timer so that it can resume with another call to Start.
			/// </summary>
			void Pause();


			/// <summary>
			/// Runs the timer and calculates the frame rate.
			/// This must be called at least once before GetFrameRate().
			/// </summary>
			void Run();

			/// <summary>
			/// Stops and resets the timer.
			/// </summary>
			void Stop();

			/// <summary>
			/// Returns the elasped time in milliseconds.
			/// TimeComplexity: O(1) for all operations.
			/// </summary>
			float GetElaspedTime() { return m_fElapsedTimeInMilliseconds; }
		};
	};
};

#endif