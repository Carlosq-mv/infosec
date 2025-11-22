#include <iostream>
#include <cassert>

using namespace std;

using int64 = long long;

int64 EEA(int64 a, int64 b, int64& x, int64 &y);
int64 get_pk(int64 p, int64 q, int64 e);

int main()
{
    int64 p, q, e;
    cout << "Enter a value for p: ";
    cin >> p;

    cout << "Enter a value for q: ";
    cin >> q;

    cout << "Enter a value for e: ";
    cin >> e;

    int64 pk = get_pk(p, q, e);
    assert(pk != -1);

    cout << "\nSmallest possible value for d: " << pk;

    return 0;
}
// a*x + b*y = gcd(a, b)
// where a = e and b = phi(N)
int64 EEA(int64 a, int64 b, int64 &x, int64 &y)
{
    // From: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b; // gcd(0,b) = b
    }

    int64 x1, y1;
    int64 gcd = EEA(b % a, a, x1, y1);

    // update x and y
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

// calculate d = e^-1 mod (phi(N))
int64 get_pk(int64 p, int64 q, int64 e)
{
    // Get N (eulers totient function)
    int64 N = (p - 1) * (q - 1);
    int64 d_temp, y_temp;

    // Use EEA to solve e*d_temp + b*y_temp = gcd(e, phi(N))
    int64 gcd_val = EEA(e, N, d_temp, y_temp);

    // Make sure e is coprime with phi(N)
    if(gcd_val != 1) {
        return -1;
    }

    int64 d = d_temp;

    // Make sure d in range [0, phi(N) - 1] and positive
    d = d % N;
    if(d < 0) {
        d += N;
    }
    return d;
}