#include "Decipher_XTEA.h"

int main()
{
	const int number_bits = 2 * sizeof(long);			// 64 bit;
	string NameInFile, NameOutFile, Key;

	cout << "Enter names input file, output file and key:\n";
	cin >> NameInFile >> NameOutFile >> Key;
	//NameInFile = "inD.txt";		NameOutFile = "outD.txt";		 Key = "bs"; 

	ifstream InputFile(NameInFile.c_str());
	ofstream OutputFile(NameOutFile.c_str());
	if (!InputFile || !OutputFile) {
		cerr << ("Error: File(s) not found.") << endl; }

	// If size Key < 128 bit
	while (Key.size() < 2 * number_bits) {
		Key += '0'; }

	const unsigned long* k = reinterpret_cast<const unsigned long*>(Key.data());
	char Buffer[number_bits];
	unsigned long cd[2];
	//unsigned long* inptr1 = reinterpret_cast<unsigned long*>(cd);
	unsigned long outptr1[2];
	int count = 0;

	InputFile >> hex;

	while (InputFile >> cd[count]) {
		if (++count == 2) {
			decipher(cd, outptr1, k);

		for (unsigned int i = 0; i < number_bits / 2; i++) {
			Buffer[i] = static_cast<char>(outptr1[0] >> 8 * i);
		}

		for (unsigned int i = number_bits / 2; i < number_bits; i++) {
			Buffer[i] = static_cast<char>(outptr1[1] >> 8 * (i % 4));
		}

		for (unsigned int i = 0; Buffer[i] != '0' && i < 8; i++) {
			OutputFile << Buffer[i]; }
		count = 0;
		}
	}

	system("pause");
	return 0;
}
