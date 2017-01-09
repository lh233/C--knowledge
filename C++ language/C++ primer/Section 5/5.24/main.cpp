#include <iostream>
#include <stdexcept>
using namespace std;
/*修改你的程序，使得当第二个数是0时抛出异常，先不要设定catch语句，运行程序并真的为除数输入0*/
int main()
{
    int c1=0, c2=0;
    std::cin >> c1 >> c2;
    if(0 == c2)
        throw runtime_error("The c2 couldn't be zero!");
    std::cout << c1/c2;
    return 0;
}
/*
1 0
terminate called after throwing an instance of 'std::runtime_error'
  what():  The c2 couldn't be zero!

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.

Process returned 3 (0x3)   execution time : 8.440 s
Press any key to continue.

*/
