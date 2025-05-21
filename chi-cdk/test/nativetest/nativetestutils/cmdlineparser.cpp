//=================================================================================================
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//=================================================================================================

//=================================================================================================
// @file  cmdlineparser.cpp
// @brief Source file for nativetest command line parser
//=================================================================================================

#include <iostream>
#include <string>
#include "cmdlineparser.h"

// static Definitions
int  CmdLineParser::m_nLog = 1;
bool CmdLineParser::m_bHelp = false;
bool CmdLineParser::m_bReport = false;
bool CmdLineParser::m_bPrint = false;
int  CmdLineParser::m_nFrames = NUM_IMAGES;
bool CmdLineParser::m_bNoImageDump = false;
int  CmdLineParser::m_nCamera = -1;   // -1 means --camera flag not set; select all cameras for testing
int  CmdLineParser::m_sensorMode = -1; // -1 means --sensormode flag not set; pick the best matching
bool CmdLineParser::m_disableFlush = false;
int  CmdLineParser::m_flushDelay = -1;

///Buffer timeout (in milliseconds) is obtained by multiplying this by TIMEOUT_RETRIES
#ifdef _LINUX
int  CmdLineParser::m_timeout = BUFFER_TIMEOUT_DEVICE_MILLI; // default is 1 second
#else
int  CmdLineParser::m_timeout = BUFFER_TIMEOUT_PRESIL_MILLI;
#endif // _LINUX

// test name parameters
std::string CmdLineParser::m_suiteName    = "";
std::string CmdLineParser::m_caseName     = "";
std::string CmdLineParser::m_fullName     = "";
// input parameters
char const* CmdLineParser::m_inputImage   = "";
uint32_t    CmdLineParser::m_inputWidth   = 0;
uint32_t    CmdLineParser::m_inputHeight  = 0;
int         CmdLineParser::m_inputFormat  = -1;            // -1 by default to indicate user did not provide
int         CmdLineParser::m_inputPort    = -1;            // -1 by default to indicate user did not provide
// output parameters
uint32_t    CmdLineParser::m_outputWidth     = 1920;
uint32_t    CmdLineParser::m_outputHeight    = 1080;
uint32_t    CmdLineParser::m_rdiOutputWidth  = 0;
uint32_t    CmdLineParser::m_rdiOutputHeight = 0;
int         CmdLineParser::m_outputFormat    = -1;            // -1 by default to indicate user did not provide
int         CmdLineParser::m_outputPort      = -1;            // -1 by default to indicate user did not provide


