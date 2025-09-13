#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

vector<bool> sieve(int n);
long long extgcd(long long a, long long b, long long &x, long long &y);
long long inv_mod_coprime(long long a, long long m);
pair<long long,long long> crt_pairwise_coprime(const vector<long long>& r, const vector<long long>& mod);

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

long long extgcd(long long a, long long b, long long &x, long long &y){
    if(b == 0){ x = (a>=0?1:-1); y = 0; return llabs(a); }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long inv_mod_coprime(long long a, long long m){
    long long x, y;
    long long g = extgcd(a, m, x, y);
    if(g != 1) return -1;
    x %= m; if(x < 0) x += m;
    return x;
}

pair<long long,long long> crt_pairwise_coprime(const vector<long long>& r,
                                               const vector<long long>& mod){
    long long N = 1;
    for(long long m : mod) N *= m;

    long long x = 0;
    for(size_t i=0;i<mod.size();++i){
        long long Mi  = N / mod[i];
        long long inv = inv_mod_coprime(Mi % mod[i], mod[i]); 
        long long term = ( ( (r[i] % N) * (Mi % N) ) % N );    
        term = (term * (inv % N)) % N;
        x = (x + term) % N;
    }
    if(x < 0) x += N;
    return {x, N};
}

int main(){
    int m;

    vector<long long> thuong = {2, 3, 4};
    vector<long long> mod = {3, 5, 7}; 
    cout<< "Giai: \n";
    for (size_t i = 0; i < thuong.size(); ++i){
        cout << "x ≡ " << thuong[i] << " (mod " << mod[i] << ")\n";
    }
    auto ans = crt_pairwise_coprime(thuong, mod);
    cout << "Ket qua: x = " << ans.first << " (mod " << ans.second << ") => "
         << "x = " << ans.first << " + " << ans.second << " * k\n";

    cout<<"Liet ke cac so nguyen to trong khoang tu [100,m] voi m > = 500"<<endl;
    cout<<"------------"<<endl;
    cout << "Nhap m : ";
    cin >>m;
    vector<bool> prime = sieve(m);
    int count = 0;
    cout <<"Cac so nguyen to tu " << 100 << " toi " << m << " la : ";
    for (int i = 100; i <= m; i++){
        if (prime[i]){
            count++;
            cout << i << " ";
        }
    }
    cout << "\nSo luong so nguyen to trong khoang tu [100," << m << "] la : " << count << endl;
}