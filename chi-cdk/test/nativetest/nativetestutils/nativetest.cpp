////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  nativetest.cpp
/// @brief Implementation of the test framework.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <list>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdexcept>
#include <cstdarg>
#include <regex>
#include "nativetest.h"

namespace tests {
    // Initialize static members
    NativeTest* NativeTest::m_pTestObj;

    // Constants
    static const size_t cStringSize = 1024;

    // Forward Declarations
    VOID ShutDown();
    bool ComparePriorities(NativeTest *first, NativeTest *second);
    VOID ReportResults(NativeTest *funcObj);
    VOID ReportAllResults(int totalPassed, int totalFailed);
    VOID RunTest(NativeTest *funcObj, int *totalPassedOut, int *totalFailedOut, bool *passedOut);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Test framework related class/structure implementations
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef struct NativeTestContainer
    {
    public:
        NativeTestContainer()
            : m_pTestListInitialize(NULL)
            , m_pTestListShutDown(NULL)
        {
            (VOID)m_TestListDefault.empty();
            (VOID)m_TestListOrder.empty();
        }

        ~NativeTestContainer()
        {
            m_pTestListInitialize = NULL;
            m_pTestListShutDown = NULL;
            (VOID)m_TestListDefault.empty();
            (VOID)m_TestListOrder.empty();
        }

        std::list<NativeTest *> m_TestListDefault;
        std::list<NativeTest *> m_TestListOrder;

        NativeTest *m_pTestListInitialize;
        NativeTest *m_pTestListShutDown;

    }    NativeTestContainer;

    // Globals
    static NativeTestContainer *g_testFuncContainer = NULL;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Test helper functions
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID signalHandler(int signum)
    {
        static char szException[cStringSize];
        //NT_LOG_ERROR();
        (VOID)snprintf(szException,
            cStringSize,
            "Signal: %d", signum);
        throw new std::runtime_error(szException);
    }

    bool Check(NativeTest *funcObj, bool passed, const char *fileName, int lineNumber, const char* condition,
        const char* errorFmt, ...)
    {
        // Get error format and args
        va_list errorArgs;
        va_start(errorArgs, errorFmt);
        char errOutput[cStringSize] = "\0";
        (VOID)vsnprintf(errOutput, cStringSize, errorFmt, errorArgs);
        va_end(errorArgs);

        if (!funcObj)
        {
            NT_LOG_ERROR("NativeTest aborted: Invalid Class Object: %p", funcObj);
            //return false;
            exit(-1);
        }
        else
        {
            if (!passed)
            {
                funcObj->SetFailed();
                NT_LOG_ERROR("CONDITION FAILED! %s:%d \"%s: %s\"\n    %s\n",
                    fileName, lineNumber, funcObj->GetTestFullName(), condition, errOutput)
            }
        }

        return (passed);
    }

    bool ComparePriorities(NativeTest *first, NativeTest *second)
    {
        if (first->GetOrder() < second->GetOrder())
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }

    VOID RegisterFunction(NativeTest *funcObj)
    {
        if (g_testFuncContainer == 0)
        {
            g_testFuncContainer = new NativeTestContainer();
        }

        if (funcObj->GetOrder() == cNativeTestOrderDefault)
        {
            g_testFuncContainer->m_TestListDefault.push_back(funcObj);
        }
        else if ((funcObj->GetOrder() >= cNativeTestOrderLowest) && (funcObj->GetOrder() <= cNativeTestOrderHighest))
        {
            g_testFuncContainer->m_TestListOrder.push_back(funcObj);
            g_testFuncContainer->m_TestListOrder.sort(ComparePriorities);
        }
        else if (funcObj->GetOrder() == cNativeTestOrderInitialize)
        {
            g_testFuncContainer->m_pTestListInitialize = funcObj;

        }
        else if (funcObj->GetOrder() == cNativeTestOrderShutDown)
        {
            g_testFuncContainer->m_pTestListShutDown = funcObj;
        }
        else
        {
            NT_LOG_ERROR("NativeTest aborted: \"%s\" was assigned to an invalid order number = %d\n",
                funcObj->GetTestFullName(), funcObj->GetOrder());
            exit(-1);
        }
    }

    VOID ReportResults(NativeTest *funcObj)
    {
        char szOutput[cStringSize];
        int failed = funcObj->GetFailed();
        NT_LOG_STD("\"%s\" report -> %s\n",
            funcObj->GetTestFullName(),
            (failed == 0) ? "[PASSED]" : "[FAILED]");
    }

    VOID ReportAllResults(int totalPassed, int totalFailed)
    {
        NT_LOG_STD("Final Report -> [%d PASSED] and [%d FAILED]\n",
            totalPassed, totalFailed);
    }

    VOID RunTest(NativeTest *funcObj, int *totalPassedOut, int *totalFailedOut, bool *passedOut)
    {
        if (funcObj)
        {
            /*try
            {*/
            funcObj->Setup();
            // Only run if setup has not failed
            if (funcObj->GetFailed() == 0)
            {
                funcObj->SetTestObject(funcObj);
                funcObj->Run();
            }
            funcObj->Teardown();

            ReportResults(funcObj);
            *totalPassedOut += funcObj->GetPassed();
            *totalFailedOut += funcObj->GetFailed();

            if (funcObj->GetFailed() != 0)
            {
                *passedOut = false;
            }
        }
    }

