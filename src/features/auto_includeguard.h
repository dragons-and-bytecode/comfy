/**
 * @file
 * 
 * the Auto Include Guard Feature will process any **header** files, that do not
 * already have an include guard around them.
 *
 * This means formally:
 * * If the source file is a **header** file AND it does not already have a 
 *   guard.
 * * If the source file is a **comfy** file AND a target header file does 
 *   already exist AND that target header file does not already have a guard.
 *
 * Whether a file already has an include guard is determined via:
 * * Does the first non empty line of the file match '#pragma once'?
 * * Do the first two non empty lines match '#ifndef (\s+)' and '#define (\s+)'
 *   where the content of '(\s+)' is the same for both lines AND does the last
 *   non empty line of the file match '#endif'
 */

#ifndef __auto_includeguard_h__
#define __auto_includeguard_h__

#include "../base.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "feature.h"
#include "../processor.h"

Feature* create_auto_incudeguard();

#endif
