#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include <map>

#include "../plugins/API.h"
#include "commands.h"

void* handle;

void cerror(){
  char* error = dlerror();

  if(error){
    printf("%s",error);
    dlclose(handle);
    exit(2);
  }
}


int plugins_load(){
  handle = dlopen("../plugins/build/libcommands.so",RTLD_LAZY);
  if(!handle){
    printf("%s\n",dlerror());
    exit(1);
  }

  using version_t = int(*)();
  version_t Version = (version_t) dlsym(handle,"Version");

  char* error = dlerror();

  cerror();

  if(Version()!=1){
  printf("Spatna verze pluginu\n");
  exit(3);
  }

  using init_t = int(*)(API_commands);
  init_t Init = (init_t) dlsym(handle,"Init");

  cerror();
  API_commands api_commands{.command_reg=command_reg};

  Init(api_commands);

  //dlclose(handle);
  return 0;
}
