int ** transpose(const int * const *m, unsigned rows, unsigned cols) {

	int **matr = new int*[cols];
	matr[0] = new int[cols*rows];
	for (int i = 1; i < cols; i++) {
		matr[i] = matr[i - 1] + rows;
	}

	for(int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			matr[i][j] = m[j][i];
		}
	}

	return matr;
}
