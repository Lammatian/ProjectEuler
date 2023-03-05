#include "segment_tree.h"

#include <cmath>
#include <iostream>

SegmentTree::SegmentTree(size_t size) : mSize(size), mTree(4*size)
{
}

SegmentTree::SegmentTree(const std::vector<ll>& values, size_t size) : mSize(size), mTree(4*size)
{
    _build(values, mRoot, 0, size - 1);
}

void SegmentTree::_build(const std::vector<ll>& values, size_t v, size_t ts, size_t te)
{
    if (ts == te)
        mTree[v] = values[ts];
    else
    {
        size_t tm = (ts + te) / 2;
        _build(values, left(v), ts, tm);
        _build(values, right(v), tm + 1, te);
        mTree[v] = mTree[left(v)] + mTree[right(v)];
    }
}

ll SegmentTree::get(size_t index)
{
    return _range_sum(index, index, mRoot, 0, mSize - 1);
}

void SegmentTree::update(size_t index, ll value, bool isIncrease)
{
    _update(index, value, mRoot, 0, mSize - 1, isIncrease);
}

void SegmentTree::_update(size_t index,
        ll value,
        size_t v,
        size_t ts,
        size_t te,
        bool isIncrease)
{
    if (ts == te)
    {
        mTree[v] = value + (isIncrease ? mTree[v] : 0);
    }
    else
    {
        size_t tm = (ts + te) / 2;
        if (index <= tm)
        {
            _update(index, value, left(v), ts, tm, isIncrease);
        }
        else
        {
            _update(index, value, right(v), tm + 1, te, isIncrease);
        }
        mTree[v] = mTree[left(v)] + mTree[right(v)];
    }
}

ll SegmentTree::range_sum(size_t start, size_t end)
{
    return _range_sum(start, end, mRoot, 0, mSize - 1);
}

ll SegmentTree::_range_sum(size_t start, size_t end, size_t v, size_t ts, size_t te)
{
    if (start > end)
        return 0;
    if (start == ts && end == te)
        return mTree[v];
    size_t tm = (ts + te) / 2;
    return _range_sum(start, std::min(end, tm), left(v), ts, tm) +
            _range_sum(std::max(start, tm + 1), end, right(v), tm + 1, te);
}