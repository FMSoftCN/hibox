/**
 * @file config.h
 * @author Vincent Wei (https://github.com/VincentWei)
 * @date 2021/09/18
 * @brief The configuration header file of HiBox.
 *
 * Copyright (C) 2021 FMSoft <https://www.fmsoft.cn>
 *
 * This file is a part of HiBox, which contains some common utilities for C.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#if defined(HAVE_CONFIG_H) && HAVE_CONFIG_H && defined(BUILDING_WITH_CMAKE)
#include "cmakeconfig.h"
#endif

#include <wtf/Platform.h>

#include <wtf/ExportMacros.h>

#if !defined(HIBOX_EXPORT)

#if defined(BUILDING_HIBOX) || defined(STATICALLY_LINKED_WITH_HIBOX)
#define HIBOX_EXPORT WTF_EXPORT_DECLARATION
#else
#define HIBOX_EXPORT WTF_IMPORT_DECLARATION
#endif

#endif /* HIBOX_EXPORT */

#if !HAVE(DLFCN_H)
#undef HAVE_DLFCN_H
#endif
#if !HAVE(ENDIAN_H)
#undef HAVE_ENDIAN_H
#endif
#if !HAVE(FCNTL_H)
#undef HAVE_FCNTL_H
#endif
#if !HAVE(INTTYPES_H)
#undef HAVE_INTTYPES_H
#endif
#if !HAVE(LIMITS_H)
#undef HAVE_LIMITS_H
#endif
#if !HAVE(LOCALE_H)
#undef HAVE_LOCALE_H
#endif
#if !HAVE(MEMORY_H)
#undef HAVE_MEMORY_H
#endif
#if !HAVE(STDARG_H)
#undef HAVE_STDARG_H
#endif
#if !HAVE(STDINT_H)
#undef HAVE_STDINT_H
#endif
#if !HAVE(STDLIB_H)
#undef HAVE_STDLIB_H
#endif
#if !HAVE(STRINGS_H)
#undef HAVE_STRINGS_H
#endif
#if !HAVE(STRING_H)
#undef HAVE_STRING_H
#endif
#if !HAVE(SYSLOG_H)
#undef HAVE_SYSLOG_H
#endif
#if !HAVE(SYS_CDEFS_H)
#undef HAVE_SYS_CDEFS_H
#endif
#if !HAVE(SYS_PARAM_H)
#undef HAVE_SYS_PARAM_H
#endif
#if !HAVE(SYS_RANDOM_H)
#undef HAVE_SYS_RANDOM_H
#endif
#if !HAVE(SYS_RESOURCE_H)
#undef HAVE_SYS_RESOURCE_H
#endif
#if !HAVE(SYS_STAT_H)
#undef HAVE_SYS_STAT_H
#endif
#if !HAVE(SYS_TYPES_H)
#undef HAVE_SYS_TYPES_H
#endif
#if !HAVE(UNISTD_H)
#undef HAVE_UNISTD_H
#endif
#if !HAVE(XLOCALE_H)
#undef HAVE_XLOCALE_H
#endif
#if !HAVE(DECL_ISINF)
#undef HAVE_DECL_ISINF
#endif
#if !HAVE(DECL_ISNAN)
#undef HAVE_DECL_ISNAN
#endif
#if !HAVE(DECL_NAN)
#undef HAVE_DECL_NAN
#endif
#if !HAVE(DECL_INFINITY)
#undef HAVE_DECL_INFINITY
#endif
#if !HAVE(DECL__FINITE)
#undef HAVE_DECL__FINITE
#endif
#if !HAVE(DECL__ISNAN)
#undef HAVE_DECL__ISNAN
#endif
#if !HAVE(OPEN)
#undef HAVE_OPEN
#endif
#if !HAVE(REALLOC)
#undef HAVE_REALLOC
#endif
#if !HAVE(SETLOCALE)
#undef HAVE_SETLOCALE
#endif
#if !HAVE(SNPRINTF)
#undef HAVE_SNPRINTF
#endif
#if !HAVE(STRCASECMP)
#undef HAVE_STRCASECMP
#endif
#if !HAVE(STRDUP)
#undef HAVE_STRDUP
#endif
#if !HAVE(STRERROR)
#undef HAVE_STRERROR
#endif
#if !HAVE(STRNCASECMP)
#undef HAVE_STRNCASECMP
#endif
#if !HAVE(USELOCALE)
#undef HAVE_USELOCALE
#endif
#if !HAVE(VASPRINTF)
#undef HAVE_VASPRINTF
#endif
#if !HAVE(VPRINTF)
#undef HAVE_VPRINTF
#endif
#if !HAVE(VSNPRINTF)
#undef HAVE_VSNPRINTF
#endif
#if !HAVE(VSYSLOG)
#undef HAVE_VSYSLOG
#endif
#if !HAVE(GETRANDOM)
#undef HAVE_GETRANDOM
#endif
#if !HAVE(GETRUSAGE)
#undef HAVE_GETRUSAGE
#endif
#if !HAVE(STRTOLL)
#undef HAVE_STRTOLL
#endif
#if !HAVE(STRTOULL)
#undef HAVE_STRTOULL
#endif

