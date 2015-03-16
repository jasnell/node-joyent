Localization bundle for Node.

This is pretty straightforward... if ICU is present, then ICU's resource
bundle mechanism is used, the resources are compiled statically into the
library, which can then be used within Node. If ICU is not present, a simple
sprintf fallback is used. Everything is macro-driven and keyed off the
--with-intl configuration flag, just like the Intl.

```
./configure --with-intl={any value}
make
```
When the --with-intl switch is on, the resources are compiled into a static
library that is statically linked into Node. The next step will be to make
it so that additional bundles can be specified at runtime.

Resource bundles are located in the resources directory. Standard ICU bundle
format but keep it simple, we currently only support top level resources.

Within the C/C++ code, use the macro:

```cc
#include "node_l10n.h"
#include <stdio.h>

...
// If KEY is found, prints the associated value,
// if not found, uses the fallback
printf(L10N("KEY", "This is the fallback"));
printf(L10N("KEY", "This is the %s"), "fallback");
```
