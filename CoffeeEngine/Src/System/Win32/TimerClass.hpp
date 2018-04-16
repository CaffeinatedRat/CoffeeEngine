//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#ifndef _WINDOWS_TIMER_CLASS_H_
#define _WINDOWS_TIMER_CLASS_H_

#pragma once

#include "stdafx.h"
#include "Common.hpp"
#include "System/ITimer.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace System
	{
		class TimerClass : public ITimer
		{
		private:
			INT64 m_nFrequency = 0;
			INT64 m_nTickStart = 0;
			float m_fTicksPerMilliseconds = 0.0f;
			float m_fElapsedTimeInMilliseconds = 0.0f;
			bool m_bRun = false;

		public:
		
			TimerClass() = default;
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
			inline float GetElaspedTime() const { return m_fElapsedTimeInMilliseconds; }
		};
	};
};

#endif

#endif
