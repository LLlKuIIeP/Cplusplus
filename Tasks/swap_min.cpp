void swap_min(int *m[], unsigned rows, unsigned cols) {
	unsigned int index = rows;
	int min_elem = m[0][0];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if(m[i][j] < min_elem) {
				index = i;
				min_elem = m[i][j];
			}
		}
	}

	int *p = m[0];
	m[0] = m[index];
	m[index] = p;
}
