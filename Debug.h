#pragma once
#if defined (DEBUG) | (_DEBUG)
#include <iostream>
#define DEBUG_LOG(x) std::cout << x << std::endl
#define WDEBUG_LOG(x) std::wcout << x << std::endl
#else
#define DEBUG_LOG(x)
#define WDEBUG_LOG(x)
#endif