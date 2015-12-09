#include"RandNum.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
using namespace std;
#define BLOCK 4
#define CODEWORD 7
int generate_matrix[4][7] = { {1,1,0,1,0,0,0}, {0,1,1,0,1,0,0}, {1,1,1,0,0,1,0}, {1,0,1,0,0,0,1} };
int check_matrix[3][7] = { { 1, 1, 0, 1, 1, 0, 0 }, { 1, 0, 1, 1, 0, 1, 0 }, { 1, 1, 1, 0, 0, 0, 1 } };
int coset[8][7] = { { 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0 }, { 1, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0 } };
int *Hamming_coding(int* uncoding_seq, int length);
int *Hamming_correction(int* received_seq, int* corrected_seq, int length);
int *Hamming_decoding(int* corrected_seq, int length);