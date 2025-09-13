#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

long long ipowll(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

void factorize(long long x, long long p[], int e[], int &m) {
    m = 0;
    for (long long d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            p[m] = d;
            e[m] = 0;
            while (x % d == 0) {
                x /= d;
                ++e[m];
            }
            ++m;
        }
    }
    if (x > 1) {
        p[m] = x;
        e[m] = 1;
        ++m;
    }
}

long long divisor_count(const int e[], int m) {
    long long t = 1;
    for (int i = 0; i < m; ++i) t *= (long long)(e[i] + 1);
    return t;
}

long long divisor_sum(const long long p[], const int e[], int m) {
    long long s = 1;
    for (int i = 0; i < m; ++i) {
        long long term = 1, cur = 1;
        for (int k = 0; k < e[i]; ++k) {
            cur *= p[i];
            term += cur;
        }
        s *= term;
    }
    return s;
}

long long n_from_pf(const long long p[], const int e[], int m) {
    long long v = 1;
    for (int i = 0; i < m; ++i)
        for (int k = 0; k < e[i]; ++k)
            v *= p[i];
    return v;
}

long long divisor_product(const long long p[], const int e[], int m) {
    long long d = divisor_count(e, m);
    long long n = n_from_pf(p, e, m);
    long long half = d / 2;
    long long base = ipowll(n, half);
    if (d % 2 == 0) return base;
    long long rt = (long long)(sqrt((long double)n) + 0.5L);
    return base * rt;
}

void gen_divs(int idx, long long cur, const long long p[], const int e[], int m, long long out[], int &pos) {
    if (idx == m) {
        out[pos++] = cur;
        return;
    }
    long long val = 1;
    for (int k = 0; k <= e[idx]; ++k) {
        gen_divs(idx + 1, cur * val, p, e, m, out, pos);
        val *= p[idx];
    }
}

int cmp_ll(const void* a, const void* b) {
    long long x = *(const long long*)a;
    long long y = *(const long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

bool perfect(long long x) {
    long long p[64]; int e[64]; int m = 0;
    factorize(x, p, e, m);
    long long s = divisor_sum(p, e, m) - x;
    return s == x;
}

int pi_exact(int n) {
    if (n < 2) return 0;
    bool* prime = new bool[n + 1];
    for (int i = 0; i <= n; ++i) prime[i] = true;
    prime[0] = false; prime[1] = false;
    for (int i = 2; (long long)i * i <= n; ++i)
        if (prime[i])
            for (long long j = 1LL * i * i; j <= n; j += i)
                prime[(int)j] = false;
    int cnt = 0;
    for (int i = 2; i <= n; ++i) if (prime[i]) ++cnt;
    delete[] prime;
    return cnt;
}

int main() {
    long long x;
    cout << "Nhap so nguyen n (>1): ";
    cin >> x;

    long long p[64]; int e[64]; int m = 0;
    factorize(x, p, e, m);

    cout << "\nBai 1: Phan tich thua so nguyen to:\n";
    for (int i = 0; i < m; ++i) cout << p[i] << "^" << e[i] << " ";
    cout << "\n";

    long long dcnt = divisor_count(e, m);
    long long* divs = new long long[dcnt];
    int pos = 0;
    gen_divs(0, 1, p, e, m, divs, pos);
    qsort(divs, (size_t)dcnt, sizeof(long long), cmp_ll);
    cout << "Cac uoc so: ";
    for (long long i = 0; i < dcnt; ++i) cout << divs[i] << " ";
    cout << "\n";

    cout << "\nBai 2: So luong uoc so: " << dcnt << "\n";
    cout << "Bai 3: Tong cac uoc so: " << divisor_sum(p, e, m) << "\n";
    cout << "Bai 4: Tich cac uoc so: " << divisor_product(p, e, m) << "\n";
    cout << "Bai 5: " << x << (perfect(x) ? " la so hoan hao\n" : " khong phai so hoan hao\n");

    cout << "\nBai 6:\n";
    int upto = (x > 2147483647LL) ? 2147483647 : (int)x;
    int pie = pi_exact(upto);
    double est = (x > 1) ? (double)x / log((double)x) : 0.0;
    cout << "So luong so nguyen to <= " << x << ": " << pie << "\n";
    cout << "Uoc luong theo n/ln(n): " << est << "\n";

    delete[] divs;
    return 0;
}
