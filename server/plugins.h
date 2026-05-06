#ifndef PLUGINS_H
#define PLUGINS_H

struct Plugin{
int id;
int version;
void (*free)(void *ptr);
};

int plugins_load();
void Plugin_free(void* ptr);

#endif
