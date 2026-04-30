#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include <map>

//std::map<void*> Plugins;

int plugins_load(){
  void* handle = dlopen("plugins/build/libcommands.so",RTLD_LAZY);
  if(!handle){
    printf("%s\n",dlerror());
    exit(1);
  }
  return 0;
}
