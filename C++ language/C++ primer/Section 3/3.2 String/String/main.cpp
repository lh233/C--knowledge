#include <iostream>
//#include <string>

using namespace std;
//using std::string;
//int main()
//{
////    string s1 = "helloS world";
//    string s1, s2;
//    cin >> s1 >> s2;
//    cout << s1 << endl << s2 << endl;
//    return 0;
//}
/*
运行结果：
    HE   HF
HE
HF

Process returned 0 (0x0)   execution time : 7.067 s
Press any key to continue.

*/



int main()
{
    string line;
    while(getline(cin, line))
        if(line.size() > 10)
        cout << line << endl;
    return 0;
}
/*
运行结果：
321564654 13212313
321564654 13212313


2313131
312312312
3132132132
32132123132231312313213
32132123132231312313213
1321321313132131313211
1321321313132131313211
111
3213214556
22112
.32132131213131
.32132131213131

*/
