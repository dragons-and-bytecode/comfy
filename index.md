---
title: Comfy
subtitle: the comfortable C dialect
layout: default

---

The C language with it's bare metal simplicity and no-nonsence attitude is awesome.

But since it has been with us for a long time now, it has been getting on a bit. It is time to admit: It has been getting a bit rusty lately.

To polish it up, and let the old girl shine as new again, we created **Comfy**, a lightweight dialect preprocessor to C, to (hopefully) keep us from becoming completely insane while we are developing our bigger game engine project.


## And what is that now?

Like ```coffeescript``` for ```javascript```, **Comfy** is a dialiect, that parses directly into ```C``` source files.

**Comfy** is also a command line tool, that does said parsing eigther on a one-time basis (for builds) or while watching a directory for changes (while developing).

Simply fire up a shell, and point comfy to the input and output directories you like.

> By default, **comfy** will use athe current directory for input and output, and will run in watch mode. so the following command will watch for files in the current directory and write them to ```./build/```.

    $ comfy --output ./build
    Watching directory: /usr/johndoe/projects/foo
        welcome.comfy changed.
            (Re)creating welcome.c        [DONE]
            (Re)creating welcome.h        [DONE]
        

## Awesome, where do I start

There is no means, to install **Comfy** yet, but we are in the progress of making it availible via *Homebrew* for Mac OS.

If you absolutelly cannot wait, clone our (Repository)[https://github.com/dragons-and-bytecode/comfy] and build from source, using make.
