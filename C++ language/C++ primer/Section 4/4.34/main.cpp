#include <iostream>

using namespace std;

int main()
{
    return 0;
}
/*
用命名的强制类型转换改写下列的旧式转换语句：
int i; double d; const string *ps; char *pc; void *pv;
(a) pv = (void*)ps;
(b) i = int(*pc)
(c)pv = &d (d)pc = (char*)pv

答：网络参考答案：
(a)pv=reinterpret_cast<void*>(ps)
(b)i=static_cast<int>(*pc)
(c) pv=reinterpret_cast<void*>(&d)
(d) pc=reinterpret_cast<char*>(pv)
*/
