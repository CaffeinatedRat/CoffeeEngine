//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

//Windows specific.
#include "..\Resources\Resource.h"
#include "System\Win32\TimerClass.h"

#include "Global.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

TimerClass::TimerClass()
{
	m_fElapsedTimeInMilliseconds = 0.0f;
	m_fTicksPerMilliseconds = 0.0f;
	m_nFrequency = 0;
	m_nTickStart = 0;

	m_bRun = false;
}

TimerClass::TimerClass(const TimerClass& object)
{
	m_bRun = object.m_bRun;
	m_nFrequency = object.m_nFrequency;
	m_nTickStart = object.m_nTickStart;
	m_fTicksPerMilliseconds = object.m_fTicksPerMilliseconds;
	m_fElapsedTimeInMilliseconds = object.m_fElapsedTimeInMilliseconds;
}

TimerClass::~TimerClass()
{
	Stop();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool TimerClass::Start()
{
	//Get the frequency in counts per second of operating system's high-resolution performance counter.
	//If the operating system does not support a high-resolution performance counter then the count will be zero.
	//Frequency = ticks per second (ticks/timeInSeconds).
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_nFrequency);
	if(m_nFrequency == 0)
		return false;

	//Calculate the number of ticks per second based on the frequency.
	//TicksPerMilliseconds = (ticks/timeInSeconds*1000)
	m_fTicksPerMilliseconds = (float)(m_nFrequency / 1000);

	//Set the initial number of ticks.
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nTickStart);

	return (m_bRun = true);
}

void TimerClass::Pause()
{
	m_bRun = false;
}

void TimerClass::Stop()
{
	//Reset the starting number of ticks.
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nTickStart);
	
	m_bRun = false;
}

void TimerClass::Run()
{
	if(m_bRun)
	{
		INT64 nCurrentNumberOfTicks;

		//Retrieve the current number of ticks.
		QueryPerformanceCounter((LARGE_INTEGER*)&nCurrentNumberOfTicks);

		//Calculate the frame rate based on the timespan between now and the last call.
		// TimeInMilliseconds = (CurrentTickCount - InitialTickCount) / (ticks / timeInSeconds*1000) = (CurrentTickCount - InitialTickCount) * (timeInSeconds*1000 / ticks) = (timeInSeconds * 1000)
		m_fElapsedTimeInMilliseconds = ((float)(nCurrentNumberOfTicks - m_nTickStart) / m_fTicksPerMilliseconds);

		//Reset the initial number of ticks.
		m_nTickStart = nCurrentNumberOfTicks;
	}
}