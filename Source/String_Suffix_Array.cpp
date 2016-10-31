vector<int> buildSuffixArray(const vector<int> &str) {
    // sa: i -> start position of str
    // O(n*lgn*lgn). probably faster than O(n*lgn) version
    int len = str.size();
    vector<int> sa(len+1), rank(len+1);
    for(int i=0; i<len; ++i) rank[sa[i] = i] = str[i];
    rank[sa.back() = len] = -1;
    for(int ll=1, cnt=0; cnt!=len; ll<<=1, cnt=rank[sa.back()]) {
        auto cmp = [&](const int l, const int r) {
            if( rank[l]!=rank[r] ) return rank[l] < rank[r];
            int lv = (l+ll < len) ? rank[l+ll] : 0;
            int rv = (r+ll < len) ? rank[r+ll] : 0;
            return lv < rv;
        };
        sort(sa.begin(), sa.end(), cmp);
        vector<int> tmp = rank;
        tmp[sa[0]] = 0;
        for(int i=1; i<sa.size(); ++i)
            tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);
        rank = tmp;
    }
    return sa;
}

vector<int> buildLcp(const vector<int> &str, const vector<int> &sa) {
    // lcp: longest common prefix for sa[i-1] sa[i]
    int len = sa.size();
    vector<int> lcp(len, 0), idx(len);
    for(int i=0; i<len; ++i) idx[sa[i]] = i;
    for(int i=0, l=0; i<len; ++i) {
        if( idx[i] == 0 ) {
            l = 0;
            continue;
        }
        int j = sa[idx[i]-1];
        while( i+l<len && j+l<len && str[i+l]==str[j+l] )
            ++l;
        lcp[idx[i]] = l;
        l -= l>0;
    }
    return lcp;
}

pair<int,int> longestRepeatedSubstring(const vector<int> &sa, const vector<int> &lcp, int k) {
    // longest repeated substring who occurs at least k times
    // return <longest length, start position>
    pair<int,int> ret = {-1, -1};
    if( k<=1 ) {
        for(int i=0; i<sa.size(); ++i)
            if( sa[i]==0 ) return {sa.size()-1, i};
    }
    if( lcp.size() < k ) return ret;
    deque<pair<int,int>> dq;
    auto maintain = [&](pair<int,int> v) {
        while( dq.size() && dq.front().second <= v.second-(k-1) )
            dq.pop_front();
        while( dq.size() && dq.back() >= v )
            dq.pop_back();
        dq.push_back(v);
    };
    for(int i=0; i<k-2; ++i) maintain({lcp[i], i});
    for(int i=k-2; i<lcp.size(); ++i) {
        maintain({lcp[i], i});
        ret = max(ret, dq.front());
    }
    return ret;
}

pair<int,int> lcs(const vector<int> &s1, const vector<int> &s2, int e1, int e2) {
    // Longest Common "Substring" in O(n*lgn*lgn) n = s1+s2
    vector<int> arr(s1.size()+s2.size()+2);
    int idx = -1;
    for(int i=0; i<s1.size(); ++i) arr[++idx] = s1[i];
    arr[++idx] = e1;
    for(int i=0; i<s2.size(); ++i) arr[++idx] = s2[i];
    arr[++idx] = e2;
    vector<int> sa = buildSuffixArray(arr);
    vector<int> lcp = buildLcp(arr, sa);
    pair<int,int> ret = {-1, -1};
    for(int i=1; i<lcp.size(); ++i)
        if( (sa[i]<=s1.size()) ^ (sa[i-1]<=s1.size()) )
            ret = max(ret, {lcp[i], sa[i]});
    return ret;
}
