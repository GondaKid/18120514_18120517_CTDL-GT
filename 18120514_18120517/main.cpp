#include "Bool.h"

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}


void print_options()
{
	cout
		<< "\n1. Boole"
		<< "\n\n--------------MATRIX----------------"
		<< "\n2.Nhap du lieu cho A"
		<< "\n3.Nhap du lieu cho B"
		<< "\n4. Xem du lieu A va Det(A)"
		<< "\n5. Xem du lieu B vaf Det(B)"
		<< "\n6.Nghich dao ma tran A"
		<< "\n7.Nghich dao ma tran B"
		<< "\n8.Tinh A*B"
		<< "\n9.Rank A"
		<< "\n10.Rank B"
		<< "\n11.Giai he phuong trinh tuyen tinh"
		<< "\n\n--------------VECTOR------------------"
		<< "\n12.Nhap du lieu cho A"
		<< "\n13.Nhap du lieu cho B"
		<< "\n14. Xem du lieu A"
		<< "\n15. Xem du lieu B"
		<< "\n16. Tinh const*A"
		<< "\n17. Tinh const*B"
		<< "\n18. Tinh A + B"
		<< "\n0.EXIT"
		<< "\n\nSelect: ";

}

int main()
{
	resizeConsole(1000, 800);
	Matrix A;
	Matrix B;
	Vector C;
	Vector D;
	Vector temp;
	float Const;

	int select;
	do
	{
		system("cls");
		print_options();
		cin >> select;

		if (select == 0) { // EXIT PROGRAM
			return 1; 
		}
		else if (select == 1) { // process Boole function
			
			system("cls");
			QuineMccluskey qmc;
			qmc.main_loop();
		
		}
		
		else if (select == 2) { // input data A
			
			A.clear();
			cin >> A;
		
		}
		
		else if (select == 3) { // input data B
			
			B.clear();	
			cin >> B;
		
		}
		
		else if (select == 4) { //output A and det(A)

			if (A.Is_empty()) cout << "A is empty";
			else {
				cout << A;
				if (A.row == A.col) {
					cout << "\n\nDet A = " << A.det();
				}
				else {
					cout << "\n\nnon-exist Det";
				}
			}
		}
		
		else if (select == 5) { //output B and det(B)
		
			if (B.Is_empty()) cout << "B is empty";
			else {
				cout << B;
				if (B.row == B.col) {
					cout << "\n\nDet B = " << B.det();
				}
				else {
					cout << "\n\nnon-exist Det";
				}
			}
		
		}

		else if (select == 6) { //reverse A
		
			if (A.Is_empty()) {
				cout << "Chua Nhap du lieu cho A";
			}
			else if (A.row != A.col) {
				cout << "Chi tim cho ma tran vuong";
			}
			else if (A.det() == 0.0) {
				cout << "Khong co ma tran nghich dao";
			}
			else {
				Matrix ReverseA = A.inverse();
				cout << ReverseA;
			}
		
		}
		
		else if (select == 7) { //reverse B
		
			if (B.Is_empty()) {
				cout << "Chua Nhap du lieu cho B";
			}
			else if (B.row != B.col) {
				cout << "Chi tim cho ma tran vuong";
			}
			else if (B.det() == 0.0) {
				cout << "Khong co ma tran nghich dao";
			}
			else {
				Matrix ReverseB = B.inverse();
				cout << ReverseB;
			}
		
		}
		
		else if (select == 8) { // A * B
		
			if (A.Is_empty()   )   cout << "\nA is empty";
			if (B.Is_empty()   )   cout << "\nB is empty";
			if (A.col != B.row )   cout << "\nERROR: colA != rowB";
			else{
				Matrix C =  A * B;
				cout << C;
			}
		
		}
		
		else if (select == 9) { //rank A
		
			if (A.Is_empty()) cout << "A is empty";
			else cout << "rank A = " << A.rank() << endl;
		
		}
		
		else if (select == 10) { // rank B
		
			if (B.Is_empty()) cout << "B is empty";
			else cout << "rank B = " << B.rank() << endl;
		
		}
		
		else if (select == 11) { //giai he phuong trinh tuyen tinh
			
			Matrix::solve();
		
		}
		
		else if (select == 12) { // input C
		
			C.clear();
			cin >> C;
		}
		
		else if (select == 13) { // input D

			D.clear();
			cin >> D;
		
		}
		
		else if (select == 14) { // output C
			
			if (C.is_empty()) cout << "C is empty";
			else              cout << C;
		
		}
		
		else if (select == 15) { // output D
			if (D.is_empty()) cout << "D is empty";
			else              cout << D;
		}
		
		else if (select == 16) {
		
			if (C.is_empty()) cout << "C is empty";
			else {
				cout << "input constant: "; cin >> Const;
				temp = C * Const;
				cout << Const << " * C = " << temp;
			}
		}
		
		else if (select == 17) {
			
			if (D.is_empty()) cout << "D is empty";
			else {
				cout << "input constant: "; cin >> Const;
				temp = D * Const;
				cout << Const << " * D = " << temp;
			}
		}
		
		else if (select == 18) {
		
			if (C.is_empty()) cout << "C is empty";
			if (D.is_empty()) cout << "\nD is empty";
			else if (!(C.is_empty() && D.is_empty())) {
				temp = C + D;
				cout << "C + D = " << temp;
			}
		}

		cout << endl;
		system("pause");
	} while (!false);

	return 0;
}