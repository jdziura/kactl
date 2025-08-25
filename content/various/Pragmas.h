/**
 * Author: nor
 * Description: GCC optimization pragmas. Should be added before \texttt{bits}.
 */
#pragma once

#include <bits/allocator.h> /// keep-include
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")