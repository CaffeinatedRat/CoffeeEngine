//--------------------------------------------------------------------------------------
// Description: A logging utility.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

//
#define _CRT_SECURE_NO_WARNINGS

//Windows specific.
#include "Utility\Logger.h"
#include <cstdio>
#include <time.h>

using namespace CoffeeEngine::Utility;

const char* CoffeeEngine::Utility::Logger::LOG_FILE_NAME = "CoffeeEngineError.log";

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
Logger::Logger()
{
}

Logger::~Logger()
{
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

void Logger::Write(std::string sEvent)
{
	FILE* pFile = NULL;
	try
	{
		//Append to the error log.
		if ( (pFile = fopen(LOG_FILE_NAME, "a")) != NULL)
		{
			//Get the current time.
			char timeBuffer[20];
			time_t timeInSeconds = time(NULL);
			strftime(timeBuffer, 20, "%m/%d/%Y %H:%M:%S", localtime(&timeInSeconds));
			
			//Write the timestamped event.
			fprintf(pFile, "%s -- %s\n", timeBuffer, sEvent.c_str());
		}
	}
	catch(...) {}
	
	//Make sure the file handle is released regardless of a successful write.
	fclose(pFile);
}