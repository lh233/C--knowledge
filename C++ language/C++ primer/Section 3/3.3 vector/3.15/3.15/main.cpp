#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string word;
    vector<string> text;
    int j=0;
    while(cin >> word)
    {
        text.push_back(word);
        cout << text[j] << "   ";
        j++;
    }
    return 0;
}
