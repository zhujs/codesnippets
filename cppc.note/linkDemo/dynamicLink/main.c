
#include <stdio.h>
#include "vector.h"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

extern int sharedVar;
int main(int argc, char *argv[])
{
    addvec(x, y, z, 2);
    printf("z = [%d %d]\n", z[0], z[1]);
    printf("The value of shared int variable: %d\n", sharedVar);
    return 0;
}
