//=================================================================================================
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//=================================================================================================

//=================================================================================================
// @file  cmdlineparser.h
// @brief Header file for NATIVECHI3 command line parser
//=================================================================================================

#ifndef __NATIVETEST_CMDPARSER__
#define __NATIVETEST_CMDPARSER__

#include <stdint.h>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "nativetestlog.h"

#define MAX_PATH          260
#ifdef _LINUX
const int NUM_IMAGES = 20;
#else
const int NUM_IMAGES = 5;
#endif

///Buffer timeout (in milliseconds) is obtained by multiplying this by TIMEOUT_RETRIES
///Timeout waiting for buffer on presil
const uint64_t BUFFER_TIMEOUT_PRESIL_MILLI = 10000;   // in milliseconds (10 sec)
///Timeout waiting for buffer on device
const uint64_t BUFFER_TIMEOUT_DEVICE_MILLI = 1000;    // in milliseconds (1 sec)
const uint64_t BUFFER_TIMEOUT_DEVICE_SEC = 1;         // in seconds

//=================================================================================================
// Class Definition
//=================================================================================================
class CmdLineParser
{
    public:

         CmdLineParser() = default;
        ~CmdLineParser() = default;

        /// Do not allow the copy constructor or assignment operator
        CmdLineParser(const CmdLineParser&) = delete;
        CmdLineParser& operator= (const CmdLineParser&) = delete;

        static int  ParseCommandLine(int argc, char** argv);
        static void PrintCommandLineUsage();

        static const char* GetTargetProduct();
        static const char* GetPlatformVersion();

        static int GetLogLevel()
        {
            return m_nLog;
        }
        static bool GenerateReport()
        {
            return m_bReport;
        }
        static int GetFrameCount()
        {
            return m_nFrames;
        }

        static int GetFlushDelay()
        {
            return m_flushDelay;
        }

        static bool DisableFlush()
        {
            return m_disableFlush;
        }

        static bool PrintToConsole()
        {
            return m_bPrint;
        }

        static bool PrintHelp()
        {
            return m_bHelp;
        }
        static int GetCamera()
        {
            return m_nCamera;
        }
        static std::string GetTestSuiteName()
        {
            return m_suiteName;
        }
        static std::string GetTestCaseName()
        {
            return m_caseName;
        }
        static std::string GetTestFullName()
        {
            return m_fullName;
        }

        static bool NoImageDump()
        {
            return m_bNoImageDump;
        }

        static char const* GetInputImage()
        {
            return m_inputImage;
        }

        static uint32_t GetInputWidth()
        {
            return m_inputWidth;
        }

        static uint32_t GetInputHeight()
        {
            return m_inputHeight;
        }

        static int GetInputFormat()
        {
            return m_inputFormat;
        }

        // Defaults to -1 if user did not provide overriding output port
        static int GetInputPort()
        {
            return m_inputPort;
        }

        static uint32_t GetOutputWidth()
        {
            return m_outputWidth;
        }

        static uint32_t GetOutputHeight()
        {
            return m_outputHeight;
        }

        static uint32_t GetRdiOutputWidth()
        {
            return m_rdiOutputWidth;
        }

        static uint32_t GetRdiOutputHeight()
        {
            return m_rdiOutputHeight;
        }

        static int GetOutputFormat()
        {
            return m_outputFormat;
        }

        // Defaults to -1 if user did not provide overriding output port
        static int GetOutputPort()
        {
            return m_outputPort;
        }

        // Returns...
        //   0          disable timeout
        //   otherwise  timeout override in milliseconds
        static int GetTimeoutOverride()
        {
            // if --timeout flag used
            if (m_timeout < static_cast<int>(BUFFER_TIMEOUT_DEVICE_SEC)) // check if not less than 1 second
            {
                m_timeout = static_cast<int>(BUFFER_TIMEOUT_DEVICE_MILLI); //set to 1000 milliseconds (1 sec)
            }
            // return specified --timeout value or default value (1000 milliseconds) if flag not used
            return m_timeout;
        }

        static int GetSensorMode()
        {
            return m_sensorMode;
        }

    private:
        static int   m_nLog;
        static bool  m_bHelp;
        static bool  m_bReport;
        static bool m_bPrint;
        static int   m_nFrames;
        static bool  m_bNoImageDump;
        static int   m_nCamera;
        static int   m_timeout;
        static int   m_sensorMode;
        static int   m_flushDelay;
        static bool  m_disableFlush;

        static std::string m_suiteName;
        static std::string m_caseName;
        static std::string m_fullName;

        // input parameters
        static char const*    m_inputImage;
        static uint32_t       m_inputWidth;
        static uint32_t       m_inputHeight;
        static int            m_inputFormat;
        static int            m_inputPort;

        // output parameters
        static uint32_t m_outputWidth;
        static uint32_t m_outputHeight;
        static uint32_t m_rdiOutputWidth;
        static uint32_t m_rdiOutputHeight;
        static int      m_outputFormat;
        static int      m_outputPort;
};

#endif //__NATIVETEST_CMDPARSER__
