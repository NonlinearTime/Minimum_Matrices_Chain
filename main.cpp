#include <iostream>
#include <windows.h>


using namespace std;

struct Matrix{
	uint64_t row;
	uint64_t col;
};

class Solution{
	int num;
	uint64_t best_solution;
	uint64_t  MAX = 0xFFFFFFFFFFFFFFFF;
	int **record;
	uint64_t **subVal;
	Matrix *matrices;
public:
	Solution(int n);
	uint64_t getSol();
	void Minimum_Chain();
	void print();
	void helper(int row , int col);
};


Solution::Solution(int n):num(n) {
	matrices = new Matrix[n];
	record = new int*[n];
	subVal = new uint64_t*[n];
	best_solution = MAX;
	uint64_t row,col;
	for (int i = 0 ; i != n ; ++i) {
		cin >> row >> col;
		record[i] = new int[n];
		subVal[i] = new uint64_t[n];
		matrices[i].row = row;
		matrices[i].col = col;
		for (int j = 0 ; j != n ; ++j) {
			record[i][j] = 0;
			if (i == j) subVal[i][j] = 0;
			//else if (j == i + 1) {
			//	subVal[i][j] = matrices[i].row * matrices[i].col * matrices[j].col;
			//}
			else {
				subVal[i][j] = MAX;
			}
		}
	}
	//cout << record[0][0] << matrices[0].row << matrices[0].col;
}

uint64_t Solution::getSol() {
	Minimum_Chain();
	return best_solution;
}

void Solution::print() {
	helper(0,num-1);
}

void Solution::Minimum_Chain() {
	int len,left,mid;
	for (len = 1 ; len != num ; ++len) {
		for (left = 0; left != num - len ; ++left) {
			int right = left + len;
			for (mid = left ; mid != right; ++mid) {
				if (subVal[left][mid] == MAX || subVal[mid+1][right] == MAX) continue;
				uint64_t  tmp = subVal[left][mid] + subVal[mid+1][right] + matrices[left].row * matrices[mid].col * matrices[right].col;
				//cout << tmp << endl;
				if (tmp < subVal[left][right]) {
					subVal[left][right] = tmp;
					record[left][right] = mid;
				}
			}
		}
	}
	best_solution = subVal[0][num - 1];
}

void Solution::helper(int row, int col) {
	if (row == col) {
		cout << row;
		return;
	}
	cout << "(" ;
	helper(row,record[row][col]);
	//cout << ")(";
	helper(record[row][col] + 1,col);
	cout << ")";
}

int main() {
	int n;
	while (cin >> n) {
		Solution solution(n);
		long long QPart1,QPart2;
		double dfMinus, dfFreq, dfTim;
		LARGE_INTEGER litmp;
		QueryPerformanceFrequency(&litmp);
		dfFreq = (double)litmp.QuadPart;
		QueryPerformanceCounter(&litmp);
		QPart1 = litmp.QuadPart;

		cout << "The least mul-times is :" << solution.getSol() << endl;
		cout << "The best solution :" << endl;
		solution.print();

		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;

		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus * 1000 /dfFreq;

		cout << "\nrun time :" << dfTim << "ms" << endl;
	}
	cout << "hello world!" << endl;
	return 0;
}