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

Resource bundles are located in the resources directory. Standard ICU format
but keep it simple, we currently only support top level resources. Also, this
assumes that most strings will be less than 200 characters fully expanded.
There is an option to specify the buffer size but let's try to be reasonable
with our error messages, shall we?

Within the C/C++ code, use the macro:

```cc
#include "node_l10n.h"
#include <stdio.h>

...

// If KEY is found, prints the associated value, if not found,
// prints the fallback
printf("%s\n", L10N("KEY", "This is the fallback"));

// If KEY is found, prints the associated value using printf to fill
// in the blank. If key is not found, uses the fallback
printf("%s\n", L10Nf("KEY", "This is the %s", "fallback"));

// Same as L10Nf but uses a char[30] buffer instead of the default 200.
printf("%s\n", L10Nfn("KEY", "This is the %s", 30, "fallback" ));

// Same as L10N but uses a char[30] buffer instead of the default 200.
printf("%s\n", L10Nn("KEY", "This is the fallback", 30));
```

This is intended to be a first pass. I'm certain improvements can be made.
