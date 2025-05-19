// This file is a part of the QPlane project
// Copyright (C) 2025 XnLogicaL
// Licensed under the GNU General Public License v3.0

#ifndef QPL_CORE_CONFIG_HPP
#define QPL_CORE_CONFIG_HPP

//
// ─── Compiler Detection ────────────────────────────────────────────────
//
#define QPL_COMPILER_GCC   0
#define QPL_COMPILER_CLANG 1
#define QPL_COMPILER_MSVC  2

#if defined(__clang__)
#define QPL_COMPILER QPL_COMPILER_CLANG
#elif defined(_MSC_VER)
#define QPL_COMPILER QPL_COMPILER_MSVC
#elif defined(__GNUC__)
#define QPL_COMPILER QPL_COMPILER_GCC
#else
#error "Unsupported compiler"
#endif

//
// ─── Function Inlining & Attributes ────────────────────────────────────
//
#define QPL_INLINE           inline
#define QPL_INLINE_CONSTEXPR inline constexpr
#define QPL_NODISCARD        [[nodiscard]]
#define QPL_NORETURN         [[noreturn]]

#if QPL_COMPILER == QPL_COMPILER_MSVC
#define QPL_ALWAYS_INLINE __forceinline
#define QPL_NOINLINE      __declspec(noinline)
#define QPL_RESTRICT      __restrict
#define QPL_HOT           // no MSVC equivalent
#define QPL_LIKELY(x)     (x)
#define QPL_UNLIKELY(x)   (x)
#define QPL_UNREACHABLE() __assume(0)
#define QPL_DEBUGTRAP()   __debugbreak()
#else
#define QPL_ALWAYS_INLINE __attribute__((always_inline)) inline
#define QPL_NOINLINE      __attribute__((noinline))
#define QPL_RESTRICT      __restrict__
#define QPL_HOT           __attribute__((hot))
#define QPL_LIKELY(x)     (__builtin_expect(!!(x), 1))
#define QPL_UNLIKELY(x)   (__builtin_expect(!!(x), 0))
#define QPL_UNREACHABLE() __builtin_unreachable()
#define QPL_DEBUGTRAP()   __builtin_trap()
#endif

#endif // QPL_CORE_CONFIG_HPP
