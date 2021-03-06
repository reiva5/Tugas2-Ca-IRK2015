/* Author	: Jehian Norman Saviero (@Reiva5) */
#include <bits/stdc++.h>
#include "RSA.h"

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

RSA::RSA(){
	n = q = 0;
	e = d = 19;
}

BigNumber RSA::get_n(){
	return n;
}

BigNumber RSA::get_e(){
	return e;
}

BigNumber RSA::get_d(){
	return d;
}
		
void RSA::generate_prime(){
	if (data.empty()){
		ifstream in("prime_numbers.txt");
		BigNumber X;
		while (in >> X) data.pb(X);
	}
	if (data.empty()){
		ifstream in("RSA/prime_numbers.txt");
		BigNumber X;
		while (in >> X) data.pb(X);
	}
	BigNumber A, B;
	ll count = 1000;
	do {
		srand(time(NULL));
		A = modPow(rand()%data.size(),rand(),data.size());
		B = modPow(modPow(A,rand(),data.size()),A,data.size());
		--count;
	} while (A == B || count > 0);
	ll a = A.toInt();
	ll b = B.toInt();
	p = data[a];
	q = data[b];
}

void RSA::set_e(BigNumber E){
	e = E;
}

bool prime[10000];
void RSA::process(){
	if (p == 0 || q == 0){
		generate_prime();
	}
	n = p*q;
	BigNumber lambda_n = (p-1)*(q-1)/gcd(p-1,q-1);
	if (small.empty()){
		memset(prime, true, sizeof prime);
		for (ll i = 2; i <= 10000; ++i){
			if (prime[i]){
				BigNumber A = i;
				small.pb(A);
				for (ll j = 2; j*i <= 10000; ++j) prime[(j*i)] = false;
			}
		}
	}
	ll count = 1000;
	srand(time(NULL));
	ll idx = rand()%small.size();
	cerr << "--";
	while (gcd(e, lambda_n) != 1 || count > 0 || e >= lambda_n){
		e = small[idx];
		idx *= rand();
		idx %= small.size();
		++idx;
		--count;
	}
	cerr << "**";
	d = modInverse(e,lambda_n);
}

BigNumber RSA::encrypt(BigNumber m, BigNumber e, BigNumber n){
	return modPow(m,e,n);
}

BigNumber RSA::decrypt(BigNumber c, BigNumber d, BigNumber n){
	return modPow(c,d,n);
}

BigNumber RSA::encrypt(BigNumber message){
	return encrypt(message,e,n);
}

BigNumber RSA::decrypt(BigNumber encoded){
	return decrypt(encoded,d,n);
}

BigNumber RSA::select_random_prime(){
	ll count = 1000;
	BigNumber A;
	do {
		srand(time(NULL));
		A = modPow(rand()%data.size(),rand(),data.size());
//		A = modPow(modPow(A,rand(),data.size()),A%,data.size());
		--count;		
	} while (count);
	return data[A.toInt()%data.size()];
}

void RSA::encrypt_to_code(const string& from, const string& to){
	ifstream in(from.c_str());
	ofstream out(to.c_str());
	string temp;
	ll count = 0;
	BigNumber tmp;
	while (getline(in,temp)){
		srand(time(NULL));
		tmp = (select_random_prime()-1)*rand()*256;
		for (ll i = 0; i < temp.size(); ++i){
/*			do {
				if ((count*small[small.size()/4]) % small[small.size()/2] <= small[small.size()/8]){
					tmp += select_random_prime()*256;
				} else {
					tmp -= small.back()*256;
				}
				++count;
			} while (gcd(tmp + temp[i], n) != 1); */
			out << encrypt(tmp + (ll)((unsigned char) temp[i])) << " ";
			count = 0;
		}
/*		do {
			if ((count*small[small.size()/4]) % small[small.size()/2] <= small[small.size()/8]){
				tmp += select_random_prime()*256;
			} else {
				tmp -= small.back()*256;
			}
			++count;
		} while (gcd(tmp + temp[i], n) != 1);	*/
		out << encrypt(tmp + (ll)((unsigned char) '\n')) << " ";
	}
}

void RSA::decrypt_to_normal(const string& from, const string& to){
	ifstream in(from.c_str());
	ofstream out(to.c_str());
	BigNumber temp;
	ll tmp;
	while (in >> temp){
		out << (char) ((decrypt(temp)).toInt()%256);
	}
}
