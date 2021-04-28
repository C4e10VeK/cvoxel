#include <stdio.h>
#include <cvector.h>

int main()
{
    Vector intVector;

    int a[] = {
        1, 2, 3, 4, 5, 6, 7
    };

    VECTOR_INIT(intVector, int);

    VECTOR_ADD_RANGE(intVector, a);

    for (size_t i = 0; i < intVector._size; i++) 
    {
        printf("%i\n", VECTOR_GET_ITEM(int, intVector, i));
    }

    printf("Hello world!\n");

    VECTOR_FREE(intVector);
    
    return 0;
}
