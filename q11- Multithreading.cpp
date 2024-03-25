#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun1(void *vargp) {
    sleep(1);
    int a=5,b=2;
    printf("Sum of numbers 5 & 2 are =%d\n",a+b);
    return NULL;
}

void *myThreadFun2(void *vargp) {
    sleep(2);
    int a=5,b=2;
    printf("product of numbers 5 & 2 are =%d\n",a*b);
    return NULL;
}

int main() {
    pthread_t thread_id1, thread_id2;

    printf("Threading starts\n");

    pthread_create(&thread_id1, NULL, myThreadFun1, NULL);
    pthread_create(&thread_id2, NULL, myThreadFun2, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    printf("Threading ends\n");

    exit(0);
}

