#pragma once

#ifdef _WIN32
#ifdef RSXML_EXPORTS
#define RSXML_API __declspec(dllexport)
#else
#define RSXML_API __declspec(dllimport)
#endif
#else
#define RSXML_API
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>