const double PI = acos(-1.0);
typedef complex<double> Complex;

void _fft(const Complex *in, Complex *out, const vector<Complex> &pls, int step, int size, double dir) {
    if(size < 1) return;
    if(size == 1) {
        out[0] = in[0];
        return;
    }
    _fft(in, out, pls, step * 2, size / 2, dir);
    _fft(in + step, out + size / 2, pls, step * 2, size / 2, dir);
    for(int i = 0; i < size / 2; ++i) {
        Complex even = out[i];
        Complex odd = out[i + size / 2];
        out[i] = even + pls[i * step] * odd;
        out[i + size / 2] = even + pls[(i + size / 2) * step] * odd;
    }
}

// x.size() must be 2^m
vector<Complex> fft(const vector<Complex> &x, bool isInv) {
    int n = x.size();
    double dir = isInv ? -1. : 1.;
    vector<Complex> pls(n);
    for(int i=0; i<n; ++i)
        pls[i] = polar(1.0, dir * 2 * PI * i / n);

    vector<Complex> out = x;
    _fft(&x[0], &out[0], pls, 1, n, dir);
    for(int i = 0; isInv && i < x.size(); i++)
        out[i] /= n;
    return out;
}
