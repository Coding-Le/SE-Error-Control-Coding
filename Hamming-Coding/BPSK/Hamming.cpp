#include<iostream>
#include"Hamming.h"

int* Hamming_coding(int* uncoding_seq, int length) {
	int message_block[BLOCK];
	//int *codeword_arr = new int[(length/BLOCK+2)*CODEWORD];
	//codeword_length = 0;
	codeword_length = -1;
	int i, j, k;
	for (i = 0; i < length; ) {
		for (j = 0; j < BLOCK && i < length; j++, i++) {
			message_block[j] = uncoding_seq[i];
		}
		if (i >= length && j < BLOCK) {
			for (k = 0; k < j; k++) {
				codeword_arr[++codeword_length] = message_block[k];
			}
			break;
		}
		for (j = 0; j < CODEWORD; j++) {
			codeword_arr[++codeword_length] = 0;
			for (k = 0; k < BLOCK; k++) {
				codeword_arr[codeword_length] += generate_matrix[k][j] * message_block[k];
			}
			codeword_arr[codeword_length] %= 2;
		}
	}
	//codeword_arr[0] = codeword_length;
	codeword_length++;
	codeword_arr[(L / BLOCK + 2)*CODEWORD - 1] = codeword_length;
	return codeword_arr;
}

int *Hamming_correction(int* error_seq, int length) {
	int error_pattern[CODEWORD - BLOCK];
	int codeword_block[CODEWORD];
	int i, j, k;
	for (i = 0; i < length; ) {
		for (j = 0; j < CODEWORD; j++, i++) {
			codeword_block[j] = error_seq[i];
		}
		if (i >= length && j < CODEWORD) {
			break;
		}
		for (j = 0; j < CODEWORD - BLOCK; j++) {
			error_pattern[j] = 0;
			for (k = 0; k < CODEWORD; k++) {
				error_pattern[j] += codeword_block[k] * check_matrix[j][k];
			}
			error_pattern[j] %= 2;
		}
		int index = 0;
		for (j = 0; j < CODEWORD - BLOCK; j++) {
			index += error_pattern[CODEWORD - BLOCK-j-1]*pow(2,j);
		}
		for (j = 0; j < CODEWORD; j++) {
			error_seq[i - CODEWORD + j] += coset[index][j];
			error_seq[i - CODEWORD + j] %= 2;
		}
	}
	return error_seq;
}

int *Hamming_decoding(int* corrected_seq, int length) {
	int codeword_block[CODEWORD];
	//int *message_arr = new int[(length / CODEWORD + 2)*BLOCK];
	//int message_length = 0;
	message_length = -1;
	int i, j, k;
	for (i = 0; i < length;) {
		for (j = 0; j < CODEWORD && i < length; j++,i++) {
			codeword_block[j] = corrected_seq[i];
		}
		if (i >= length && j < CODEWORD) {
			for (k = 0; k < j; k++) {
				message_arr[++message_length] = codeword_block[k];
			}
			break;
		}
		for (j = BLOCK-1; j < CODEWORD; j++) {
			/*message_arr[++message_length] = 0;
			for (k = 0; k < CODEWORD; k++) {
				message_arr[message_length] += codeword_block[k] * generate_matrix[j][k];
			}*/
			message_arr[++message_length] = codeword_block[j];
		}
	}
	//message_arr[0] = message_length;
	message_length++;
	message_arr[L + BLOCK * 4 - 1] = message_length;
	return message_arr;
}