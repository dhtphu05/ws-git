#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

vector<bool> sieve(int n){

    vector<bool> prime(n+1, true);

    prime[0] = prime[1] = false;

    for (int i = 2; i * i <= n; i++){
        if (prime[i] == true){
            for (int j = i * i; j <= n; j += i){
                prime[j] = false;
            }
        }
    }

    return prime;
}

vector<int> findPrimes(int n){
    vector<bool> prime = sieve(n);
    vector<int> res;
    for (int i = 2; i <= n; i++){
        if (prime[i]){
            res.push_back(i);
        }
    }
    return res;
}

void printPrimes(vector<int> primes){
    for (auto ele : primes){
        cout << ele << " ";
    }
}

int gcd_basic(int a, int b){
    while  (a != b){
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}

int gcd(int a, int b){
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long lcm(int a, int b){
    return (a * b) / gcd(a, b);
}

vector<pair<int,int>> primeFactorization(int n){

    vector<pair<int,int>> res;

    for (int i = 2; i * i <= n; i++){
        int count = 0;
        while (n % i == 0){
            n /= i;
            count++;
        }
        if (count > 0){
            res.push_back({i, count});
        }
    }

    if (n > 1){
        res.push_back({n, 1});
    }

    return res;

}

int eulerTotientFunction(int n){
    vector<pair<int,int>> factors = primeFactorization(n);
    int phi = 1;
    for (size_t i = 0; i< factors.size(); i++){
        phi *= pow(factors[i].first, factors[i].second- 1) * (factors[i].first - 1);
    }
    return phi;
}

bool isPrime(int n){
    return (eulerTotientFunction(n) == n - 1);
}

bool isCoPrime(int a, int b){
    if (gcd(a,b) == 1) return true;
    return false;
}

void displayCoPrime(int n){
    for (int i = 1; i < n; i++){
        if (isCoPrime(i, n)){
            cout << i << " ";
        }
    }
}

bool check_add(int x, int y, int m){
    return ((x + y) % m)  == ((x % m + y % m) % m);     
}

bool check_sub(int x, int y, int m){
    return ((x - y) % m) == ((x % m - y % m) % m);
}

bool check_mul(int x, int y, int m){
    return ((x * y) % m) == ((x % m * y % m) % m);
}

int modpow(int x, int n, int m){
    if (n == 0) return 1 % m;
    long long u = modpow(x, n / 2, m);
    u = u * u % m;
    if (n % 2 == 1) u = u * x % m;
    return u;
}

bool check_pow(int x, int n, int m){
    return modpow(x, n, m) == modpow((x % m), n, m);
}

int modularInverse(int x, int m){
    if ((gcd(x, m) != 1) || !isPrime(m)){
        return -1;
    }
    else{
        return modpow(x, m - 2, m);
    }
    
}

int main(){

    int n, a, b, p, q, x, y, m;

    cout << "Enter a positive number: ";
    cin >> n;
    cout << "\n";

    vector<int>res = findPrimes(n);

    cout <<"Primes from 1 to " << n << " are: ";
    printPrimes(res);
    cout << "\n\n";


    cout << "Enter two numbers a and b: ";
    cin >> a >> b;
    vector<bool> prime = sieve(b);
    cout <<"Primes from " << a << " to " << b << " are: ";
    for (int i = a; i <= b; i++){
        if (prime[i]){
            cout << i << " ";
        }
    }
    cout << "\n\n";

    cout << "Enter two numbers p and q: ";
    cin >> p >> q;
    cout << "GCD(" << p << ", " << q << ") = "<< gcd_basic(p, q) << endl; 
    cout << "GCD(" << p << ", " << q << ") = "<< gcd(p, q) << endl;
    cout << "LCM(" << p << ", " << q << ") = " << lcm(p, q);
    cout << "\n\n";

    cout << "Euler's Totient Function of " << n << " is: " << eulerTotientFunction(n) << endl;
    cout << n << " is" << (isPrime(n)? " a prime number" : " not a prime number") << endl; 

    cout << "The numbers that are coprime with " << n << " are: " << endl;
    displayCoPrime(n);
    cout << "\n\n";

    cout <<"Check Modular Arithmetic: " << endl;
    cout << "Enter x, y, n, m: ";
    cin >> x >> y >> n >> m;
    cout << "Check (x + y) mod m: " << ((check_add(x, y, m) ? "True" : "False")) << endl;
    cout << "Check (x - y) mod m: " << ((check_sub(x, y, m) ? "True" : "False")) << endl;
    cout << "Check (x * y) mod m: " << ((check_mul(x, y, m) ? "True" : "False")) << endl;
    cout << "Check x^n mod m: " << ((check_pow(x, n, m) ? "True" : "False")) << endl;
    cout << "\n\n";

    cout << "Modular Exponentiation: " << endl;
    cout << "Enter x, n, m: ";
    cin >> x >> n >> m;
    cout << "Result of " << x << "^" << n << " mod " << m << " is: " << modpow(x, n, m) << endl;
    cout << "\n\n";

    cout << "Enter x, m to find modular inverse: ";
    cin >> x >> m;
    int inv = modularInverse(x, m);
    if (inv == -1){
        cout << "Modular inverse does not exist." << endl;
    }
    else{
        cout << "Modular inverse of " << x << " mod " << m << " is: " << inv << endl;
    }
    cout << "\n\n";

}
