#include <iostream>

using namespace std;
int main(int argc, char ** argv){
    if(argc != 2){
        cout << "use help like this: gchelp -l" << endl;
        cout << "   -l: the help of LOGGER" << endl;
        exit(EXIT_FAILURE);
    }
    std::string arg = argv[1];
    if(arg.length() < 2 || arg[0] != '-'){
#ifdef _WIN32
        cout << "use gchelp like this: .\\gchelp.exe -l" << endl;
#elif __linux__
        cout << "use gchelp like this: ./gchelp -l" << endl;
#endif
        cout << "   -l: the help of LOGGER" << endl;
        exit(EXIT_FAILURE);
    }
    switch (arg[1])
    {
    case 'l':
        cout << "The pattern of loggers is defined by %" << endl;
        cout << "   %s: The actually message" << endl;
        cout << "   %y: The year" << endl;
        cout << "   %m: The month" << endl;
        cout << "   %d: The day" << endl;
        cout << "   %h: The hour" << endl;
        cout << "   %i: The minute" << endl;
        cout << "   %e: The second" << endl;
        cout << "   %l: The message level" << endl;
        cout << "   %s: The source file" << endl;
        cout << "   %f: The function called" << endl;
        cout << "   %n: The line-number in the source file" << endl;
        cout << "   %t: The thread_id" << endl;
        break;
    
    default:
        break;
    }

    return 0;
}