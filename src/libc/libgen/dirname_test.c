// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <libgen.h>
#include <stddef.h>
#include <testing.h>

TEST(dirname, null) {
  ASSERT_STREQ(".", dirname(NULL));
}

TEST(dirname, example) {
#define EXAMPLE(in, out)               \
  {                                    \
    char inbuf[] = in;                 \
    ASSERT_STREQ(out, dirname(inbuf)); \
  }
  EXAMPLE("///", "/");
  EXAMPLE("/usr//lib//", "/usr");

  // Examples from POSIX.
  EXAMPLE("/usr/lib", "/usr");
  EXAMPLE("/usr/", "/");
  EXAMPLE("usr", ".");
  EXAMPLE("/", "/");
  EXAMPLE(".", ".");
  EXAMPLE("..", ".");
  EXAMPLE("//foo", "/");
#undef EXAMPLE
}
