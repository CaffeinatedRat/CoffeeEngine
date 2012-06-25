//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
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

}

TimerClass::TimerClass(const TimerClass& object)
{
	m_bRun = object.m_bRun;
	m_nFrequency = object.m_nFrequency;
	m_fTicksPerSecond = object.m_fTicksPerSecond;
	m_nStartTime = object.m_nStartTime;
	m_fFrameRate = object.m_fFrameRate;
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
	//Get the frequency of operating system's high-resolution performance counter.
	//If the operating system does not support a high-resolution performance counter then zero is returned.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_nFrequency);
	if(m_nFrequency == 0)
		return false;

	//Calculate the number of ticks per second based on the frequency.
	m_fTicksPerSecond = (float)(m_nFrequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_nStartTime);

	return (m_bRun = true);
}

void TimerClass::Pause()
{
	m_bRun = false;
}

void TimerClass::Stop()
{
	//Reset the timer.
	QueryPerformanceCounter((LARGE_INTEGER*)&m_nStartTime);
	
	m_bRun = false;
}

void TimerClass::Run()
{
	if(m_bRun)
	{
		INT64 nCurrentTime;

		QueryPerformanceCounter((LARGE_INTEGER*)&nCurrentTime);

		//Calculate the frame rate based on the timespan between now and the last call.
		m_fFrameRate = ((float)(nCurrentTime - m_nStartTime) / m_fTicksPerSecond);

		//Update the time.
		m_nStartTime = nCurrentTime;
	}
}