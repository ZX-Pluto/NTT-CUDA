#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include "my_hexl.h"
using namespace std;
class Ntt {
public:
	uint64_t kesai;
	uint64_t q;
	uint64_t degree;
	uint64_t inv_kesai;
	// uint64_t inv_degree;
	uint64_t m_pow;
	vector<uint64_t> w_rom;
	vector<uint64_t> w_inv;
	Ntt(uint64_t q, uint64_t kesai, uint64_t degree):q(q),kesai(kesai),degree(degree) {
		m_pow = Log2(degree);
		inv_kesai = PowMod(kesai, (degree<<1) -1, q);
		w_rom.resize(degree);
		w_inv.resize(degree);
		for (long i = 0; i < degree; ++i)
		{
			w_rom[i] = PowMod(kesai, bitreverse(i,m_pow) % q, q);
		}
	}

	uint64_t bitreverse(uint64_t n, uint64_t l)
	{
		uint64_t res = 0;
		for (long i = 0; i < l; ++i)
		{
			res = (res << 1) | (n & 1);
			n >>= 1;
		}
		return res;
	}
	vector<uint64_t> ntt(vector<uint64_t> a) {
		uint64_t n = a.size();
		uint64_t log_n = Log2(n);
		uint64_t r = 1;
		// ofstream fout("nwc_NTT_C.txt"); //文件输出流对象
		// streambuf* pOld =cout.rdbuf(fout.rdbuf());
		// int my_i = 0;
		for (long p = log_n - 1; p >= 0; --p)
		{
			int J = 1 << p;
			for (long k = 0; k < n/(J << 1); ++k)
			{
				uint64_t w = w_rom[r++];
				for (long j = 0; j < J; ++j)
				{
					uint64_t u = a[(k<<1)*J + j] % q;
					uint64_t t = MultiplyMod(a[(k<<1)*J + j + J], w, q);
					a[(k<<1)*J + j] = (u + t) % q;
					u += q*(u < t);
					a[(k<<1)*J + j + J] = (u - t) % q;
				}	
			}
		}
		return a;
	}

	uint64_t op21(uint64_t a)
	{
		return (a & 1) == 0 ? (a >> 1) % q : ((a >> 1) + ((q + 1) >> 1)) % q;
	}

	vector<uint64_t> rntt(vector<uint64_t> a) {
		uint64_t n = a.size();
		uint64_t log_n = Log2(n);
		uint64_t r = w_rom.size() - 1;
		for (long i = 0; i < log_n; ++i)
		{
			uint64_t J = 1 << i;
			for (long k = 0; k < n/(J << 1); ++k)
			{
				uint64_t w = w_rom[r--];
				for (long j = 0; j < J; ++j)
				{
					uint64_t u = a[(k<<1)*J + j] % q;
					uint64_t t = a[(k<<1)*J + j + J] % q;
					a[(k<<1)*J + j] = (op21(u + t)) % q;
					t += q*((t < u));
					a[(k<<1)*J + j + J] = MultiplyMod(op21(t - u), w, q);
					// if(0 < ((k<<1)*J + j) && ((k<<1)*J + j) < 10){
					// 	cout << (k<<1)*J + j << " : " << " u = " << u << ", t = " << t << endl;
					// 	cout << "a[" << (k<<1)*J + j << "] = " << a[(k<<1)*J + j] << endl;
					// }
				}	
			}
		}
		return a;
	}
	
};

template <typename T>
void print_vector(vector<T> vector_temp){
    cout << "{";
    for(auto item : vector_temp) cout << item << ",";
    cout << "\b}";
}

template <typename T>
void print_array(T *array_temp,size_t len){
    cout << "{";
    for (long i = 0; i < len; i++)  cout << array_temp[i] << ",";
    cout << "\b}";
}

vector<uint64_t> pwm(vector<uint64_t> x, vector<uint64_t> y, uint64_t modulus)
{
	int len_x = x.size();
	vector<uint64_t> z(len_x);
	for (long i = 0; i < len_x; ++i)
	{
		z[i] = MultiplyMod(x[i], y[i], modulus);
	}
	return z;
}

int main() {
	// q = 137438691329;
	// psi = 22157790;
	// psiinv = 88431458764;
	// ninv = 137371582593;
	// q_bit = 37;
	uint64_t n = 4096;
	uint64_t q = 970662608897;;
	uint64_t psi = 0;
	uint64_t psiinv = 0;
	uint64_t ninv = 0;
	uint64_t q_bit = 0;
	// psi = GeneratePrimitiveRoot(n << 1, q);
	while(true){
		psi = GeneratePrimitiveRoot(n << 1, q);
		if(psi < 391209173) break;
	}
	psiinv = PowMod(psi, (n >> 1) - 1, q);
	ninv = InverseMod(n, q);
	q_bit = Log2(q)+1;

	std::cout << "n = " << n << ";" << std::endl;
	std::cout << "q = " << q << ";" << std::endl;
	std::cout << "psi = " << psi << ";" << std::endl;
	// std::cout << "root = " << psi << std::endl;
	std::cout << "psiinv = " << psiinv << ";" << std::endl;
	std::cout << "ninv = " << ninv << ";" << std::endl;
	std::cout << "q_bit = " << q_bit << ";" << std::endl;
	exit(0);



	uint64_t modulus,degree,root;
	// modulus = 1067353111686807553;
	// degree = 8192;
	// root = GeneratePrimitiveRoot(degree << 1, modulus);
	modulus = 970662608897;
	// root = 637513799784;
	degree = 8192;
	root = GeneratePrimitiveRoot(degree << 1, modulus);
	// cout << "root = " << root << endl;
	// modulus = q;
	// degree = n;
	// root = psi;
	Ntt tmp(modulus, root, degree);
	vector<uint64_t> xp(degree,0);
	for (long i = 0; i < degree; i++)
	{
		xp[i] = i;
	}
	// cout << "xp = " ; print_vector(xp); cout << endl;
	// my_a.begin() = xp;

	auto xp_n=tmp.ntt(xp);
	// cout << "xp_n = " ; print_vector(xp_n); cout << endl;
	

	vector<uint64_t> yp(degree, 0);
	yp[0] = 1;
	auto yp_n=tmp.ntt(yp);
	// cout << "yp_n = " ; print_vector(yp_n); cout << endl;
	vector<uint64_t> z_n = pwm(xp_n, yp_n, modulus);
	cout << "z_n = " ; print_vector(z_n); cout << endl;

    auto z_p = tmp.rntt(xp_n);
	cout << "z_p = " ; print_vector(z_p); cout << endl;
}