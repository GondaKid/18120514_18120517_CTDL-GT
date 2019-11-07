#include "Bool.h"
//FUNCTION SUPPORT ----------------------------------------------------------
int nVar = 0;

string Table_2_Var[9] = { "  ", "b ", "B",
							 "a ", "0 ", "1",
							 "A ", "2 ", "3" };

string Table_3_Var[15] = { "   ", "c ", "C",
							 "ab ", "0 ", "1",
							 "aB ", "2 ", "3",
							 "AB ", "6 ", "7",
							 "Ab ", "4 ", "5" };

string Table_4_Var[25] = { "   ", "cd ", "cD ", "CD ", "Cd",
						   "ab ", " 0 ", " 1 ", " 3 ", " 2",
						   "aB ", " 4 ", " 5 ", " 7 ", " 6",
						   "AB ", "12 ", "13 ", "15 ", "14",
						   "Ab ", " 8 ", " 9 ", "11 ", "10" };

string Table_5_Var[45] = {   "    ","de ","dE ","DE ","De",
                             "abc "," 0 "," 1 "," 3 "," 2",
							 "abC "," 4 "," 5 "," 7 "," 6",
							 "aBC ","12 ","13 ","15 ","14",
							 "aBc "," 8 "," 9 ","11 ","10",
							 "Abc ","16 ","17 ","19 ","18",
							 "AbC ","20 ","21 ","23 ","22",
							 "ABC ","28 ","29 ","31 ","30",
							 "ABc ","24 ","25 ","27 ","26",};

string Table_6_Var[81] = { "    ", "def ","deF ","dEF ","dEf ","Def ", "DeF ","DEF ","DEf",
							 "abc ", "  0 ","  1 ","  3 ","  2 ","  4 ", "  5 ","  7 ","  6",
							 "abC ", "  8 ","  9 "," 11 "," 10 "," 12 ", " 13 "," 15 "," 14",
							 "aBC ", " 24 "," 25 "," 27 "," 26 "," 28 ", " 29 "," 31 "," 30",
							 "aBc ", " 16 "," 17 "," 19 "," 18 "," 20 ", " 21 "," 23 "," 22",
							 "Abc ", " 32 "," 33 "," 35 "," 34 "," 36 ", " 37 "," 39 "," 38",
							 "AbC ", " 40 "," 41 "," 43 "," 42 "," 44 ", " 45 "," 47 "," 46",
							 "ABC ", " 56 "," 57 "," 59 "," 58 "," 60 ", " 61 "," 63 "," 62",
							 "ABc ", " 48 "," 49 "," 51 "," 50 "," 52 ", " 53 "," 55 "," 54" };

void PrintTable_Var(string	*Table, int row, int col)
{
	for (int i = 0; i < row*col; i++) {
		if (i > 0 && i % col == 0) {
			cout << endl;
			/*for (int j = 0; j < col; j++)
				cout << "---";*/
			cout << endl;
		}
		cout << Table[i] << "|";
	}
}

arr1D INT_to_Binary(int a)
{
	arr1D bin(nVar);
	for (int i = nVar - 1; i >= 0; i--)
	{
		bin[i] = a % 2;
		a /= 2;
	}
	return bin;
}

int count_value_1_in_Binary(arr1D bin)
{
	int count = 0;
	for (int i = 0; i < nVar; i++)
		if (bin[i] == 1) count++;

	return count;
}

bool cmp_Binary(arr1D bin1, arr1D bin2) // count amount the different among bin1 & bin2
{
	int countDiff = 0;
	for (int i = 0; i < nVar; i++)
		if (bin1[i] != bin2[i]) countDiff++;

	return countDiff == 1;
}

arr1D get_Different(arr1D bin1, arr1D bin2)
{
	arr1D newBin(nVar);
	for (int i = 0; i < nVar; i++)
		if   (bin1[i] == bin2[i])   newBin[i] = bin1[i];
		else /*bin[i] != bin2[i]*/  newBin[i] = -1;

	return newBin;

}

string Bin_to_String(arr1D bin)
{
	string str;
	for (int i = 0; i < nVar; i++)
		if      (bin[i] == 1) str.push_back(char('A' + i));
		else if (bin[i] == 0) str.push_back(char('a' + i));

	return str;
}

bool primeInclude(arr1D ipc, arr1D minTerm)
{
	// check is a prime implicant satisfies a min term or not
	for (int i = 0; i < ipc.size(); ++i) {
		if (ipc[i] != -1) {
			if (ipc[i] != minTerm[i]) 
				return false;
		}
	}
	return true;
}

