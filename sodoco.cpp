// sodoco.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Sudoku {
	private:
		int table[9][9];
	public:
		void set(int game[9][9][10]);
		bool checkRow(int row,int number);
		bool checkColumn(int column, int number);
		bool checkArea(int row, int column, int number);
		void possibility(int game[9][9][10], int number);
		void solveRow(int game[9][9][10], int number);
		void Sudoku::solveColumn(int game[9][9][10], int number);
		void Sudoku::solveArea(int game[9][9][10], int number);
};
void Sudoku::set(int game[9][9][10]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9 ; j++) {
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
	int i=0, j=0;
	while (i <= 8) {
		i += 3;
		while (j<=8) {
			j+=3;
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
					if (checkColumn(j, number)&&checkArea(i,j,number)) {
						game[i][j][number] = number;
					}
				}
			}
		}
	}
}
void Sudoku::solveRow(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i++) {
		if (checkRow(i, number)) {
			int counter = 0, int temp = 0;
			for (int j = 0; j < 9; j++) {
				if (game[i][j][number] == number) {
					counter++;
					temp = j;
				}
			}
			if (counter == 1) {
				table[i][temp] = number;
				possibility(game, number);
			}
		}
	}
}
void Sudoku::solveArea(int game[9][9][10], int number) {
	for (int i = 0; i < 9; i += 3) {
		for (int j = 0; j < 9; j += 3) {
			if (checkArea(i, j, number)) {
				int counter = 0, int temprow = 0, int tempcol = 0;
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
				}
			}
		}
	}
}



int main()
{
    return 0;
}

