#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace std;
#define MAX_SIZE 100

int ArrayCompartido[MAX_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fibonacciThread(void* arg) {
    int n = *(int*)arg;
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);
        ArrayCompartido[i] = a;
        int tmp = b;
        b += a;
        a = tmp;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<<"Error: se requiere un argumento para el número de elementos de Fibonacci.\n";
        return 1;
    }
    
    int n = atoi(argv[1]);
    if (n <= 0) {
       cout<<"Error: el número de elementos de Fibonacci debe ser un entero positivo.\n";
        return 1;
    }
    
    pthread_t thread;
    int args[1];
    args[0] = n;
    pthread_create(&thread, NULL, fibonacciThread, args);
    pthread_join(thread, NULL);
    
    printf("La secuencia de Fibonacci con %d elementos es:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", ArrayCompartido[i]);
    }
    cout<<"\n";
    
    return 0;
}
