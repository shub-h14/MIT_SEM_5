#include <pthread.h>
#include <stdio.h>

int fib[100];

void* child_thread(void * param){
    int *id = (int *)param;
    fib[0] = 0;
    fib[1] = 1;
    for(int j=2;j<*id;j++)
        fib[j] = fib[j-1] + fib[j-2];
}
int main(){
    pthread_t thread;
    int i;
    printf("Enter number of fibbonaci sequence : ");
    scanf("%d", &i);
    pthread_create(&thread, 0, &child_thread, (void*)&i);
    pthread_join(thread,0);
    printf("Fibonacci sequence generated - \n");
    for(int j=0;j<i;j++){
        printf("%d ", fib[j]);
    }
    printf("\n");
}
