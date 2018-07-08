//--------------------------------------------------------------------------------------
// Description: A logging utility.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _LOGGER_UTILITY_CLASS_H_
#define _LOGGER_UTILITY_CLASS_H_

#pragma once

#include "Common.hpp"
#include "UtilTypes.hpp"
#include "LoggingTypes.hpp"
#include <atomic>

namespace CoffeeEngine
{
	namespace Utility
	{
		namespace Logging
		{
			class Logger
			{
			public:

				////////////////////////////////////////////////////////////
				// Constants
				////////////////////////////////////////////////////////////
				static constexpr char* LOG_FILE_NAME = "CoffeeEngineError.log";
				static constexpr int MAX_FLUSH_COUNT = 16;

			public:

				Logger() = delete;
				Logger(const char *szFilename, LogLevelType verbosityLevel = Verbosity::Normal);
				Logger(const std::string& szFilename, LogLevelType verbosityLevel = Verbosity::Normal)
					: Logger(szFilename.c_str()) {};
				~Logger();

				////////////////////////////////////////////////////////////
				// Properties
				////////////////////////////////////////////////////////////

				/// <summary>
				/// Changes the verbosity of the logger.
				/// </summary>
				inline void SetVerbosity(LogLevelType verbosityLevel) {
					m_verbosityLevel = verbosityLevel;
				}

				/// <summary>
				/// Returns the verbosity of the logger.
				/// </summary>
				inline LogLevelType GetVerbosity() const {
					return m_verbosityLevel;
				}

				/// <summary>
				/// Changes the max flush count of the logger.
				/// </summary>
				inline void SetMaxFlushCount(unsigned int numOfWritesUntilFlush) {
					m_nNumOfWritesUntilFlush = numOfWritesUntilFlush;
				}

				/// <summary>
				/// Returns the max flush count of the logger.
				/// </summary>
				inline int GetMaxFlushCount() const {
					return m_nNumOfWritesUntilFlush;
				}

				/// <summary>
				/// Writes an timestamped event to the error log.
				/// </summary>
				void Write(const char*, LogLevelType = LogLevelType::Informational);
				void Write(const std::string&, LogLevelType = LogLevelType::Informational);
				void Write(Exception&, LogLevelType = LogLevelType::Error);

			private:
				unique_file_ptr m_fpLogFile;
				std::atomic_int m_nFlushCount = 0;
				const char* m_szLogFileName = nullptr;
				int m_nNumOfWritesUntilFlush = Logger::MAX_FLUSH_COUNT;
				LogLevelType m_verbosityLevel = Verbosity::Normal;
				bool m_bDisposed = false;
			};
		};
	};
};

#endif
