#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include <map>
#include <string>
#include <dirent.h>
#include <fnmatch.h>

#include "../plugins/API.h"
#include "./commands.h"
#include "./plugins.h"
#include "./helpers.h"

void* handle;
static int IDs = 0;

Plugin plugin;
std::vector<Plugin> plugins;

void cerror(){
  char* error = dlerror();

  if(error){
    fprintf(stderr,"%s\n",error);
    dlclose(handle);
    exit(2);
  }
}


int plugins_load(){
  DIR* dir = opendir("../plugins/build");
  if(dir == NULL){
    perror("../plugins/build\n");
    exit(1);
  }
  struct dirent* item;

  while((item = readdir(dir)) != NULL){
    if (fnmatch("lib*.so", item->d_name, 0) != 0) {continue;}
    printf("%s\n", item->d_name);

  handle = dlopen(std::string(std::string("../plugins/build/")+std::string(item->d_name)).c_str(),RTLD_LAZY);
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
  plugin.version = Version();

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

  plugin.handle = handle;
  plugin.id = IDs++;
  plugins.push_back(plugin);
  }
  return 0;
}

void Plugin_free(void* ptr){
  plugin.free(ptr);
}

void* Plugin_realloc(String ptr){
  
}
