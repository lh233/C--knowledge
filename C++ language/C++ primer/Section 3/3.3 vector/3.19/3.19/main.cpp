#include <iostream>
#include <vector>
using namespace std;
/*
如果想定义一个含有10个元素的vector对象，所有元素的值都是42，请列举三种不同的实现方法
*/
int main()
{
    vector<int> p(10, 42);
    vector<int> p{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
    for(int i=0; i<10; i++)
    {
        p.push_back(10);
    }
//    for(int i=0; i<p.size(); i++)
//    {
//        cout << p[i] << "  ";
//    }
    return 0;
}
