//--------------------------------------------------------------------------------------
// Description: A logging utility.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

//Disable the security warnings created by Windows, so that we can increase portability.
#define _CRT_SECURE_NO_WARNINGS

//Windows specific.
#include "Common.hpp"
#include "Logger.hpp"
#include <time.h>
#include <atomic>
#include <cassert>

using namespace CoffeeEngine::Utility::Logging;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

Logger::Logger(const char* szFilename, LogLevelType verbosityLevel)
{
	assert(szFilename);
	m_szLogFileName = szFilename == nullptr ? Logger::LOG_FILE_NAME : szFilename;
	m_verbosityLevel = verbosityLevel;
}

Logger::~Logger()
{
	if (m_fpLogFile)
		m_fpLogFile.reset(nullptr);

	m_bDisposed = true;
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

/// <summary>
/// Writes an event to the event log based on the event type.
/// </summary>
/// <param name="sEvent">Event to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void Logger::Write(const char* szEvent, LogLevelType logEventType)
{
	try
	{
		//Determine if this event should be written.
		//Perform a bitwise operation to determine if the verbosity level contains the acceptable logEventTypes
		if (m_bDisposed || ((m_verbosityLevel & logEventType) != logEventType))
			return;

		if (!m_fpLogFile)
			m_fpLogFile = make_file_ptr(m_szLogFileName, "a");

		assert(m_fpLogFile);

		//Append to the error log.
		if (m_fpLogFile)
		{
			auto fileHandle = m_fpLogFile.get();
			assert(fileHandle);
			if (fileHandle != nullptr) {

				//Get the current time.
				//NOTE: No-throw guarantee
				char timeBuffer[20];
				time_t timeInSeconds = time(nullptr);
				strftime(timeBuffer, std::size(timeBuffer), "%m/%d/%Y %H:%M:%S", localtime(&timeInSeconds));

				//noexcept
				m_nFlushCount.fetch_add(1, std::memory_order::memory_order_relaxed);

				//noexcept
				int flushCount = m_nFlushCount.load();
				if (flushCount > 0 && flushCount % m_nNumOfWritesUntilFlush == 0) {
					std::fflush(fileHandle);
				}

				//Write the timestamped event.
				fprintf_s(fileHandle, "<%s> %s -- %s \n", GetLogLevelName(logEventType), timeBuffer, szEvent);
			}
		}
	}
	catch (...) {}
}

/// <summary>
/// Writes an event to the event log based on the event type.
/// </summary>
/// <param name="sEvent">Event to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void Logger::Write(const std::string& sEvent, LogLevelType logEventType)
{
	Write(sEvent.c_str());
}

/// <summary>
/// Writes an exception to the event log based on the event type.
/// </summary>
/// <param name="sEvent">Event to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void Logger::Write(Exception& exception, LogLevelType logEventType)
{
	Write(exception.ToString(), logEventType);
}