#include <ctime>
#include <cstdlib>
#include "Random.h"

int seed = time(0);
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

int init_random(){
    srand(seed);
    return 0;
}
