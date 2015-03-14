// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef L10N__H
#define L10N__H

#include "l10n_version.h"
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
# define L10N_EXTERN /* nothing */
#elif __GNUC__ >= 4
# define L10N_EXTERN __attribute__((visibility("default")))
#else
# define L10N_EXTERN /* nothing */
#endif

/**
 * Initialize the resource bundle. This will register an atexit handler
 * to deal with the cleanup in normal termination
 **/
L10N_EXTERN bool l10n_initialize(const char * locale);

/**
 * Fetch the value for the specified key. Returns a pointer to dest.
 **/
L10N_EXTERN const char * l10n_fetch(const char * key,
                                    const char * fallback,
                                    char * dest,
                                    int32_t *len);

/**
 * Fetch the value for the specified key then do a u_sprintf with the
 * provided varargs... return the resulting string
 **/
L10N_EXTERN const char * l10n_sprintf(const char * key,
                                      const char * fallback,
                                      char * dest,
                                      int32_t *len,
                                      ...);

/**
 * Lookup the key, return the value. Doesn't get much easier. fallback
 * is ignored here. Uses a maximum buffer size of 200. If you need to
 * specify an alternative buffer size, use the L10Nn variant
 **/
#define L10N(key, fallback) ({                                          \
  char buffer[200];                                                     \
  int32_t len = sizeof(buffer);                                         \
  const char * res = l10n_fetch(key, fallback, buffer, &len);           \
  res; })

/**
 * Lookup the key, return the value. fallback is ignored. Uses a supplied
 * maximum buffer size. example: L10Nn("foo", "ignored", 100)
 **/
#define L10Nn(key, fallback, len) ({                                    \
  char buffer[len];                                                     \
  int32_t len = sizeof(buffer);                                         \
  const char * res = l10n_fetch(key, fallback, buffer, &len);           \
  res; })

/**
 * Lookup the key, use the value as the pattern for a sprintf. Uses a
 * maximum buffer size of 200. If you need to specify an alternative buffer
 * size, use the L10Nfn variant
 **/
#define L10Nf(key, fallback, ...) ({                                          \
  char buffer[200];                                                           \
  int32_t blen = sizeof(buffer);                                              \
  const char * res = l10n_sprintf(key, fallback, buffer, &blen, __VA_ARGS__); \
  res;                                                                        \
})

/**
 * Lookup the key, use the value as the pattern for a sprintf. Uses a
 * supplied maximum buffer size. example: L10Nn("foo", "ignored", 100, "a", 1)
 **/
#define L10Nfn(key, fallback, len, ...) ({                                    \
  char buffer[len];                                                           \
  int32_t blen = sizeof(buffer);                                              \
  const char * res = l10n_sprintf(key, fallback, buffer, &blen, __VA_ARGS__); \
  res; })

#endif // L10N__H
