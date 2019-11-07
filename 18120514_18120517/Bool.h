#pragma once
#include "Matrix.h"
typedef set<int> arrVal1D;
typedef vector<int> arr1D;
typedef vector<arr1D> group;
typedef vector<group>Table;
typedef vector< vector<bool> >TableCheck;
typedef set<arrVal1D> arrVal2D;



arr1D INT_to_Binary(int a);
int count_value_1_in_Binary(arr1D bin);
bool cmp_Binary(arr1D bin1, arr1D bin2);
arr1D get_Different(arr1D bin1, arr1D bin2);
string Bin_to_String(arr1D bin);
bool primeInclude(arr1D ipc, arr1D minTerm);
int Get_Variable(arrVal1D combination, group primeIpc);
void outputBinary(arr1D bin);
bool is_TableEmpty(Table table);
void PrintTable_Var(string	*Table, int row, int col);
class QuineMccluskey
{
private:
	arr1D minTerm;
	group minBinary;
	int n_minTerm;
	Table table;
	group PrimeIpc;
	vector<arrVal1D> expression;

public:
	void input();
	void Init_minBinary();
	void Init_Table();
	Table combine_minterms(Table table, set<arr1D>& primeIpc);
	void Init_PrimeIpc();
	void get_All_expression_Combination(vector<arrVal1D> &posValid, arrVal1D posCombination_1D, arrVal2D& posCombination_2D, int amount);
	void prime_implicant_chart();
	void output_minimize_expression();
	void main_loop();
};
