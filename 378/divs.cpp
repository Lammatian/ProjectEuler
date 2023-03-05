#include <iostream>
#include <cmath>
#include <vector>

#include "segment_tree.h"

using namespace std;
using ll = __int128;

ll num_divisors(ll n)
{
    int divs = 0;
    ll i = 1;
    for (; i * i < n; ++i)
    {
        if (n % i == 0) divs += 2;
    }

    if (i * i == n) divs += 1;
    return divs;
}

ll N = 60'000'000;
// ll N = 1000;
ll MOD = 1'000'000'000'000'000'000;
vector<ll> divs(N + 1);
vector<bool> parsed(N + 1);
vector<ll> smallest_prime(N + 1);

ll triangle_divs(ll n)
{
    if (n % 2 == 0) return divs[n / 2] * divs[n + 1];
    else return divs[n] * divs[(n + 1) / 2];
}

int main()
{
    // SegmentTree s({3, 2, 0, 1, 5, 1}, 6);
    // SegmentTree s(6); 
    // s.update(1, 3);
    // s.update(2, 2);
    // s.update(3, 0);
    // s.update(4, 1);
    // s.update(5, 5);
    // s.update(6, 1);
    // cout << s.range_sum(0, 5) << "\n";
    // cout << s.range_sum(0, 2) << "\n";
    // cout << s.range_sum(0, 3) << "\n";
    // cout << s.range_sum(4, 5) << "\n";
    // for (int i = 0; i < 14; ++i)
    // {
    //     cout << s.get(i) << " ";
    // }
    // cout << "\n";

    // return 0;
    SegmentTree div_counts(23041);
    SegmentTree pairs(23041);
    divs[1] = 1;
    ll result = 0;
    for (ll i = 2; i <= N + 1; ++i)
    {
        if (!parsed[i])
        {
            // Prime
            parsed[i] = true;
            divs[i] = 2;
            
            for (ll j = i * i; j <= N + 1; j += i)
            {
                if (smallest_prime[j] == 0)
                {
                    smallest_prime[j] = i;
                    parsed[j] = true;
                }
            }
        }
        else
        {
            ll p = smallest_prime[i];
            int alpha_p = 0;
            ll i_prime = i;
            while (i_prime % p == 0)
            {
                i_prime /= p;
                alpha_p += 1;
            }

            divs[i] = (alpha_p + 1) * divs[i_prime];
        }
    }

    for (ll i = 1; i <= N; ++i)
    {
        div_counts.update(triangle_divs(i), 1, true);
        ll bigger_divs = div_counts.range_sum(triangle_divs(i) + 1, 23040);
        pairs.update(triangle_divs(i), bigger_divs, true);
        ll new_triples = pairs.range_sum(triangle_divs(i) + 1, 23040) % MOD;
        result = (result + new_triples) % MOD;
    }

    cout << (long long)result << "\n";

    return 0;
}
