#include <iostream>
#include <vector>
using namespace std;
/*
编写一段程序，创建一个含有10个整数的vector对象，然后使用迭代器将所有元素的值变成原来的两倍
*/
int main()
{
    vector<int> v1(10, 30);
    for(auto a=v1.begin(); a!=v1.end(); a++)
    {
        cout << (*a) << '\t';
        (*a) = (*a)*2;
    }

    for(auto a=v1.begin(); a!=v1.end(); a++)
    {
        cout << (*a) << '\t';
    }
    return 0;
}
