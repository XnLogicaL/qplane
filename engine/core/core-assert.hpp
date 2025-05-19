// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL - Licensed under GNU GPL v3.0

#ifndef QPL_CORE_ASSERT_HPP
#define QPL_CORE_ASSERT_HPP

#include "core-config.hpp"
#include "core-io.hpp"

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#define QPL_HAS_SOURCE_LOCATION __has_include(<source_location>)

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#else
#include <execinfo.h>
#include <unistd.h>
#endif

#if QPL_HAS_SOURCE_LOCATION
#include <source_location>
using src_loc = std::source_location;
#else
struct src_loc {
  static src_loc current(
    const char* file = __builtin_FILE(), int line = __builtin_LINE(), const char* func = __builtin_FUNCTION()
  ) {
    return {file, line, func};
  }

  std::string m_file_name;
  int m_line;
  std::string m_function_name;

  // clang-format off
  QPL_INLINE int line() const { return m_line; }
  QPL_INLINE const char* file_name() const { return m_file_name.c_str(); }
  QPL_INLINE const char* function_name() const { return m_function_name.c_str(); }
  // clang-format on
};
#endif

namespace qpl {

QPL_INLINE void AssertPrintBacktrace(std::ostream& os = std::cerr, size_t skip = 2) {
#ifdef _WIN32
  void* stack[64];
  HANDLE process = GetCurrentProcess();
  SymInitialize(process, nullptr, TRUE);
  WORD frames = CaptureStackBackTrace((DWORD)skip, 64, stack, nullptr);

  SYMBOL_INFO* symbol = (SYMBOL_INFO*)std::calloc(sizeof(SYMBOL_INFO) + 256, 1);
  symbol->MaxNameLen = 255;
  symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

  for (WORD i = 0; i < frames; ++i) {
    SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
    os << "  [" << i << "] " << symbol->Name << " - 0x" << std::hex << symbol->Address << std::dec << "\n";
  }

  std::free(symbol);
#else
  void* callstack[128];
  int frames = backtrace(callstack, 128);
  char** symbols = backtrace_symbols(callstack, frames);

  for (int i = skip; i < frames; ++i) {
    os << "  [" << i - skip << "] " << symbols[i] << "\n";
  }
  std::free(symbols);
#endif
}

QPL_INLINE void AssertFail(const char* exprStr, const src_loc& loc) {
  LogError(std::format("Runtime assertion '{}' failed:", exprStr));
  std::cerr << " at " << loc.file_name() << ':' << loc.line() << ':' << loc.column() << ' ' << loc.function_name()
            << "\n";
  std::cerr << " stacktrace:\n";
  AssertPrintBacktrace();
  std::abort();
}

} // namespace qpl

#if QPL_HAS_SOURCE_LOCATION
#define QPL_CORE_ASSERT(expr) ((expr) ? (void)0 : qpl::AssertFail(#expr, std::source_location::current()))
#else
#define QPL_CORE_ASSERT(expr) ((expr) ? (void)0 : qpl::AssertFail(#expr, qpl::src_loc::current()))
#endif

#endif
