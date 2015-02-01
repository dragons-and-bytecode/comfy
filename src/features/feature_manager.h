#ifndef __feature_manager_h__
#define __feature_manager_h__

#include "../base.h"

void feature_manager_init();
void feature_manager_teardown();

string feature_manager_process(string file_name, string content);

#endif
