/* Author	: Jehian Norman Saviero (@Reiva5) */
#include <bits/stdc++.h>
#include "BigNumber.h"
/* MACROS SAMPAH */
#define jehian using
#define mau namespace
#define libur std
#define cepet {ios_base::sync_with_stdio(0);cin.tie(NULL);}

jehian mau libur;
/* MACROS FOR TYPE */
typedef long l;
typedef long double ld;
typedef long long ll;
typedef unsigned long ul;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<l> vl;
typedef vector<ll> vll;
typedef pair<int, int> pi;
typedef pair<l,l> pl;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;

/* MACROS FOR PRINT */
#define nl printf("\n");
#define sp printf(" ");

/* MACROS FOR FUNCTION */
#define pb push_back
#define mp make_pair
#define eb emplace_back

int main(){
	BigNumber A, B;
	cin >> A >> B;
	BigNumber Z(0), C = Z;
	C += A;
	cout << C << endl;
	C = 100000;
	cout << C << endl;
	cout << A + B << endl;
	cout << A - B << endl;
	cout << A * B << endl;
	return 0;
}