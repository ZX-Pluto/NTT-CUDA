#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include "helper.h"
#include "parameter.h"
#include "ntt_60bit.cuh"
#include "poly_arithmetic.cuh"

#include <time.h>
#include <sys/time.h> 

#define check 0

int main()
{
    unsigned N = 4096 << 1;
    // unsigned N = 32768;

    int size_array = sizeof(unsigned long long) * N;
    int size = sizeof(unsigned long long);

    unsigned long long q, psi, psiinv, ninv;
    unsigned int q_bit;

    getParams(q, psi, psiinv, ninv, q_bit, N);

    unsigned long long* psiTable = (unsigned long long*)malloc(size_array);
    unsigned long long* psiinvTable = (unsigned long long*)malloc(size_array);
    fillTablePsi128(psi, q, psiinv, psiTable, psiinvTable, N); //gel psi psi
    // exit(0);

    //copy powers of psi and psi inverse tables to device
    unsigned long long* psi_powers, * psiinv_powers;

    cudaMalloc(&psi_powers, size_array);
    cudaMalloc(&psiinv_powers, size_array);

    cudaMemcpy(psi_powers, psiTable, size_array, cudaMemcpyHostToDevice);
    cudaMemcpy(psiinv_powers, psiinvTable, size_array, cudaMemcpyHostToDevice);

    // cout << "n = " << N << endl;
    // cout << "q = " << q << endl;
    // cout << "Psi = " << psi << endl;
    // cout << "Psi Inverse = " << psiinv << endl;

    //generate parameters for barrett
    unsigned int bit_length = q_bit;
    uint128_t mu1 = uint128_t::exp2(bit_length * 2);
    unsigned long long mu = (mu1 / q).low;
    
    clock_t start,stop;
  	start = clock();
    // MyTimer timer;
    // MyTimer timer2;
    // long ntt_time = 0,intt_time = 0, trans_in_time = 0, trans_out_time = 0;
    // timer2.Start();
    unsigned long long* a;
    cudaMallocHost(&a, sizeof(unsigned long long) * N);
    // randomArray128(a, N, q);
    unsigned long long* b;  
    cudaMallocHost(&b, sizeof(unsigned long long) * N);
    for(int j = 0; j < 100000; ++j)
    {
        // timer.Start();
        
        // randomArray128(b, N, q);
        for (size_t i = 0; i < N; i++)
        {
            a[i] = i;
            b[i] = 0;
        }
        b[0] = 1;
        unsigned long long* d_a;
        cudaMalloc(&d_a, size_array);
        unsigned long long* d_b;
        cudaMalloc(&d_b, size_array);
        cudaStream_t ntt1, ntt2;
        // cudaStream_t ntt1;
        cudaStreamCreate(&ntt1);
        cudaStreamCreate(&ntt2);
        cudaMemcpyAsync(d_a, a, size_array, cudaMemcpyHostToDevice, ntt1);
        cudaMemcpyAsync(d_b, b, size_array, cudaMemcpyHostToDevice, ntt2);
        cudaDeviceSynchronize();
        // timer.End();
        // trans_in_time += timer.costTime;
        // timer.Reset();

        // timer.Start();
        // forwardNTTdouble(d_a, d_b, N, ntt1, ntt2, q, mu, bit_length, psi_powers);
        forwardNTT(d_a, N, ntt1, q, mu, bit_length, psi_powers);
        cudaDeviceSynchronize();
        // timer.End();
        // std::cout << "NTT-time:" << timer.costTime << "us" << std::endl;
        // ntt_time += timer.costTime;
        // timer.Reset();
        forwardNTT(d_b, N, ntt1, q, mu, bit_length, psi_powers);
        
        barrett << <N / 256, 256 >> > (d_a, d_b, q, mu, bit_length);
        // timer.Start();
        inverseNTT(d_a, N, ntt1, q, mu, bit_length, psiinv_powers);
        // cudaDeviceSynchronize();
        // timer.End();
        // std::cout << "INTT-time:" << timer.costTime << "us" << std::endl;
        // intt_time += timer.costTime;
        // timer.Reset();

        // timer.Start();
        cudaMemcpyAsync(a, d_a, size_array, cudaMemcpyDeviceToHost, 0);
        cudaDeviceSynchronize();
        // timer.End();
        // std::cout << "INTT-time:" << timer.costTime << "us" << std::endl;
        // trans_out_time += timer.costTime;
        // timer.Reset();

        cudaStreamDestroy(ntt1); 
        // cudaStreamDestroy(ntt2);
        // timer2.End();
        // for (size_t i = 0; i < N; i++)
        // {
        //     cout << a[i] << " " ;
        // }
        // cout << endl;
        // cudaFreeHost(a); 
        // cudaFreeHost(b);
    }
    // timer2.End();
    // std::cout << "trans_in-time:" <<trans_in_time/10000 << "us" << std::endl;
    // std::cout << "trans_out-time:" << trans_out_time/10000 << "us" << std::endl;
    // std::cout << "NTT-time:" << ntt_time/1 << "us" << std::endl;
    // std::cout << "INTT-time:" << intt_time/1 << "us" << std::endl;
    // std::cout << "all-time:" << timer2.costTime/1 << "us" << std::endl;
    
	stop = clock();
  	double endtime=(double)(stop-start)/CLOCKS_PER_SEC; 
 	std::cout << "time: "<< endtime << "s" <<std::endl;

    // unsigned long long* a;
    // cudaMallocHost(&a, sizeof(unsigned long long) * N);
    // // randomArray128(a, N, q); //fill array with random numbers between 0 and q - 1
    

    // unsigned long long* b;  
    // cudaMallocHost(&b, sizeof(unsigned long long) * N);
    // // randomArray128(b, N, q); //fill array with random numbers between 0 and q - 1
    // for (size_t i = 0; i < N; i++)
    // {
    //     a[i] = i;
    //     b[i] = 0;
    // }
    // // for (size_t i = 0; i < 4; i++)
    // // {
    // //     a[i] = 1;
    // // }
    
    // b[0] = 1;
    

    // unsigned long long* d_a;
    // cudaMalloc(&d_a, size_array);
    // unsigned long long* d_b;
    // cudaMalloc(&d_b, size_array);

    // unsigned long long* refc;
    // if (check)
    //     refc = refPolyMul128(a, b, q, N);

    // cudaStream_t ntt1, ntt2;
    // cudaStreamCreate(&ntt1);
    // cudaStreamCreate(&ntt2);

    // cudaMemcpyAsync(d_a, a, size_array, cudaMemcpyHostToDevice, ntt1);
    // cudaMemcpyAsync(d_b, b, size_array, cudaMemcpyHostToDevice, ntt2);

    // // forwardNTT(d_a, N, ntt1, q, mu, bit_length, psi_powers);
    // // cout << "mu1.low = " << mu1.low << "mu1.high = " << mu1.high << "; mu = " << mu << endl;
    // forwardNTTdouble(d_a, d_b, N, ntt1, ntt2, q, mu, bit_length, psi_powers);
    // // forwardNTT(d_b, N, ntt1, q, mu, bit_length, psi_powers);
    
    // barrett << <N / 256, 256 >> > (d_a, d_b, q, mu, bit_length);
    // inverseNTT(d_a, N, ntt1, q, mu, bit_length, psiinv_powers);

    // cudaMemcpyAsync(a, d_a, size_array, cudaMemcpyDeviceToHost, 0);

    // cudaDeviceSynchronize();

    // cudaStreamDestroy(ntt1); cudaStreamDestroy(ntt2);

    // // for (size_t i = 0; i < N; i++)
    // // {
    // //     cout << a[i] << " " ;
    // // }
    

    // // if (check) //check the correctness of results
    // // {
    // //     for (int i = 0; i < N; i++)
    // //     {
    // //         if (a[i] != refc[i])
    // //         {
    // //             cout << "error" << endl;
    // //             cout << i << "   " << a[i] << "   " << refc[i] << endl;
    // //         }

    // //     }

    // //     free(refc);
    // // }

    // cudaFreeHost(a); cudaFreeHost(b);

    return 0;
}


