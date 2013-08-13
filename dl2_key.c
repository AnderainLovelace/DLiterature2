#include "dl2_all.h"

uint waitkey() {uint key ;GetKey(&key);return key;}
void wait(uint key) {uint k;do{GetKey(&k);}while(key!=k);}