    int RunTests()
    {
        bool passed = true;
        int totalPassed = 0;
        int totalFailed = 0;
        int totalRegistered = 0;
        int registeredTests = 0;
        int matchingTestCaseCount = 0;

        // pCurrent test either holds exact match or keeps tracks of partial matches
        NativeTest* pCurrentTest = nullptr;
        char szOutput[cStringSize];

        std::list<NativeTest *>::iterator i;
        std::list<NativeTest *>::iterator end;
        NativeTest* pTest = nullptr;

        // Flush stdout and stderr by default
        setbuf(stdout, NULL);

        // Get test to run from user
        std::string testSuiteName = CmdLineParser::GetTestSuiteName();
        std::string testCaseName = CmdLineParser::GetTestCaseName();
        std::string testFullName = CmdLineParser::GetTestFullName();

        // Treat wildcard input (*) as empty string
        if (testSuiteName == "*") testSuiteName = "";
        if (testCaseName == "*") testCaseName = "";

        // Register signal handlers to trap test case crashes
        signal(SIGSEGV, signalHandler);
        signal(SIGFPE, signalHandler);
        signal(SIGILL, signalHandler);

        // Run initialize
        RunTest(g_testFuncContainer->m_pTestListInitialize, &totalPassed, &totalFailed, &passed);

        // Unordered / Default tests
        end = g_testFuncContainer->m_TestListDefault.end();
        for (i = g_testFuncContainer->m_TestListDefault.begin();
            i != end;
            ++i)
        {
            totalRegistered++;
            pTest = reinterpret_cast<NativeTest *>(*i);
            std::string regTestSuiteName(pTest->GetTestSuiteName());
            std::string regTestCaseName(pTest->GetTestCaseName());

            if (nullptr == pCurrentTest) //iterate over other tests only for partial match
            {
                if (0 == testSuiteName.compare(regTestSuiteName) || testSuiteName == "")
                {
                    // check if testcase is exact match
                    if (testCaseName == regTestCaseName)
                    {
                        // assign match test object
                        pCurrentTest = pTest;
                        NTLog.SetTestName(testSuiteName.c_str(), testCaseName.c_str());
                        NT_LOG_STD("Now Running with exact match : %s ", testFullName.c_str());
                        RunTest(pCurrentTest, &totalPassed, &totalFailed, &passed);
                        matchingTestCaseCount = 0;
                        break;
                    }
                    // otherwise check for partial match
                    else
                    {
                        std::string searchCase = testCaseName + "(.*)";
                        std::regex searchCaseObj(searchCase);
                        if (regex_match(regTestCaseName, searchCaseObj) || testCaseName == "")
                        {
                            matchingTestCaseCount++;
                        }
                    }
                }
            }
        }

        if ((nullptr == pCurrentTest) && (0 != matchingTestCaseCount))
        {
            NT_LOG_STD("Running %d of %d Tests: %s ", matchingTestCaseCount, g_testFuncContainer->m_TestListDefault.size(),
                testCaseName.c_str());
            // Run Unordered / Default list
            //iterate over other tests only for partial match
            for (i = g_testFuncContainer->m_TestListDefault.begin();
                i != end;
                ++i)
            {
                pTest = reinterpret_cast<NativeTest*>(*i);
                std::string regTestSuiteName(pTest->GetTestSuiteName());
                std::string regTestCaseName(pTest->GetTestCaseName());
                std::string regTestFullName(pTest->GetTestFullName());
                if (0 == testSuiteName.compare(regTestSuiteName) || testSuiteName == "")
                {
                    std::string searchCase = testCaseName + "(.*)";
                    std::regex searchCaseObj(searchCase);
                    if (regex_match(regTestCaseName, searchCaseObj) || testCaseName == "")
                    {
                        pCurrentTest = pTest;
                        NT_LOG_STD("Now Running a partially matched test : %s ", regTestFullName.c_str());
                        NTLog.SetTestName(regTestSuiteName.c_str(), regTestCaseName.c_str());
                        RunTest(pTest, &totalPassed, &totalFailed, &passed);
                    }
                }

                if ((i == end) && (nullptr == pCurrentTest))
                {
                    NT_LOG_ERROR("No tests match the input. Aborting.");
                    break;
                }
            }
        }

        // Run shutdown
        RunTest(g_testFuncContainer->m_pTestListShutDown, &totalPassed, &totalFailed, &passed);

        ShutDown();

        // Report
        ReportAllResults(totalPassed, totalFailed);

        if (passed)
        {
            return (0);
        }
        else
        {
            return (1);
        }
    }

    VOID ShutDown()
    {
        if (g_testFuncContainer)
        {
            delete g_testFuncContainer;
            g_testFuncContainer = NULL;
        }
    }
}
