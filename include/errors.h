// SPDX-License-Identifier: GPL-2.0

#ifndef INCLUDE_ERRORS_H
#define INCLUDE_ERRORS_H

#if defined(DEBUG)
#include "debug.h"

// errors
#define ER_NULL_PTR pr_error("Null pointer")
#define ER_INV_BUFFSIZE                                                        \
    pr_error("buffer size out of range or exceed which indeed")
// warnings

// avoiding buffer overflow by truncating the buffer to the maximum length
// defined in prompt.h
#define WR_TRUNCATE_BUFFER pr_warn("Truncate buffer")

#endif /*DEBUG*/

//IS_NULL_PTR MACRO  contains a debug option so prefer the compare to null in often cas
#define IS_NULL_PTR(ptr)                                                      \
	({                                                                        \
		__typeof__(ptr) _ptr = (ptr);                                         \
		int _is_null = (_ptr == NULL);                                        \
		if (_is_null)                                                         \
			pr_error("Null pointer: %s", #ptr);                              \
		_is_null;                                                             \
	})

#endif /*INCLUDE_ERRORS_H*/