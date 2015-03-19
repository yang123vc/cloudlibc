// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#ifndef COMMON_FLOAT10_H
#define COMMON_FLOAT10_H

#include <stddef.h>

// Handling of base-10 floating point numbers. These functions are
// wrappers around the double-conversion library.

__BEGIN_DECLS
float __float10_to_float(const char *, size_t, int);
double __float10_to_double(const char *, size_t, int);
long double __float10_to_long_double(const char *, size_t, int);
__END_DECLS

#endif
