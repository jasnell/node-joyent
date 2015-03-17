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

#if defined(NODE_HAVE_I18N_SUPPORT)
#include <l10n.h>
#define L10N_INIT(locale) do {l10n_initialize(locale);} while(0)
#else

// If I18N Support is not enabled use simple sprintf fallback
#define L10N(key, fallback) ({fallback;})
#define L10N_INIT(locale) do {} while(0)

#endif

#define L10N_PRINTF(key, fallback)                                 \
  do {                                                             \
    const char * res = L10N(key,fallback);                         \
    printf(res);                                                   \
    if (res != fallback) {delete[] res; }                          \
  } while(0)

#define L10N_PRINTFV(key, fallback, ...)                           \
  do {                                                             \
    const char * res = L10N(key,fallback);                         \
    printf(res, __VA_ARGS__);                                      \
    if (res != fallback) {delete[] res; }                          \
  } while(0)

#define L10N_ASPRINTF(key, target, fallback) ({                    \
  const char * res = L10N(key,fallback);                           \
  int ret = asprintf(&target, res);                                \
  if (res != fallback) { delete[] res; }                           \
  ret; })

#define L10N_ASPRINTFV(key, target, fallback, ...) ({              \
  const char * res = L10N(key,fallback);                           \
  int ret = asprintf(&target, res, __VA_ARGS__);                   \
  if (res != fallback) { delete[] res; }                           \
  ret; })

#ifndef SRC_BUNDLE_H_
#define SRC_BUNDLE_H_

#include "env.h"

namespace node {

class Bundle {
 public:
  static void Initialize(v8::Handle<v8::Object> target,
                         v8::Handle<v8::Value> unused,
                         v8::Handle<v8::Context> context);
 private:
  static void Fetch(const v8::FunctionCallbackInfo<v8::Value>& args);
};

} // namespace node

#endif // SRC_BUNDLE_H_
