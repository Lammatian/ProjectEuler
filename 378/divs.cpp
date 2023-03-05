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
ll MOD = 1'000'000'000'000'000'000;
vector<ll> divs(N + 1);
vector<ll> smallest_prime(N + 1);

ll triangle_divs(ll n)
{
    if (n % 2 == 0) return divs[n / 2] * divs[n + 1];
    else return divs[n] * divs[(n + 1) / 2];
}

int main()
{
    divs[1] = 1;
    ll result = 0;
    // We need to calculate #divs for up to N + 1 to use triangle_divs
    for (ll i = 2; i <= N + 1; ++i)
    {
        if (smallest_prime[i] == 0)
        {
            // Prime
            divs[i] = 2;
            
            for (ll j = i * i; j <= N + 1; j += i)
            {
                if (smallest_prime[j] == 0)
                {
                    smallest_prime[j] = i;
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

    ll max_tri_div = 1;
    for (ll i = 1; i <= N; ++i)
    {
        max_tri_div = max(max_tri_div, triangle_divs(i));
    }

    // i -> count of triangle numbers with i divisors
    SegmentTree div_counts(max_tri_div + 1);
    // i -> count of triangle numbers k with k < i but dT(k) > dT(i)
    SegmentTree pairs(max_tri_div + 1);
    for (ll i = 1; i <= N; ++i)
    {
        div_counts.update(triangle_divs(i), 1, true);
        ll bigger_divs = div_counts.range_sum(triangle_divs(i) + 1, max_tri_div);
        pairs.update(triangle_divs(i), bigger_divs, true);
        ll new_triples = pairs.range_sum(triangle_divs(i) + 1, max_tri_div) % MOD;
        result = (result + new_triples) % MOD;
    }

    cout << (long long)result << "\n";

    return 0;
}
