// sodoco.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Sudoku {
	
public:
	int table[9][9];
	void setTable(int a[9][9]);
	void set(int game[9][9][10]);
	bool checkRow(int row, int number);
	bool checkColumn(int column, int number);
	bool checkArea(int row, int column, int number);
	void possibility(int game[9][9][10], int number);
	int solveRow(int game[9][9][10], int number);
	int solveColumn(int game[9][9][10], int number);
	int solveArea(int game[9][9][10], int number);
	void print(int a[9][9]);
};

void Sudoku::setTable(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			table[i][j] = a[i][j];
		}
	}
}

void Sudoku::print(int a[9][9]) {
	for (int i = 0; i < 9; i++) {
		std::cout << "-----------------------------------" << "\n";
		for (int j = 0; j < 9; j++) {
			std::cout << a[i][j] << " | ";
		}
		std::cout << "\n";
	}
	std::cout << "-----------------------------------" << "\n";
}


void Sudoku::set(int game[9][9][10]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int z = 0; z <= 9; z++) {
				game[i][j][z] = table[i][j];
			}
		}
	}
}


bool Sudoku::checkRow(int row, int number) {
	for (int i = 0; i <= 9; i++) {
		if (table[row][i] == number)
			return false;
	}
	return true;
}


bool Sudoku::checkColumn(int column, int number) {
	for (int i = 0; i <= 9; i++) {
		if (table[i][column] == number)
			return false;
	}
	return true;
}


bool Sudoku::checkArea(int row, int column, int number) {
	int i = 0, j = 0;
	while (i <= 8) {
		i += 3;
		while (j <= 8) {
			j += 3;
			if (row >= i - 3 && row <= i) {
				if (column >= j - 3 && column <= j) {
					int k = i - 3;
					int z = j - 3;
					while (k <= i) {
						while (z <= j) {
							if (table[k][z] == number)
								return false;
							z++;
						}
						k++;
					}
				}
				return true;
			}

		}
	}

}


void Sudoku::possibility(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i++) {
		if (checkRow(i, number)) {
			for (int j = 0; j < 9; j++) {
				if (table[i][j] == 0) {
					if (checkColumn(j, number) && checkArea(i, j, number)) {
						game[i][j][number] = number;
					}
				}
			}
		}
	}
}


int Sudoku::solveRow(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i++) {
		if (checkRow(i, number)) {
			int counter = 0, temp = 0;
			for (int j = 0; j < 9; j++) {
				if (game[i][j][number] == number) {
					counter++;
					temp = j;
				}
			}
			if (counter == 1) {
				table[i][temp] = number;
				possibility(game, number);
				return 1;
			}
		}
	}
	return 0;
}

int Sudoku::solveColumn(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i++) {
		if (checkColumn(i, number)) {
			int counter = 0, temp = 0;
			for (int j = 0; j < 9; j++) {
				if (game[j][i][number] == number) {
					counter++;
					temp = j;
				}
			}
			if (counter == 1) {
				table[temp][i] = number;
				possibility(game, number);
				return 1;
			}
		}
	}
	return 0;
}


int Sudoku::solveArea(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			if (checkArea(i, j, number)) {
				int counter = 0, temprow = 0, tempcol = 0;
				for (int k = 0; k < 3; k++) {
					for (int z = 0; z < 3; z++) {
						if (game[i + k][j + z][number] == number) {
							counter++;
							tempcol = j + z;
							temprow = i + k;
						}
					}
				}
				if (counter == 1) {
					table[temprow][tempcol] = number;
					possibility(game, number);
					return 1;
				}
			}
		}
	}
	return 0;
}



int main()
{

	int t[9][9] = {
		{1 , 6 , 5 , 4 , 0 , 0 , 2 , 3 , 0} ,
		{4 , 2 , 0 , 3 , 2 , 0 , 0 , 0 , 5} ,
	    {7 , 0 , 3 , 2 , 5 , 0 , 4 , 6 , 1} ,
		{2 , 1 , 6 , 5 , 0 , 3 , 0 , 0 , 4} ,
		{0 , 3 , 4 , 1 , 0 , 0 , 5 , 0 , 2} ,
		{0 , 5 , 7 , 0 , 4 , 2 , 3 , 1 , 6} ,
		{0 , 7 , 1 , 0 , 2 , 4 , 6 , 5 , 3} ,
		{5 , 4 , 0 , 6 , 3 , 1 , 0 , 2 , 0} ,
		{3 , 6 , 2 , 0 , 0 , 5 , 1 , 4 , 0}
	};

	int g[9][9][10];
	int rowResult = 0, columnResult = 0, areaResult = 0
		;
	Sudoku s;

	s.setTable(t);
	s.set(g);

	while (true) {
		rowResult = columnResult = areaResult = 0;
		for (int i = 0; i < 9; i++) {
			rowResult += s.solveRow(g, i);
			columnResult += s.solveColumn(g, i);
			areaResult += s.solveArea(g, i);
		}
		if (rowResult == 0 && columnResult == 0 && areaResult == 0) {
			break;
		}
		else {
			//s.print(s.table);
		}
	}

	s.print(s.table);
	return 0;
}

