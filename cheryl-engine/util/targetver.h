#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

// TODO: regress this to vista? I don't have the headers to look it up
#include <WinSDKVer.h>
#ifdef _WIN32_WINNT
#  undef _WIN32_WINNT
#endif
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <SDKDDKVer.h>
