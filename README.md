# comfy

The comfortable C dialect.

The C language has been getting on a bit. And although I still like it, for it's bare metal simplicity and no-nonsence attitude, it is time to admit: It has been getting a bit rusty lately.

While starting our bigger engine project, which will be mainly written in C, we will also develop a lightweight dialect preprocessor to C, to (hopefully) keep us from becoming completely insane.

Maybe this is not really necessary; Maybe this is even stupid. But it seems like fun, and could just maybe turn out to be something really good. :)

As the **Comfy** dialect grows, this readme should be keeping track about all the little changes from the original C language.


## Automatic include guard

    @version: FUTURE

I never met anybody, who used includes in a way, that they didn't profit from
include guards. Thus (except for lazyness) I have never seen C (or C++) code
that didn't include-guard its headers.

The **Comfy** preprocessor will therefore prepend any header it is given with
an include guard automatically.

The following is therefore not neccessary anymore:

    #ifndef __headername__
    #define __headername__

    //Your code goes here...

    #endif

