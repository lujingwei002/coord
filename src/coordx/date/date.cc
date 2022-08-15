#include "coordx/date/date.h"

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
namespace coordx {
namespace date {
    
   const char* FormatNano(uint64_t nano) {
       static thread_local char buff[128];
       buff[0] = 0;
       if (nano < 0){
           return buff;
       }
       if(nano > 1000000000){
           sprintf(buff, "%lds", nano/1000000000);
           return buff;
       } else if(nano > 1000000){
           sprintf(buff, "%ldms", nano/1000000);
           return buff;
       } else if(nano > 1000){
           sprintf(buff, "%ldµs", nano/1000);
           return buff;
       } else {
           sprintf(buff, "%ldns", nano);
           return buff;
       }
       return buff;
   }

    
}
}