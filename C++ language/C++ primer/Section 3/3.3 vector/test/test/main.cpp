#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<int>> ph;

    vector<int> p;
    p.push_back(1);
    p.push_back(2);
    p.push_back(3);
    p.push_back(4);

    for(int i=0; i<p.size(); i++)
    {
        cout << p[i] << '\t';
    }

    vector<int> q;
    q.push_back(5);
    q.push_back(6);
    q.push_back(7);
    q.push_back(8);

    for(int i=0; i<q.size(); i++)
    {
        cout << q[i] << '\t';
    }

    ph.push_back(p);
    ph.push_back(q);

    for(vector< vector<int> >::size_type u = 0; u < ph.size(); u++)
    {
        for(vector<int>::size_type v = 0; v < ph[u].size(); v++)
        {
            cout << ph[u][v] << " ";
        }
        cout << endl;
    }
    return 0;
}
