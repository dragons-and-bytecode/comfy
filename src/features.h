#ifndef __features_h__
#define __features_h__

#include "features/feature.h"
#include "features/auto_includeguard.h"

#include "list.h"

List* create_feature_list();
void destroy_feature_list(List* feature_list);

#endif
