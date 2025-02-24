#ifdef __linux__
#include <unistd.h>
#include <sys/signal.h>
#endif
#include <ucontext.h>
#include <iostream>
#include <assert.h>
#include <functional>

#define STACK_SIZE 8192
ucontext_t mainctx, ucp1, ucp2;  //TODO: How to make these ucontext_ts not global and easy to switch?
bool isstop = false;

void cancel_fun(int sig_num){
    std::cout << "SIGNAL: SIGINT is triggered" << std::endl;
    isstop = true;
}

void print1(){  //TODO: How to send parameters to this function? How to get return value;
    std::cout << "Print:" << 1.1 << std::endl;
    swapcontext(&ucp1, &mainctx);
    std::cout << "Print:" << 1.2 << std::endl;
}

void print2(){
    std::cout << "Print:" << 2.1 << std::endl;
    swapcontext(&ucp2, &mainctx);
    std::cout << "Print:" << 2.2 << std::endl;
}

int main(){
    struct sigaction sga; 
    sga.sa_flags = 0;
    sga.sa_handler = cancel_fun;
    sigemptyset(&sga.sa_mask);
    sigaction(SIGINT, &sga, nullptr);

    char* stack1 = (char *)malloc(sizeof(char) * STACK_SIZE);
    char* stack2 = (char *)malloc(sizeof(char) * STACK_SIZE);
    
    int i = 1;
    //register ucontexts
    getcontext(&ucp1);
    getcontext(&ucp2);

    ucp1.uc_stack.ss_flags = 0;
    ucp1.uc_link = &mainctx;
    ucp1.uc_stack.ss_size = STACK_SIZE;
    ucp1.uc_stack.ss_sp = stack1;
    makecontext(&ucp1, print1, 0);

    ucp2.uc_stack.ss_flags = 0;
    ucp2.uc_link = &mainctx;
    ucp2.uc_stack.ss_size = STACK_SIZE;
    ucp2.uc_stack.ss_sp = stack2;
    makecontext(&ucp2, print2, 0);

    // scheduler
    while(!isstop){
        std::cout << i << std::endl;
        swapcontext(&mainctx, i % 2 ? &ucp1: & ucp2);
        sleep(1);
        ++i;
    }
    return 0;   
}