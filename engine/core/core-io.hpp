// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_CORE_IO_HPP
#define QPL_CORE_IO_HPP

#include <iostream>
#include "core-config.hpp"

namespace qpl {

QPL_INLINE void LogInfo(const std::string& message) {
  std::cout << "[\033[32mINF\033[0m] " << message << "\n";
}

QPL_INLINE void LogWarning(const std::string& message) {
  std::cout << "[\033[33mWRN\033[0m] " << message << "\n";
}

QPL_INLINE void LogError(const std::string& message) {
  std::cerr << "[\033[31mERR\033[0m] " << message << "\n";
}

} // namespace qpl

#endif
