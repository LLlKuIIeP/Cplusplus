#define BUFF_SIZE 1024

char* resize(const char *str, unsigned size, unsigned new_size) {
	//cout << str << ": " << size << ", " << new_size << endl;
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
}


char* getline() {
	int i = 0;
	int k = 1;
	char *str = new char[BUFF_SIZE];
	char c = cin.get();
	while(c != '\n' && !cin.eof()) {
		str[i] = c;
		c = cin.get();
		i++;
		if(i == k * BUFF_SIZE) {
			str = resize(str, k * BUFF_SIZE, (k + 1) * BUFF_SIZE);
			k++;
		}
	}
	str[i] = '\0';
	i++;
	return resize(str, i, i);
}
