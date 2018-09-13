////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Sha256String
//
//  Outputs SHA256 hash of a string specified on command line. Hash is output in hex
//
//  This is free and unencumbered software released into the public domain - June 2013 waterjuice.org
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  IMPORTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sha256.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  main
//
//  Program entry point
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int ArgC, char** ArgV) {
    byte*           string;
    Sha256Context   sha256Context;
    SHA256_HASH     sha256Hash;
    uint16_t        i;

//    ArgC = 2;
//
//    if( 2 != ArgC )
//    {
//        printf(
//                "Syntax\n"
//                "   Sha256String <String>\n" );
//        return 1;
//    }

//    string = ArgV[1];
    string = "123";
//    uint8_t a = 0x78, b = 0x00, c = 0x01, d = 0x00;
//    string = {a,b,c,d};

    Sha256Initialise( &sha256Context );
    Sha256Update( &sha256Context, (unsigned char*)string, (uint32_t)strlen(string) );
    Sha256Finalise( &sha256Context, &sha256Hash );

    for( i=0; i<sizeof(sha256Hash); i++ )
    {
        printf( "%2.2X", sha256Hash.bytes[i] );
    }
    printf( "\n" );

    return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdint.h>
//#include <windows.h>
//
//#define SHA256_ROTL(a,b) (((a>>(32-b))&(0x7fffffff>>(31-b)))|(a<<b))
//#define SHA256_SR(a,b)   ((a>>b)&(0x7fffffff>>(b-1)))
//
//#define SHA256_Ch(x,y,z)  ((x&y)^((~x)&z))
//#define SHA256_Maj(x,y,z) ((x&y)^(x&z)^(y&z))
//
//#define SHA256_E0(x) (SHA256_ROTL(x,30)^SHA256_ROTL(x,19)^SHA256_ROTL(x,10))
//#define SHA256_E1(x) (SHA256_ROTL(x,26)^SHA256_ROTL(x,21)^SHA256_ROTL(x,7) )
//
//#define SHA256_O0(x) (SHA256_ROTL(x,25)^SHA256_ROTL(x,14)^SHA256_SR  (x,3) )
//#define SHA256_O1(x) (SHA256_ROTL(x,15)^SHA256_ROTL(x,13)^SHA256_SR  (x,10))
//
//extern char* StrSHA256(const char* str,  long length, char* sha256){
//    /*
//    计算字符串SHA-256
//    参数说明：
//    str                  字符串指针
//    length               字符串长度
//    sha256               用于保存SHA-256的字符串指针
//    返回值为参数sha256
//    */
//    char *pp, *ppend;
//    int l, i, W[64], T1, T2, A, B, C, D, E, F, G, H, H0, H1, H2, H3, H4, H5, H6, H7;
//    H0 = 0x6a09e667, H1 = 0xbb67ae85, H2 = 0x3c6ef372, H3 = 0xa54ff53a;
//    H4 = 0x510e527f, H5 = 0x9b05688c, H6 = 0x1f83d9ab, H7 = 0x5be0cd19;
//    long K[64] = {
//            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
//            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
//            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
//            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
//            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
//            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
//            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
//            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
//    };
//    l = length + ((length % 64 >= 56) ? (128 - length % 64) : (64 - length % 64));
//
//    if (!(pp = (char*)malloc((unsigned long)l))){
//        return 0;
//    }
//
//    for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++);
//    for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0, i++);
//    *((long*)(pp + l - 4)) = length << 3;
//    *((long*)(pp + l - 8)) = length >> 29;
//    for (ppend = pp + l; pp < ppend; pp += 64){
//        for (i = 0; i < 16; W[i] = ((long*)pp)[i], i++);
//        for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] + SHA256_O0(W[i - 15]) + W[i - 16]), i++);
//        A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
//        for (i = 0; i < 64; i++){
//            T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] + W[i];
//            T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
//            H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
//        }
//        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
//    }
//    free(pp - l);
//    sprintf(sha256, "%08X%08X%08X%08X%08X%08X%08X%08X", H0, H1, H2, H3, H4, H5, H6, H7);
//    return sha256;
//}
//
//int main(void){
////    char text [] = "78000100";
//    uint8_t a = 0x78, b = 0x00, c = 0x01, d = 0x00;
//    char text [] = {a,b,c,d};
//    char sha256[65];
//    StrSHA256(text,sizeof(text)-1,sha256);    // 函数返回值即sha256，直接输出也可以
//    puts(sha256);
//    return 0;
//}
//
////    char text [] = "0005FF0000000054000000020000F00000000088B707241545A346265AAB1FFB32FF64B55BF8F8DC1B56A46EF33CE3D15DB11D330000F100000000105A2CFE8AB935918525D44FD6FD87C70FC83B4F29D1A727672E1B48F380473FC1";
////
////    byte text [] = {0x00,0x00,0x00,0x02,0x00,0xFC,0x00,0x00,0x00,0x00,0x04,0x00,0xD1,0x56,0x8F,0x40,0xC5,0x65,0xA7,0x97,0x42,0x2C,0x4F,0xE7,0x02,0x67,0xB6,
////                    0x85,0x2E,0x26,0xCE,0xC4,0xE8,0x90,0xB9,0xF3,0x2D,0x7A,0xF6,0x30,0x4F,0x25,0xD5,0x91,0x01,0x00,0x00,0x00,0x00,0x02,0xE6,0x00,0xA8,0x81,
////                    0x07,0x6F,0x8F,0x6B,0x2D,0xC5,0x63,0xF3,0x4A,0x6B,0x61,0x0CA,0xE1,0x1B,0xAF,0xDA,0xD8,0xE8,0x62,0xAB,0x69,0x98,0xBE,0x2C,0x2A,0x8C,0x6A,
////                    0xAD,0x96,0x15};
////
////    00 FC 00 80 00 00 00 07 94 06 00 01 20 41 41
////
////    byte text [] = {0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x5A,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,
////                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
////                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
////                    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
////
////    char text [] = {0x00,0x05,0xFF,0x00,0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x02,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x88,0xB7,0x07,0x24,0x15,0x45,0xA3,0x46,
////                    0x26,0x5A,0xAB,0x1F,0xFB,0x32,0xFF,0x64,0xB5,0x5B,0xF8,0xF8,0xDC,0x1B,0x56,0xA4,0x6E,0xF3,0x3C,0xE3,0xD1,0x5D,0xB1,0x1D,0x33,0x00,0x00,
////                    0xF1,0x00,0x00,0x00,0x00,0x10,0x5A,0x2C,0xFE,0x8A,0xB9,0x35,0x91,0x85,0x25,0xD4,0x4F,0xD6,0xFD,0x87,0xC7,0x0F,0xC8,0x3B,0x4F,0x29,0xD1,
////                    0xA7,0x27,0x67,0x2E,0x1B,0x48,0xF3,0x80,0x47,0x3F,0xC1};