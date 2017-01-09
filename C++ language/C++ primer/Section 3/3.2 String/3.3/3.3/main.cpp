#include <iostream>

using namespace std;
/*
比较两个字符串，比较其是否相等并输出结果。如果不相等，输出较大的那个字符串。

*/
int main()
{
    string a;
    string b;
    cin >> a >> b;
    if(a != b)
    {
        cout << "较大的一个数是："<< endl;
        cout << (a.size() > b.size()? a:b) << endl;
    }
    cout << a << endl << b << endl;
    return 0;
}
/*
运行结果：
123456 1234
较大的一个数是：
123456
123456
1234

Process returned 0 (0x0)   execution time : 5.023 s
Press any key to continue.

*/
