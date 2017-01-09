#include <iostream>
#include <vector>
#include <string>
using namespace std;

//int main()
//{
//    string word={0};
//    vector<string> p;
////    while(cin >> word)
////    {
////        p.push_back(word);
////    }
//    while(cin >> word)
//        p.push_back(word);
//    for(auto c:p)
//    {
//        for(auto &ch:c)
//        {
//            ch = toupper(ch);
//        }
//    }
//
//
//
//
//    return 0;
//}


int main()
{
    string word;
    vector<string> Str;
    while(cin>>word)
        Str.push_back(word);
    for(auto c:Str)
    {
         cout<<c<<" ";
         for(auto &ch:c)
            ch=toupper(ch);
         cout<<c<<endl;
    }
    cout<<endl;
    return 0;
}
/*
都说在windows下输入ctrl+Z即退出。

其实在Vc++ 6.0控制台模式下，ctrl+Z显示的是^z，当然^z在Vc中模拟文件尾（EOF）。

wrhieoh
hadohfjfh
^Z
wrhieoh WRHIEOH
hadohfjfh HADOHFJFH


Process returned 0 (0x0)   execution time : 9.989 s
Press any key to continue.

*/
