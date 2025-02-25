#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include "./base/noncopyable.h"

using namespace std;
using namespace gc;

class Test: noncopyable{
public:
    Test(): noncopyable(){
        cout << "default constructor" << endl;
    }

    Test(const Test & other){
        cout << "copy constructor" << endl;
    }
};

int main(){
    Test t1;
    Test t2 = t1;
    Test t3(t1);

    return 0;
}