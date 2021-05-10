#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//head


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    //just brutal enumerate
    for (int i = 1; i <= 1000; i ++)
        for (int j = 1; j <= i; j++)
            for (int k = 1; k <= j; k++)
                if (i + j + k == 1000 && j * j + k * k == i * i) {
                    cout << k << ' ' <<  j << ' ' << i << endl;
                    cout << k * j  * i << endl;
                    break;
                }

    return 0;
}
