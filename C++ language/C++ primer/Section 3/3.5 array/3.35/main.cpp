#include <iostream>

using namespace std;

int main()
{
    int a[5] = {0, 1, 2, 3, 4};
    for(int i=0; i<5; i++)
    {
        cout << a[i] << endl;
    }
    int *p = a;
    for(int i=0; i<5; i++)
    {
        p[i] = 0;
    }
    for(int i=0; i<5; i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}