int Get_Variable(arrVal1D combination, group primeIpc)
{
	// returns the number of variables in a petrick method combination
	int count = 0;
	arrVal1D ::iterator itr;
	for (itr = combination.begin(); itr != combination.end(); ++itr) {
		int imp = *itr;
		for (int i = 0; i < primeIpc[imp].size(); ++i) {
			if (primeIpc[imp][i] != -1)
				count++;
		}
	}
	return count;
}

void outputBinary(arr1D bin)
{
	for (int i = 0; i < nVar; i++)
		cout << bin[i];
}

bool is_TableEmpty(Table table)
{
	for (int i = 0; i < table.size(); i++)
		if (table[i].size() != 0)
			return false;
	return true;
}
//CLASS --------------------------------------------------------------------------------
void QuineMccluskey::input()
{
INPUT:
	cout << "\ninput Variable: "; cin >> nVar;
	if     (nVar == 2) PrintTable_Var(Table_2_Var, 3, 3);
	else if (nVar == 3) PrintTable_Var(Table_3_Var, 5, 3);
	else if (nVar == 4) PrintTable_Var(Table_4_Var, 5, 5);
	else if (nVar == 5) PrintTable_Var(Table_5_Var, 9, 5);
	else if (nVar == 6) PrintTable_Var(Table_6_Var, 9, 9);

	cout << "\n\ninput termMin(0 <= termMin <= " << pow(2, nVar) - 1 << "):\n";
	string str;
	cin.ignore(256, '\n');
	getline(cin, str);

	vector<string>token;
	string item;
	int lenStr = str.length();
	
	//get token digit
	for (int i = 0; i < lenStr; i++)
	{
		if (str[i] == ' ' && str[i + 1] != ' ') {
			token.push_back(item);
			item.clear();
		}
		else if (str[i] != ' ')
		{
			item.push_back(str[i]);
		}
	}
	token.push_back(item);
	int nToken = token.size();

	//get minTerm
	int X;
	for (int i = 0; i < nToken; i++) {
		X = stoi(token[i]);
		if (X >= 0 && X <= pow(2, nVar) - 1)
			minTerm.push_back(X);
	}

	// delete the same values
	sort(minTerm.begin(), minTerm.end());
	for (int i = 0; i < minTerm.size() - 1; i++) 
	{
		if (minTerm[i] == minTerm[i + 1])
		{
			minTerm.erase(minTerm.begin() + i);
			i--;
		}
	}

	n_minTerm = minTerm.size();
	cout << "\nnot A = a, not B = b, ...";
}

void QuineMccluskey::Init_minBinary()
{
	for (int i = 0; i < n_minTerm; i++)
		minBinary.push_back(INT_to_Binary(minTerm[i]));

	cout << "\n\n-----STEP 1: init term to Binary-----\n";
	for (int i = 0; i < n_minTerm; i++) {
		cout << minTerm[i] << '\t'; outputBinary(minBinary[i]);
		cout << endl;
	}
}

void QuineMccluskey::Init_Table()
{
	table.resize(nVar + 1);
	int count_1;
	for (int i = 0; i < n_minTerm; ++i) {
		count_1 = count_value_1_in_Binary(minBinary[i]);
		table[count_1].push_back(minBinary[i]);
	}

	cout << "\n-----STEP 2: Init Group-----" << endl;
	for (int i = 0; i < nVar + 1; ++i) {
		cout << i << ")  ";
		for (int j = 0; j < table[i].size(); ++j) {
			outputBinary(table[i][j]); cout << ", ";
		}
		cout << endl;
	}
}
Table QuineMccluskey::combine_minterms(Table table, set<arr1D>& primeIpc)
{
	bool **checked;
	checked = new bool*[table.size()];
	for (int i = 0; i < table.size(); i++)
		checked[i] = new bool [n_minTerm] { false };
	Table newTable(table.size() - 1);


	for (int i = 0; i < table.size() - 1; ++i) {
		for (int j = 0; j < table[i].size(); ++j) {
			for (int k = 0; k < table[i + 1].size(); k++) {
				if (cmp_Binary(table[i][j], table[i + 1][k])) {
					newTable[i].push_back(get_Different(table[i][j], table[i + 1][k]));
					checked[i][j] = true;
					checked[i + 1][k] = true;
				}
			}
		}
	}

	for (int i = 0; i < table.size(); ++i) {
		for (int j = 0; j < table[i].size(); ++j) {
			if (!checked[i][j]) {
				primeIpc.insert(table[i][j]);
			}
		}
	}

	return newTable;
}

