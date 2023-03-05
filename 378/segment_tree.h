#include <vector>

using ll = __int128;

class SegmentTree
{
    std::vector<ll> mTree;
    size_t mSize;
    size_t mRoot{1};

public:
    SegmentTree(size_t max);
    SegmentTree(const std::vector<ll>& values, size_t max);
    void update(size_t index, ll value, bool isIncrease=false);
    ll get(size_t index);
    ll range_sum(size_t start, size_t end);

private:
    void _build(const std::vector<ll>& values, size_t v, size_t ts, size_t te);
    void _update(size_t index, ll value, size_t v, size_t s, size_t e, bool isIncrease=false);
    ll _range_sum(size_t start, size_t end, size_t v, size_t ts, size_t te);
    inline static size_t left(size_t v) { return 2 * v; }
    inline static size_t right(size_t v) { return 2 * v + 1; }
};