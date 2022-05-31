#pragma once

#include "helper.h"

void fillTablePsi128(unsigned long long psi, unsigned long long q, unsigned long long psiinv, unsigned long long psiTable[], unsigned long long psiinvTable[], unsigned int n)
{
    cout << "psi = " << psi << endl;
	cout << "lo2(n) = " << log2(n) << endl;

    for (int i = 0; i < n; i++)
    {
        psiTable[i] = modpow128(psi, bitReverse(i, log2(n)), q);
        psiinvTable[n - i - 1] = psiTable[i];
        // psiinvTable[i] = modpow128(psiinv, bitReverse(i, log2(n)), q);
        // if(i < n) {
        //     cout << i << " : bitreserve = " << bitReverse(i,log2(n)) << ", w_inv = " << psiinvTable[i] << endl;
        // }
    }
    // int* rev = (int*)malloc(sizeof(int) * n);
    // int l = log2(n);
    // unsigned long long mytemp;
    // for (int i = 0; i < n; i++)   
    // {
    //     rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l-1));
    //     if (i < rev[i]) {
    //         mytemp = psiinvTable[i];
    //         psiinvTable[i] = psiinvTable[rev[i]];
    //         psiinvTable[rev[i]] = mytemp;
    //     }
    // }
    // for(int i = 0; i < 5; ++i){
    //     cout << i << " : w_inv = " << psiinvTable[i] << endl;
    // }
    // cout << 4096 << " : w_inv = " << psiinvTable[4096] << endl;
    // cout << 4096 << " : w_inv = " << psiinvTable[4096] << endl;
}

void fillTablePsi128Forward(unsigned long long psi, unsigned long long q, unsigned long long psiTable[], unsigned int n)
{
    for (int i = 0; i < n; i++)
    {
        psiTable[i] = modpow128(psi, bitReverse(i, log2(n)), q);
    }
}

void fillTablePsi64(unsigned psi, unsigned q, unsigned psiinv, unsigned psiTable[], unsigned psiinvTable[], unsigned int n)
{
    for (int i = 0; i < n; i++)
    {
        psiTable[i] = modpow64(psi, bitReverse(i, log2(n)), q);
        // psiinvTable[i] = modpow64(psiinv, bitReverse(i, log2(n)), q);
        psiinvTable[n - i - 1] = psiTable[i];
    }
}

void getParams(unsigned long long& q, unsigned long long& psi, unsigned long long& psiinv, unsigned long long& ninv, unsigned int& q_bit, unsigned long long n)
{
    if (n == 2048)
    {
        // q = 137438691329;
        // psi = 22157790;
        // psiinv = 88431458764;
        // ninv = 137371582593;
        // q_bit = 37;

        q = 970662608897;
        psi = 416958171;
        psiinv = 491988523000;
        ninv = 970188652545;
        q_bit = 40;
    }
    else if (n == 4096)
    {
        /*q = 288230376135196673;
        psi = 60193018759093;
        psiinv = 236271020333049746;
        ninv = 288160007391023041;
        q_bit = 58;*/

        q = 970662608897;
        psi = 391209173;
        psiinv = 159575809722;
        ninv = 970425630721;
        q_bit = 40;

        // q = 33538049;
        // psi = 2386;
        // psiinv = 26102329;
        // ninv = 33529861;
        // q_bit = 25;
    }
    else if (n == 8192)
    {
        // q = 8796092858369;
        // psi = 1734247217;
        // psiinv = 5727406356888;
        // ninv = 8795019116565;
        // q_bit = 43;

        // q = 970662608897;
        // psi = 8383185559;
        // psiinv = 724611380857;
        // ninv = 970544119809;
        // q_bit = 40;

        // q = 263882790666241;
        // psi = 793584798341;
        // psiinv = 79140600827483;
        // ninv = 263850578411521;
        // q_bit = 48;

        q = 1067353111686807553;
        psi = 3880757215850882;
        psiinv = 642145176100015345;
        ninv = 1067222819558916097;
        q_bit = 60;

    }
    else if (n == 16384)
    {

        q = 966367641601;
        psi = 56177670;
        psiinv = 775604640312;
        ninv = 966308659201;
        q_bit = 40;

        // q = 281474976546817;
        // psi = 23720796222;
        // psiinv = 129310633907832;
        // ninv = 281457796677643;
        // q_bit = 48;

        // q = 1067353111686807553;
        // psi = 69038609272135;
        // psiinv = 863028901020454976;
        // ninv = 1067287965622861825;
        // q_bit = 60;
        
    }
    else if (n == 32768)
    { 


        // q = 970662608897;
        // psi = 19879708;
        // psiinv = 309934455628;
        // ninv = 970632986625;
        // q_bit = 40;

        q = 263882790666241;
        psi = 11399559836;
        psiinv = 164931646953814;
        ninv = 263874737602561;
        q_bit = 48;


        // q = 1067353111686807553;
        // psi = 4517939337050;
        // psiinv = 592337270253447633;
        // ninv = 1067320538654834689;
        // q_bit = 60;

        // q = 36028797017456641;
        // psi = 1155186985540;
        // psiinv = 31335194304461613;
        // ninv = 36027697505828911;
        // q_bit = 55;
    }
}

void getParams30(unsigned& q, unsigned& psi, unsigned& psiinv, unsigned& ninv, unsigned& q_bit, unsigned n)
{
    if (n == 2048)
    {
        /*q = 12931073;
        psi = 3733;
        psiinv = 10610200;
        q_bit = 24;
        ninv = 12924759;*/

        q = 536608769;
        psi = 284166;
        psiinv = 208001377;
        q_bit = 29;
        ninv = 536346753;
    }
    else if (n == 4096)
    {
        q = 33538049;
        psi = 2386;
        psiinv = 26102329;
        ninv = 33529861;
        q_bit = 25;
    }
    else if (n == 8192)
    {
        q = 8716289;
        psi = 1089;
        psiinv = 8196033;
        q_bit = 24;
        ninv = 8715225;
    }
    else if (n == 16384)
    {
        q = 13664257;
        psi = 273;
        psiinv = 8959348;
        q_bit = 24;
        ninv = 13663423;
    }
    else if (n == 32768)
    {
        q = 19070977;
        psi = 377;
        psiinv = 16642842;
        q_bit = 25;
        ninv = 19070395;
    }
    else if (n == 65536)
    {
        q = 13631489;
        psi = 13;
        psiinv = 12582913;
        q_bit = 24;
        ninv = 13631281;
    }
}
