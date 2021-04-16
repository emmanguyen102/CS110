#include "array_operations.hh"

using namespace std;

int greatest_v1(int* itemptr, int size) {
    auto a = itemptr;
    int max = 0;
    while ( itemptr < a + size ) {
        if(max < *itemptr) {
            max = *itemptr;
        }
        ++itemptr;
    }
    return max;

}

int greatest_v2(int* itemptr, int* endptr) {
    int max = 0;
    while ( itemptr < endptr ) {
        if(max < *itemptr) {
            max = *itemptr;
        }
        ++itemptr;
    }

    return max;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
    int length = endptr - itemptr;
    for(int i=0 ; i<length ; i++){
        *(targetptr+i) = *(itemptr+i);
    }
}

void reverse(int* leftptr, int* rightptr) {
    rightptr--;
    while (leftptr < rightptr) {
        int temp = *leftptr;
        *leftptr = *(rightptr);
        *rightptr = temp;
        leftptr++;
        rightptr--;
    }
}

