#pragma once

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <string>
#include <chrono>
#include <memory>
#include <cassert>
#include <type_traits>
#include <atomic>
#include <thread>
#include <functional>
#include <cassert>

using byte		= unsigned char;
using wchar		= wchar_t;

#define SAFE_DELETE( Val )\
if( Val != nullptr )\
{ delete Val; Val = nullptr; }