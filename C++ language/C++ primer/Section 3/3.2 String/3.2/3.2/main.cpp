#include <iostream>

using namespace std;


/*
编写一段程序从标准输入中一次读入一整行，然后修改该程序使其一次读入一个词
*/
int main()
{
    string a;
    while(getline(cin, a))
        cout << a << endl;
    return 0;
}
