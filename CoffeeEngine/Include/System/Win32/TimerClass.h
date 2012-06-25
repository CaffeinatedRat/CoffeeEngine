//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
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
			float m_fTicksPerSecond;
			INT64 m_nStartTime;
			float m_fFrameRate;
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
			/// Stops and resets the timer.
			/// </summary>
			void Stop();

			/// <summary>
			/// Runs the timer and calculates the frame rate.
			/// This must be called at least once before GetFrameRate().
			/// </summary>
			void Run();

			/// <summary>
			/// Returns the current frame time.
			/// </summary>
			float GetFrameRate() { return m_fFrameRate; }
		};
	};
};

#endif