	char *new_mas = new char[new_size];
	int i;
	if(new_size >= size) {
		for(i = 0; i < size; i++) {
			new_mas[i] = str[i];
		}
		while(i < new_size) {
			new_mas[i] = '\0'; 
			i++;
		}
	}
	else {
		for(i = 0; i < new_size; i++) {
			new_mas[i] = str[i];
		}
	}

	delete [] str;
	return new_mas;
