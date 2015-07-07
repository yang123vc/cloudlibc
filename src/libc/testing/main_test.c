// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <argdata.h>
#include <program.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <testing.h>

static int tmpdir = -1;
static int logfile = -1;

static bool fetch_fds(const argdata_t *key, const argdata_t *value,
                      void *thunk) {
  // Fetch key and value.
  const char *keystr;
  if (argdata_get_str_c(key, &keystr) != 0)
    return true;
  int valuefd;
  if (argdata_get_fd(value, &valuefd) != 0)
    return true;

  // Set file descriptors.
  if (strcmp(keystr, "tmpdir") == 0)
    tmpdir = valuefd;
  else if (strcmp(keystr, "logfile") == 0)
    logfile = valuefd;
  return true;
}

void program_main(const argdata_t *ad) {
  // Fetch file descriptor numbers from arguments.
  argdata_iterate_map(ad, NULL, fetch_fds);

  // Set up stderr.
  FILE *f = fdopen(logfile, "w");
  if (f != NULL)
    fswap(stderr, f);

  // Invoke test suite.
  testing_execute(tmpdir, logfile);
  exit(0);
}
