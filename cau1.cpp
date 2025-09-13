#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

void factorize(long long x, long long p[], int e[], int &m);
long long divisor_count(const int e[], int m);
void gen_divs(int idx, long long cur, const long long p[], const int e[], int m, long long out[], int &pos);
int cmp_ll(const void *a, const void *b);
bool isPrimeLL(long long n);
long long prevPrimeLL(long long n);
long long nextPrimeLL(long long n);

void factorize(long long x, long long p[], int e[], int &m)
{
    m = 0;
    for (long long d = 2; d * d <= x; ++d)
    {
        if (x % d == 0)
        {
            p[m] = d;
            e[m] = 0;
            while (x % d == 0)
            {
                x /= d;
                ++e[m];
            }
            ++m;
        }
    }
    if (x > 1)
    {
        p[m] = x;
        e[m] = 1;
        ++m;
    }
}

long long divisor_count(const int e[], int m)
{
    long long t = 1;
    for (int i = 0; i < m; ++i)
        t *= (long long)(e[i] + 1);
    return t;
}

void gen_divs(int idx, long long cur, const long long p[], const int e[], int m, long long out[], int &pos)
{
    if (idx == m)
    {
        out[pos++] = cur;
        return;
    }
    long long val = 1;
    for (int k = 0; k <= e[idx]; ++k)
    {
        gen_divs(idx + 1, cur * val, p, e, m, out, pos);
        val *= p[idx];
    }
}

int cmp_ll(const void *a, const void *b)
{
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

bool isPrimeLL(long long n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (long long d = 3; d * d <= n; d += 2)
        if (n % d == 0)
            return false;
    return true;
}

long long prevPrimeLL(long long n)
{
    long long c = n - 1;
    if (c < 2)
        return -1;
    if (c % 2 == 0)
        --c;
    for (; c >= 3; c -= 2)
        if (isPrimeLL(c))
            return c;
    return 2;
}

long long nextPrimeLL(long long n)
{
    long long c = n + 1;
    if (c <= 2)
        return 2;
    if (c % 2 == 0)
        ++c;
    for (;; c += 2)
    {
        if (isPrimeLL(c))
            return c;
        if (c < 0)
            return -1;
    }
}

int main()
{
    long long x;
    cout << "Nhap so nguyen n (>1): ";
    cin >> x;

    long long p[64];
    int e[64];
    int m = 0;
    factorize(x, p, e, m);

    cout << "\n Phan tich thua so nguyen to:\n";
    for (int i = 0; i < m; ++i)
        cout << p[i] << "^" << e[i] << " ";
    cout << "\n";

    long long dcnt = divisor_count(e, m);

    long long *divs = new long long[dcnt];
    int pos = 0;
    gen_divs(0, 1, p, e, m, divs, pos);
    qsort(divs, (size_t)dcnt, sizeof(long long), cmp_ll);
    cout << "Cac uoc so: ";
    for (long long i = 0; i < dcnt; ++i)
        cout << divs[i] << " ";
    cout << "\n";
    long long mPrime = p[m - 1];
    cout << "Uoc so nguyen to lon nhat cua n la m = " << mPrime << "\n";
    long long below = prevPrimeLL(mPrime);
    long long above = nextPrimeLL(mPrime);

    long long bestBelow = (below == -1) ? LLONG_MAX : (mPrime - below);
    long long bestAbove = (above == -1) ? LLONG_MAX : (above - mPrime);

    if (bestBelow < bestAbove)
    {
        cout << "So nguyen to gan m nhat: " << below << " (be hon m)\n";
    }
    else if (bestAbove < bestBelow)
    {
        cout << "So nguyen to gan m nhat: " << above << " (lon hon m)\n";
    }
    else
    {
        if (bestBelow == LLONG_MAX)
        {
            cout << "Khong tim duoc so nguyen to gan m.\n";
        }
        else
        {
            cout << "Hai so nguyen to gan m nhat (cach deu): "
                 << below << " va " << above << "\n";
        }
    }
    delete[] divs;
    return 0;
}