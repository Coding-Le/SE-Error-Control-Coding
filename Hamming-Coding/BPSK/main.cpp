#include"RandNum.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
#include"Hamming.h"
using namespace std;

int source_arr[L];
int encode_arr[(L / BLOCK + 2)*CODEWORD];
double total_arr[(L / BLOCK + 2)*CODEWORD];
int decode_arr[(L / BLOCK + 2)*CODEWORD];
int* generator(int length) {
	double token;
	CLCRandNum temp = CLCRandNum();
	temp.SetSeed(0);
	for (int i = 0; i < length; i++) {
		token = temp.Uniform();   // generate number between 0~1
		source_arr[i] = token > 0.5 ? 1 : 0;
	}
	return source_arr;
}
int *encode(int *src_arr, int length) {
	for (int i = 0; i < length; i++) {
		encode_arr[i] = (src_arr[i] > 0.5) ? 1 : -1;
	}
	return encode_arr;
}
double *add_noise(int *encode_arr, int length, double delta) {
	CLCRandNum temp = CLCRandNum();
	temp.Normal(total_arr, length);
	for (int i = 0; i < length; i++) {
		total_arr[i] = delta*total_arr[i] + encode_arr[i];
	}
	return total_arr;
}
int *decode(double *total_arr, int length) {
	for (int i = 0; i < length; i++) {
		decode_arr[i] = total_arr[i] > 0 ? 1 : 0;
	}
	return decode_arr;
}
int error_num(int *source_arr, int *decode_arr, int length) {
	int error_num = 0;
	for (int i = 0; i < length; i++) {
		if (source_arr[i] != decode_arr[i]) {
			error_num++;
		}
	}
	return error_num;
}
double calculate_delta(double E_No) {
	double temp = E_No;
	temp = pow(10,temp/10);
	temp = sqrt(0.5 / temp);
	return temp;
}
int main() {
	double *E_No = new double[100];
	double *delta = new double[100];
	for (int i = 2; i < 100; i++) {
		double temp_int = i;
		E_No[i] = double(temp_int / 10);
		delta[i] = calculate_delta(E_No[i]);
	}
	fstream DataWriter;
	DataWriter.open("data.txt", ios::out);
	if (!DataWriter) {
		cout << "Create File Error" << endl;
		exit(0);
	}
	DataWriter << "   Es/No         Bit-Error Probability" << endl;
	cout << "   Es/No" << "         Bit-Error Probability" << endl;
 	for (int i = 2; i < 100; i++) {
		int total_error = 0;
		for (int j = 0; j < 1000000; j++) {
			int *source_arr = generator(L);
			/*for (int t = 0; t < L; t++) {
				cout << source_arr[t] << " ";
				if (t == L - 1)
					cout << endl;
			}*/
			int *HammingCodewordArr = Hamming_coding(source_arr, L);
			codeword_length = HammingCodewordArr[(L / BLOCK + 2)*CODEWORD - 1];
			/*for (int t = 0; t < codeword_length; t++) {
				cout << HammingCodewordArr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			int *encode_arr = encode(HammingCodewordArr, codeword_length);
			/*for (int t = 0; t < codeword_length; t++) {
				cout << encode_arr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			double *total_arr = add_noise(encode_arr, codeword_length, delta[i]);
			/*cout << delta[i] << endl;
			for (int t = 0; t < codeword_length; t++) {
				cout << total_arr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			int *decode_arr = decode(total_arr, codeword_length);
			/*for (int t = 0; t < codeword_length; t++) {
				cout << decode_arr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			int *HammingMessageArr = Hamming_correction(decode_arr, codeword_length);
			/*for (int t = 0; t < codeword_length; t++) {
				cout << HammingMessageArr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			int *received_arr = Hamming_decoding(HammingMessageArr, codeword_length);
			message_length = received_arr[L + BLOCK * 4 - 1];
			/*for (int t = 0; t < message_length; t++) {
				cout << received_arr[t] << " ";
				if (t == codeword_length - 1)
					cout << endl;
			}*/
			total_error += error_num(source_arr, received_arr, L);
			/*int temp_error = error_num(HammingCodewordArr, decode_arr, codeword_length);
			cout << temp_error << endl;*/
		}
		cout.precision(4);
		cout << "X: " << fixed << E_No[i] << ",         " << "Y: " << total_error << "*10^(-9)" << endl;
		DataWriter << E_No[i] << "       " << total_error << "\n";
	}
	DataWriter.close();
	system("pause");
}