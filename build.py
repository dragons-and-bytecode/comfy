#!/usr/bin/python3

from sys import argv, stderr
from subprocess import call
import os

from buildtools import *

default_target = 'compile'

sources_dir = './src'
build_dir = './build'

def is_sourcefile(file):
    return file.endswith(".c") or file.endswith(".C")

def gather_sources(source_dir):
    sources = []
    for file in os.listdir(source_dir):
        file = os.path.join(source_dir, file)
        if os.path.isdir(file):
            sources += gather_sources(file)
        elif is_sourcefile(file):
            sources += [file]
            
    return sources

def compile():
    print("Compiling...")
    sources = gather_sources(sources_dir)
    make_directories(build_dir)
    call(["clang", "-o", "%s/comfy" % build_dir] + sources)

if __name__ == '__main__':
    target = argv[1] if len(argv) >= 2 else default_target
    
    target_func = globals().get(target)
    if not target_func or not callable(target_func):
        print("Unknown target %s" % target, file=stderr)
        exit(1)
    else:
        print("Building %s" % target)
        eval(target)()
    