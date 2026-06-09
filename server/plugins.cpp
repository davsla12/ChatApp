#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include <map>

#include "../plugins/API.h"
#include "./commands.h"
#include "./plugins.h"
#include "./helpers.h"

void* handle;

Plugin plugin;

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

  using init_t = int(*)(API_s);
  init_t Init = (init_t) dlsym(handle,"Init");

  cerror();
  API_s apis;
  apis.commands = {.command_reg = command_reg};
  apis.users = {.users_getbid = users_getbid,
                .users_getstr = users_getstr};
  apis.helpers.send_bid = send_bid;
  Init(apis);

  using free_t = void(*)(void*);
  free_t Free = (free_t)dlsym(handle,"Free");
  cerror();
  plugin.free = Free;

  //dlclose(handle);
  return 0;
}

void Plugin_free(void* ptr){
  plugin.free(ptr);
}

void* Plugin_realloc(String ptr){
  
}