/**************************************************************************************************
*   ParseCommandLine
*
*   @brief
*       Parse the command line using GNU Getopt feature
*   @return
*       0 on success, -1 on failure
**************************************************************************************************/
int CmdLineParser::ParseCommandLine(
    int argc,       ///< [in] the total number of arguments
    char** argv)    ///< [in] array of argument values
{
    int getOptReturn;

    // Parse all command line flag options with '-' and '--'
    while (true)
    {
        int optionIndex = 0;

        // TODO: Link all flags to test logic
        static struct option cmdLineOptions[] =
        {
            // option,            HasData,            flag,      value/alias
            { "help",             no_argument,        0,         'h' }, // --help    (-h)
            { "list",             no_argument,        0,         'l' }, // --list    (-l)
            { "verbose",          required_argument,  0,         'v' }, // --verbose (-v) [val]
            { "report",           no_argument,        0,         'r' }, // --report  (-r)
            { "frames",           required_argument,  0,         'f' }, // --frames  (-f) [val]
            { "camera",           required_argument,  0,         'c' }, // --camera  (-c) [val]
            { "timeout",          required_argument,  0,         't' }, // --timeout (-t) [val]

            // Run testsuite / testcase
            { "test",             required_argument,  0,      0 }, // --test [val]

            // Disable image dumping
            { "noimagedump",      no_argument,        0,      1 }, // --noimagedump
            { "nid",              no_argument,        0,      2 }, // --nid

            // Input parameters for configurable tests
            { "inputimage",       required_argument,  0,      3 }, // --inputimage [val]
            { "ii",               required_argument,  0,      4 }, // --ii [val]

            { "inputwidth",       required_argument,  0,      5 }, // --inputwidth [val]
            { "iw",               required_argument,  0,      6 }, // --iw [val]

            { "inputheight",      required_argument,  0,      7 }, // --inputheight [val]
            { "ih",               required_argument,  0,      8 }, // --ih [val]

            { "inputformat",      required_argument,  0,      9 }, // --inputformat [val]
            { "if",               required_argument,  0,     10 }, // --if [val]

            { "inputport",        required_argument,  0,     11 }, // --inputport [val]
            { "ip",               required_argument,  0,     12 }, // --ip [val]

            // Output parameters for configurable tests
            { "outputwidth",      required_argument,  0,     13 }, // --outputwidth [val]
            { "ow",               required_argument,  0,     14 }, // --ow [val]

            { "outputheight",     required_argument,  0,     15 }, // --outputheight [val]
            { "oh",               required_argument,  0,     16 }, // --oh [val]

            { "outputformat",     required_argument,  0,     17 }, // --outputformat [val]
            { "of",               required_argument,  0,     18 }, // --of [val]

            { "outputport",       required_argument,  0,     19 }, // --outputport [val]
            { "op",               required_argument,  0,     20 }, // --op [val]

            { "rdioutputwidth",   required_argument,  0,     21 }, // --rdioutputwidth [val]
            { "row",              required_argument,  0,     22 }, // --row [val]

            { "rdioutputheight",  required_argument,  0,     23 }, // --rdioutputheight [val]
            { "roh",              required_argument,  0,     24 }, // --roh [val]

            { 0,              0,                  0,      0 }  //last element is 0 to mark ending
        };

        getOptReturn = getopt_long(argc, argv, "hlrv:f:c:t:0:123:4:5:6:7:8:9:10:11:12:13:14:15:16:17:18:19:20:", cmdLineOptions, &optionIndex);

        if(getOptReturn == -1)
            break; //TODO: Add a better exit statement, preferably CAMX_ASSERT

        switch (getOptReturn)
        {
        case 'h':
        case '?':
            m_bHelp = true;
            break;
        case 'r':
            m_bReport = true;
            break;
        case 'v':
            m_nLog = atoi(optarg);
            break;
        case 'f':
            m_nFrames = atoi(optarg);
            break;
        case 'c':
            m_nCamera = atoi(optarg);
            break;
        case 't':
            m_timeout = atoi(optarg);
            break;
        case 0:
        {
            std::string delimiter = ".";
            std::string testArg(optarg);                               // convert to string type for further parsing
            m_suiteName = testArg.substr(0, testArg.find(delimiter));  // extract suite name
            m_caseName = testArg.erase(0, m_suiteName.size() + 1);     // extract case  name
            m_fullName = m_suiteName + delimiter + m_caseName;         // create valid test full name [unused]
            break;
        }
        case 1:
        case 2:
            m_bNoImageDump = true;
            break;
        case 3:
        case 4:
            m_inputImage = optarg;
            break;
        case 5:
        case 6:
            m_inputWidth = atoi(optarg);
            break;
        case 7:
        case 8:
            m_inputHeight = atoi(optarg);
            break;
        case 9:
        case 10:
            m_inputFormat = atoi(optarg);
            break;
        case 11:
        case 12:
            m_inputPort = atoi(optarg);
            break;
        case 13:
        case 14:
            m_outputWidth = atoi(optarg);
            break;
        case 15:
        case 16:
            m_outputHeight = atoi(optarg);
            break;
        case 17:
        case 18:
            m_outputFormat = atoi(optarg);
            break;
        case 19:
        case 20:
            m_outputPort = atoi(optarg);
            break;
        case 21:
        case 22:
            m_rdiOutputWidth = atoi(optarg);
            break;
        case 23:
        case 24:
            m_rdiOutputHeight = atoi(optarg);
            break;
        default:
            m_bHelp = true;
            break;
        }
    }

    if (m_bHelp)
    {
        return -1;
    }

    return 0;
}
/**************************************************************************************************
*   PrintCommandLineUsage
*
*   @brief
*       Print the usage instructions to stdout
*       Usage instructions are printed when a commandline error is detected or --help (-h) is used
**************************************************************************************************/
void CmdLineParser::PrintCommandLineUsage()
{
    printf("******************************** USAGE *********************************\n");
    printf(" --help    (-h)                   : print the usage instructions\n");
    printf(" --verbose (-v) [val]             : logging levels. Insert number in range [0,7]\n");
    printf("                                    [0-entry & exit, 2-debug, 3-info, 4-performance, 5-unsupported\n");
    printf("                                     6-warning, 7-error] and above messages\n");
    printf(" --report  (-r)                   : generate a summary report for the test\n");
    printf(" --frames  (-f) [val]             : override default number of frames to be dumped\n");
    printf(" --camera  (-c) [val]             : override for camera selection to run test on\n");
    printf(" --timeout (-t) [val]             : timeout in seconds while waiting for buffers/results (0 disables timeout)\n");
    printf(" --noimagedump (--nid)            : disable result image dumping to device\n");
    printf("\n");
    printf(" --test     (no alias) [val]      : run the given testsuite / testcases(s)\n");
    printf("                                    usage: --test TestSuiteName.TestCase or TestSuiteName.*\n");
    printf("\n");
    printf(" --inputimage  (--ii)  [val]      : set the input image for offline recipe tests\n");
    printf(" --inputwidth  (--iw)  [val]      : set the input width for recipe tests\n");
    printf(" --inputheight (--ih)  [val]      : set the input height for recipe tests\n");
    printf(" --inputformat (--if)  [val]      : set the input stream format for recipe tests\n");
    printf(" --inputport   (--ip)  [val]      : set the input port on IFE/IPE/BPS for recipe tests\n");
    printf("\n");
    printf(" --outputwidth  (--ow) [val]      : set the output width for recipe tests\n");
    printf(" --outputheight (--oh) [val]      : set the output height for recipe tests\n");
    printf(" --rdioutputwidth (--row) [val]   : Set the RDI output width for recipe tests and few mixed pipeline tests \n");
    printf(" --rdioutputheight (--roh) [val]  : Set the RDI output height for recipe tests and few mixed pipeline tests\n");
    printf(" --outputformat (--of) [val]      : set the output stream format for recipe tests\n");
    printf(" --outputport (--op) [val]        : set the output port on IFE/IPE/BPS for recipe tests\n");
    printf("************************************************************************\n");
}

/**************************************************************************************************
*   CmdLineParser::GetTargetProduct
*
*   @brief
*       Return string describing the target product
**************************************************************************************************/
const char* CmdLineParser::GetTargetProduct()
{
#ifdef TARGET_KONA
    return "Kona";
#elif TARGET_HANA
    return "Hana";
#elif TARGET_TALOSMOOREA
    return "Talos/Moorea";
#elif TARGET_NAPALI
    return "Napali";
#endif
    return "?";
}

/**************************************************************************************************
*   CmdLineParser::GetPlatformVersion
*
*   @brief
*       Return string describing the Android platform version
**************************************************************************************************/
const char* CmdLineParser::GetPlatformVersion()
{
#ifdef PLATFORM_VERSION_Q
    return "Q";
#elif PLATFORM_VERSION_P
    return "P";
#endif
    return "?";
}
