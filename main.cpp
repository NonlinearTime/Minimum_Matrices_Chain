#include <iostream>
#include <windows.h>


using namespace std;

struct Matrix{                          //Matrix definition
	uint64_t row;
	uint64_t col;
};

class Solution{
	int num;
	uint64_t best_solution;
	uint64_t  MAX = 0xFFFFFFFFFFFFFFFF;//use MAX as infinity
	int **record;
	uint64_t **subVal;
	Matrix *matrices;
public:
	Solution(int n);
	uint64_t getSol();                  //get the solution
	void Minimum_Chain();               //compute
	void print();                       //print the solution
	void helper(int row , int col);     //help print
};


Solution::Solution(int n):num(n) {
	matrices = new Matrix[n];
	record = new int*[n];
	subVal = new uint64_t*[n];
	best_solution = MAX;
	uint64_t row,col;
	for (int i = 0 ; i != n ; ++i) {    //get the matrices chain from keyboard and initial
		cin >> row >> col;
		record[i] = new int[n];
		subVal[i] = new uint64_t[n];
		matrices[i].row = row;
		matrices[i].col = col;
		for (int j = 0 ; j != n ; ++j) {
			record[i][j] = 0;
			if (i == j) subVal[i][j] = 0;
			else {
				subVal[i][j] = MAX;
			}
		}
	}
}

uint64_t Solution::getSol() {
	Minimum_Chain();
	return best_solution;
}

void Solution::print() {
	helper(0,num-1);
}

void Solution::Minimum_Chain() {        //use dp
	int len,left,mid;
	for (len = 1 ; len != num ; ++len) {
		for (left = 0; left != num - len ; ++left) {
			int right = left + len;
			for (mid = left ; mid != right; ++mid) {
				if (subVal[left][mid] == MAX || subVal[mid+1][right] == MAX) continue;  //skip the max value to avoid overflow
				uint64_t  tmp = subVal[left][mid] + subVal[mid+1][right]
				                + matrices[left].row * matrices[mid].col * matrices[right].col;
				//cout << tmp << endl;
				if (tmp < subVal[left][right]) {    //update the best solution of sub problem
					subVal[left][right] = tmp;
					record[left][right] = mid;
				}
			}
		}
	}
	best_solution = subVal[0][num - 1];
}

void Solution::helper(int row, int col) {   //print result by recursion
	if (row == col) {
		cout << row;
		return;
	}
	cout << "(" ;
	helper(row,record[row][col]);
	helper(record[row][col] + 1,col);
	cout << ")";
}

int main() {
	int n;
	while (cin >> n) {
		Solution solution(n);               //instantiation the solution class
		long long QPart1,QPart2;
		double dfMinus, dfFreq, dfTim;
		LARGE_INTEGER litmp;
		QueryPerformanceFrequency(&litmp);  //get system clock frequency
		dfFreq = (double)litmp.QuadPart;
		QueryPerformanceCounter(&litmp);    //get system clock tick num when the process begin
		QPart1 = litmp.QuadPart;

		cout << "\nThe least mul-times is :" << solution.getSol() << endl;    //output the solution
		cout << "The best solution :" << endl;


		QueryPerformanceCounter(&litmp);    //get system clock tick num when the process end
		QPart2 = litmp.QuadPart;

		dfMinus = (double)(QPart2-QPart1);
		dfTim = dfMinus * 1000000/dfFreq;   //print runtime
		solution.print();                   //print solution

		cout << "\nrun time :" << dfTim << "us" << endl;
	}
	return 0;
}