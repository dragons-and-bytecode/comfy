#ifndef __feature_h__
#define __feature_h__

#include "../base.h"
#include "../processor.h"

typedef struct Feature {
    bool (*would_modify)(const ComfyFile* bundle);
    void (*process)(ComfyFile* bundle);
} Feature;

#endif