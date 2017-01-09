#include <iostream>

using namespace std;
/*
编写一段程序，使用范围for语句将字符串内的所有字符串的所有字符用X代替
*/
int main()
{
    string a = "Hello world!";
    for(auto &c:a)
        c = 'X';
    cout << a << endl;
    return 0;
}
/*
XXXXXXXXXXXX

Process returned 0 (0x0)   execution time : 0.388 s
Press any key to continue.

*/
