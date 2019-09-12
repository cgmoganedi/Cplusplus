#include <iostream>

using namespace std;

// Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
int main(int argc, char* args[])
{
    unsigned short a[100], b[100], i;

    string mystr;

    cin >> mystr;
    for(i = 0; i < 50; ++i)
    {
        a[49 + i] = (int) mystr[i];
    }
    
    while (mystr != "end" ){
        cin >> mystr;
        for(i = 0; i < 50; ++i)
        {
            b[49 + i] = (int) mystr[i];
        }
        for(i = 99; i > 0; --i)
        {
            a[i] += b[i];
            if (a[i] < 10)
            {
                continue;
            }
            else
            {
                a[i] -= 10;
                a[i-i] += 1;
            }
        }
        while (i < 100)
        {
            cout << a[i] << " " << endl;
        }
    }
    
    cout<<"Hello Kelly"<<endl;
    return 0;
}