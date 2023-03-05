def left(node):
    return 2 * node


def right(node):
    return 2 * node + 1


class SegmentTree:
    def __init__(self, max_size, values=None):
        self.root = 1
        self.ts = 0
        self.te = max_size - 1
        self.max_size = max_size
        self.tree = [0] * (4 * max_size)
        if values:
            self._build(values, self.root, self.ts, self.te)

    def _build(self, values, v, ts, te):
        if ts == te:
            self.tree[v] = values[ts]
        else:
            tm = (ts + te) // 2
            self._build(values, left(v), ts, tm)
            self._build(values, right(v), tm + 1, te)
            self.tree[v] = self.tree[left(v)] + self.tree[right(v)]

    def increase(self, index, by):
        self._update(index, by, self.root, self.ts, self.te, is_increase=True)

    def update(self, index, value):
        self._update(index, value, self.root, self.ts, self.te)

    def _update(self, index, value, v, ts, te, is_increase=False):
        if ts == te:
            self.tree[v] = value + self.tree[v] if is_increase else 0
        else:
            tm = (ts + te) // 2
            if tm >= index: 
                self._update(index, value, left(v), ts, tm)
            else:
                self._update(index, value, right(v), tm + 1, te)
            self.tree[v] = self.tree[left(v)] + self.tree[right(v)]

    def get(self, index):
        return self.range_sum(index, index)

    def range_sum(self, start, end):
        return self._range_sum(start, end, self.root, self.ts, self.te)

    def _range_sum(self, start, end, v, ts, te):
        if start > end:
            return 0
        if ts == start and te == end:
            return self.tree[v]
        else:
            tm = (ts + te) // 2
            return self._range_sum(start, min(tm, end), left(v), ts, tm)\
                    + self._range_sum(max(start, tm + 1), end, right(v), tm + 1, te)