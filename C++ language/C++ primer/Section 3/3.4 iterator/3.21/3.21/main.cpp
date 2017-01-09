#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1(10, 1);
    for(auto a=v1.begin(); a!=v1.end(); a++)
    {
        cout << (*a) << endl;
    }
    return 0;
}
