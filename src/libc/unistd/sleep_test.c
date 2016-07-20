// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <testing.h>
#include <time.h>
#include <unistd.h>

TEST(sleep, example) {
  // We should sleep somewhere between 1 and 3 seconds.
  time_t before = time(NULL);
  ASSERT_EQ(0, sleep(2));
  time_t after = time(NULL);
  ASSERT_LE(before + 1, after);
  ASSERT_GE(before + 3, after);
}
