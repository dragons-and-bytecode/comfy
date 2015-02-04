# comfy

[![Build Status](https://travis-ci.org/dragons-and-bytecode/comfy.svg?branch=master)](https://travis-ci.org/dragons-and-bytecode/comfy)

The comfortable C dialect.

The C language has been getting on a bit. And although I still like it, for
it's bare metal simplicity and no-nonsence attitude, it is time to admit: It
has been getting a bit rusty lately.

While starting our bigger engine project, which will be mainly written in C, we
will also develop a lightweight dialect preprocessor to C, to (hopefully) keep
us from becoming completely insane.

Maybe this is not really necessary; Maybe this is even stupid. But it seems
like fun, and could just maybe turn out to be something really good. :)

As the **Comfy** dialect grows, this readme should be keeping track about all
the little changes from the original C language.


## Automatic include guard

    @version: 0.1

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


## Automatic Header creation

This is the big one.

The one thing that did not only always bug me about coding in C, but which I find actually slightly dangerous is the need for separate header files.

Having to maintain header files, alongside your actual code means that you'll

 * have to say goodbye to the DRY principle, since you will write most
   definitions two times.
 * Write documentation in a separate file to the rest of your code, which will
   likely lead to worse documentation (programmery ARE lazy after all).
 * Be slower and clunkier, when working with the code of a module, since you
   will be looking up definitions in the header file and then switching back to
   the source file all the time.

Aside from those, it is simply unnecessary today.

With **Comfy** you are able, to write your code in ```.comfy``` files, which
the **Comfy** processor will parse into a ```.c``` and a ```.h``` file.

It will do so, separating out any lines, that start with the token ```§``` out
into the header file and writing any unmasked lines into the resulting c source
file.

It will also add an include to the source file, which includes the newly
generated header into the source.

So this comfy source:

    #include <stdio.h>

    § /**
    §  * Says hello to anybody
    §  */
    § void sayHello();
    void sayHello()
    {
        printf("Hello World.\n");
    }

will be translated into a C header file, containing the comment and method
declaration like so:

    /**
     * Says hello to anybody
     */
    void sayHello();

as well, as a C source file, containing the rest, and having an include to our
new header file.

    #include "hello.h"
    #include <stdio.h>

    void sayHello()
    {
        printf("Hello World.\n");
    }

This step happens, right after all the ```.comfy``` related features are
processed, but before all the ```.header``` or ```.c``` related features are
processed.

This will, in combination with some future ```.comfy``` features allow you,
to semantically separate code into public and private, without having to
maintain two separate code bases to do so.
