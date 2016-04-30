#include <complex>
#include <vector>
using namespace std;

const double PI = 3.141592654;
typedef complex<double> Complex;

void _fft(vector<Complex>& buf, vector<Complex>& out,
	int st, int step, bool isInv) {

	if (step >= buf.size()) return;

	_fft(out, buf, st, step * 2, isInv);
	_fft(out, buf, st + step, step * 2, isInv);

	int n = buf.size();
	double c = isInv ? 1.0 : -1.0;
	for (int i = 0; i < n; i += 2 * step) {
		Complex t = polar(1.0, c * 2 * PI * i / n) * out[i + step + st];
		buf[i / 2 + st] = out[i + st] + t;
		buf[(i + n) / 2 + st] = out[i + st] - t;
	}
}

void fft(vector<Complex> &x, bool isInv) {
	int n = x.size(), nxt2 = 0;
	for (int i = 0, mask = 1; i < 31; i++, mask <<= 1)
		nxt2 = (n&mask) ? (n != mask) ? 1 << (i + 1) : 1 << i : nxt2;
	n = nxt2;
	while (x.size() < n)
		x.push_back(0);

	vector<Complex> out = x;
	_fft(x, out, 0, 1, isInv);
	for (int i = 0; isInv && i < x.size(); i++)
		x[i] /= n;
}
