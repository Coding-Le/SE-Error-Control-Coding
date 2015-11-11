#include"RandNum.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>
#include<cstdlib>
using namespace std;
#define L 1000
int source_arr[L];
int encode_arr[L];
double total_arr[L];
int decode_arr[L];

/*int* generator() {
	int length = 10000000;
	int *my_arr = new int[length + 1];
	my_arr[0] = length;
	int token;
	for (int i = 1; i <= length; i++) {
		token = rand() % 3 - 1;   // generate number between -1~1
		my_arr[i] = token > 0 ? 1 : -1;
	}
	return my_arr;
}
double gaussrand() {
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else {
		X = V2 * sqrt(-2 * log(S) / S);
	}
	phase = 1 - phase;

	return X;
}
double* add_noise(int delta, int length) {
	double *my_arr = new double[length + 1];
	for (int i = 1; i <= length; i++) {
		my_arr[i] = gaussrand();
	}
	return my_arr;
}
int* BPSK_func(int* int_arr, double* double_arr) {
	int length = int_arr[0];
	int *return_arr = new int[length + 1];
	return_arr[0] = length;
	for (int i = 1; i <= length; i++) {
		return_arr[i] = abs(double_arr[i] + int_arr[i] - 1) > abs(double_arr[i] + int_arr[i] + 1) ? -1 : 1;
	}
	return return_arr;
}
int main()
{
	int *origin_arr = generator();
	double *noise_arr = add_noise(0, origin_arr[0]);
	int *BPSK_arr = BPSK_func(origin_arr, noise_arr);
	int length = BPSK_arr[0];
	int error_num = 0;
	for (int i = 1; i <= length; i++) {
		if (BPSK_arr[i] != origin_arr[i]) {
			error_num++;
		}
	}
	double error_rate = (double)error_num / (double)length;
	cout << error_rate << endl;
	int i;
	cin >> i;
	return 0;
}*/
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
	temp.SetSeed(0);
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
		cout << delta[i] << endl;
	}
	fstream DataWriter;
	DataWriter.open("data.txt", ios::out);
	if (!DataWriter) {
		cout << "Create File Error" << endl;
		exit(0);
	}
	DataWriter << "Es/No       Bit-Error Probability" << endl;
	cout << "Es/No" << "       Bit-Error Probability" << endl;
 	for (int i = 2; i < 100; i++) {
		int total_error = 0;
		for (int j = 0; j < 1000000; j++) {
			int *source_arr = generator(L);
			int *encode_arr = encode(source_arr, L);
			double *total_arr = add_noise(encode_arr, L, delta[i]);
			int *decode_arr = decode(total_arr, L);
			total_error += error_num(source_arr,decode_arr,L);
		}
		cout.precision(20);
		cout << "X: " << E_No[i] << ",               " << "Y: " << total_error << "*10^(-9)" << endl;
		DataWriter << E_No[i] << "         " << total_error << "\n";
	}
	DataWriter.close();
	system("pause");
}