void QuineMccluskey::Init_PrimeIpc()
{
	set<arr1D> primeIpc_Temp;
	while (!is_TableEmpty(table)) {
		table = combine_minterms(table, primeIpc_Temp);
	}
	set<arr1D>::iterator idex;
	for (idex = primeIpc_Temp.begin(); idex != primeIpc_Temp.end(); idex++) {
		PrimeIpc.push_back(*idex);
	}

	cout << "\n-----STEP 3: finding prime implicants-----" << endl;
	for (int i = 0; i < PrimeIpc.size(); ++i) {
		cout << "cell_"<< i << ": " << Bin_to_String(PrimeIpc[i]) << endl;
	}
}

void QuineMccluskey::get_All_expression_Combination(vector<arrVal1D> &posValid, arrVal1D posCombination_1D,
	arrVal2D& posCombination_2D, int amount = 0)
{
	// a recursive function to multiple elements of set patLogic and store it in set posComb
	if (amount == posValid.size()) {
		arrVal1D elm = posCombination_1D;
		posCombination_2D.insert(elm);
		return;
	}
	else {
		set<int > ::iterator itr;
		for (itr = posValid[amount].begin(); itr != posValid[amount].end(); ++itr) {

			int x = *itr;
			bool inserted = posCombination_1D.insert(x).second; // checked x that has been exist in posCombination_1D
			get_All_expression_Combination(posValid, posCombination_1D, posCombination_2D, amount + 1);
			if (inserted) {
				posCombination_1D.erase(x);
			}
		}
	}
}

void QuineMccluskey::prime_implicant_chart()
{
	// create a table check
	bool **TableCheck;
	TableCheck = new bool*[PrimeIpc.size()];
	for (int i = 0; i < PrimeIpc.size(); ++i)
		TableCheck[i] = new bool[n_minTerm] {false};
	
	cout << "\n-----STEP 4: Create Table Check-----\n";
	for (int i = 0; i < PrimeIpc.size(); i++) {
		for (int j = 0; j < n_minTerm; j++) {
			TableCheck[i][j] = primeInclude(PrimeIpc[i], minBinary[j]);
			cout << (int)TableCheck[i][j] << '\t';
		}
		cout << endl;
	}

	//Save positives i in column that Check[i][row] = 1
	vector<arrVal1D>posValid;
	arrVal1D temp;
	for (int iCol = 0; iCol < n_minTerm; iCol++) {
		temp.clear();
		for (int iRow = 0; iRow < PrimeIpc.size(); iRow++)
			if (TableCheck[iRow][iCol] == 1)
				temp.insert(iRow);
		posValid.push_back(temp);
	}

	// get All expression
	arrVal2D posCombination_2D;
	arrVal1D posCombination_1D;
	get_All_expression_Combination(posValid, posCombination_1D, posCombination_2D);

	//get size min avaribles and output all combination satisfy
	int min = INT_MAX;
	cout << "\nPossible combinations that satisfy all minterms:" << endl;
	arrVal2D ::iterator itr1;
	for (itr1 = posCombination_2D.begin(); itr1 != posCombination_2D.end(); ++itr1) {
		if (itr1->size() < min) {
			min = itr1->size();
		}
		arrVal1D ::iterator itr;
		for (itr = itr1->begin(); itr != itr1->end(); ++itr) {
			cout << "cell_"<< *itr << " + ";
		}
		cout << "\b\b \n";
	}
	//get all min combinatio
	vector< arrVal1D > minComb;
	set< set<int> > ::iterator itr;
	for (itr = posCombination_2D.begin(); itr != posCombination_2D.end(); ++itr) {
		if (itr->size() == min) {
			minComb.push_back(*itr);
		}
	}

	//Combinations with minimum variables
	min = INT_MAX; int a;
	for (int i = 0; i < minComb.size(); ++i) {
		a = Get_Variable(minComb[i], PrimeIpc);
		if (a < min)
			min = a;
	}

	for (int i = 0; i < minComb.size(); ++i) {
		a = Get_Variable(minComb[i], PrimeIpc);
		if (a == min)
			expression.push_back(minComb[i]);
	}
}

void QuineMccluskey::output_minimize_expression()
{
	cout << "\n-----RESULT-----\n";
	arrVal1D::iterator itr;
	for (int i = 0; i < expression.size(); ++i) {
		for (itr = expression[i].begin(); itr != expression[i].end(); ++itr) {
			cout << Bin_to_String(PrimeIpc[*itr]) << " + ";
		}
		cout << "\b\b \n" << endl;
	}
}

void QuineMccluskey::main_loop()
{
	input();
	Init_minBinary();
	Init_Table();
	Init_PrimeIpc();
	prime_implicant_chart();
	output_minimize_expression();
}