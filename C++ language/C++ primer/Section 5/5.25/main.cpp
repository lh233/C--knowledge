#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    int c1=0, c2=0;

    while(std::cin >> c1 >> c2)
    {
        try{
            if(0 == c2)
                throw runtime_error("The c2 couldn't be zero!");
            cout << c1/c2 << endl;
        }catch(runtime_error err){
            cout << err.what() << "\nTry Again? Enter y or n" << endl;
            char c;
            cin >> c;
            if(!cin || c=='n')
                break;
        }
    }


    return 0;
}
