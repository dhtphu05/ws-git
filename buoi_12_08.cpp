#include <iostream>
#include <vector>
using namespace std;

vector<int> eratos(int n){
    vector<int> mangdanhdau(n,0);
    for(int i=2;i<n;i++){
        if(mangdanhdau[i])
        continue;
        else{
            for(int j=i*2;j<n;j+=i){
                mangdanhdau[j]=i;
            }
        }
    }
    vector<int> result;
    for(int i=2;i<n;i++){
        if(mangdanhdau[i]==0){
            result.push_back(i);
        }
    }
    return result;
}

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
long long lcm(int a, int b){
    return (long long)a * b / gcd(a,b);
}



int main(){


}