# P-Rex

## What is this?

POSIX regex in JavaScript, using WASM.


## Why?

For compatibility reasons, sometimes you need to match the POSIX standard exactly. This does that.


## How do I use it?

```js
import { prexRawMatch } from "https://deno.land/x/prex@0.0.0.1/main.js"

console.log( 
    prexRawMatch(
        /[[:space:]]+([[:upper:]]+)[[:space:]]+/,
        "  FOO   "
    )
)
// [ "  FOO   ", "FOO" ]

console.log( 
    prexRawMatch(
        /[[:space:]]+([[:upper:]]+)[[:space:]]+/,
        "  foo   "
    )
)
// [ ]

```
