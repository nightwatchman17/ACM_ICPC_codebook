vector<int> btwEncode(const vector<int> &src) {
    // O(n*lgn*lgn). probably faster than O(n*lgn) version
    int len = src.size();
    vector<int> sa(len), rank(len);
    for(int i=0; i<len; ++i) rank[sa[i] = i] = src[i];
    for(int ll=1, cnt=0; cnt!=len; ll<<=1, cnt=rank[sa.back()]+1) {
        auto cmp = [&](const int l, const int r) {
            if( rank[l]!=rank[r] ) return rank[l] < rank[r];
            return rank[(l+ll)%len] < rank[(r+ll)%len];
        };
        sort(sa.begin(), sa.end(), cmp);
        vector<int> tmp = rank;
        tmp[sa[0]] = 0;
        for(int i=1; i<sa.size(); ++i)
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);
        rank = tmp;
    }
    vector<int> rst(len);
    for(int i=0; i<len; ++i) rst[i] = src[(sa[i]+len-1)%len];
    return rst;
}

vector<int> btwDecode(const vector<int> &rst) {
    int len = rst.size();
    vector<pair<int,int> > pre(len);
    for(int i=0; i<len; ++i) pre[i] = {rst[i], i};
    sort(pre.begin(), pre.end());
    vector<int> table(len);
    for(int i=0; i<len; ++i) table[pre[i].second] = i;
    vector<int> src(len);
    for(int i=rst.size()-1, idx=0; i>=0; --i, idx=table[idx])
        src[i] = rst[table[idx]];
    return src;
}
