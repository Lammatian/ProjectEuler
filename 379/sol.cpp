#include <iostream>
using namespace std;
using ll = long long;

int main()
{
    ll result = 0;
    for (int i = 1; i <= (1 << 30); ++i)
    {
        if (i % 100000 == 0) cout << i << "\n";
        if ((i ^ (2 * i) ^ (3 * i)) == 0) result++;
    }
    cout << result << "\n";
    return 0;
}