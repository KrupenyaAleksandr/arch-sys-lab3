#include <iostream>
#include <locale.h>
#include <omp.h>
#include <random>
#include <vector>

void task1() {
	std::vector<int> A, B, C;
	int left = 10, right = 30;
	int count = rand() % (right - left + 1) + left;
	for (int i = 0; i < count; ++i) {
		A.push_back(rand() % 200);
		B.push_back(rand() % 200);
	}
	#pragma omp parallel shared(C) num_threads(2)
	{
		#pragma omp for
		for (int i = 0; i < count; ++i)
		{
			std::cout << "Номер потока: " << omp_get_thread_num() << ", номер рассчитанного элемента массива: " << i << std::endl;
			C.push_back(A[i] + B[i]);
		}
	}
	return;
}

void task2() {
	std::vector<int> A, B;
	int count = 100;
	for (int i = 0; i < count; ++i) {
		A.push_back(rand() % 20);
		B.push_back(rand() % 20);
	}
	int sum = 0;
	#pragma omp parallel for reduction(+: sum) num_threads(2)
	for (int i = 0; i < count; ++i)
	{
		sum += A[i] * B[i];
		std::cout << "Номер потока: " << omp_get_thread_num() << ", sum = " << sum << std::endl;
	}
	std::cout << "Конечная сумма: " << sum << std::endl;
}

void task3() {
	const int SIZE = 8;
	std::vector<int> A(SIZE), C(SIZE);
	std::vector<std::vector<int>> matrix(SIZE, std::vector<int>(SIZE));
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < SIZE; ++i) A[i] = rand() % 20;
	#pragma omp parallel for num_threads(2)
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			matrix[i][j] = rand() % 20;
			C[i] += matrix[i][j] * A[j];
			std::cout << "Номер потока: " << omp_get_thread_num() << ", C[" << i << "]: " << C[i] << std::endl;
		}
	}
	std::cout << "\nИсходный вектор A: ";
	for (int i = 0; i < SIZE; ++i) {
		std::cout << A[i] << " ";
	}
	std::cout << "\n\nИсходная матрица B:\n\n";
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\nРезультирующий вектор C: ";
	for (int i = 0; i < SIZE; ++i) {
		std::cout << C[i] << " ";
	}
	std::cout << "\n";
}

void task4() {
	#pragma omp parallel num_threads(9)
	{
		#pragma omp for ordered
		for (int i = 0; i < 9; ++i) {
			#pragma omp ordered
			{
				for (int j = 0; j < 9; ++j) {
					std::cout << (j + 1) * (i + 1) << " ";
				}
				std::cout << "\n";
			}
		}
	}
}

#ifdef _OPENMP
int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	//task1(); 
	//task2();
	//task3();
	//task4();
	return 0;
}
#endif