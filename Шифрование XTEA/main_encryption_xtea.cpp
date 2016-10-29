#include "Encryption_XTEA.h"

int main()
{
	const int number_bits = 2 * sizeof(long);			// 64 bit;
	string NameInFile, NameOutFile, Key;
	
	cout << "Enter names input file, output file and key:\n";
	cin >> NameInFile >> NameOutFile >> Key;
	//NameInFile = "File1.txt";		NameOutFile = "File2.txt";		 Key = "bs";  

	ifstream InputFile(NameInFile.c_str());
	ofstream OutputFile(NameOutFile.c_str());	
	if (!InputFile || !OutputFile) {
		cerr << ("Error: File(s) not found.") << endl; }

	// If size Key < 128 bit
	while (Key.size() < 2 * number_bits) {
		Key += '0'; }
	
	const unsigned long* k = reinterpret_cast<const unsigned long*>(Key.data());
	char Buffer[number_bits];
    
	unsigned long* InputBuf = reinterpret_cast<unsigned long*>(Buffer);
	unsigned long OutputBuf[2];

	OutputFile << hex; // èñïîëüçóåòñÿ øåñòíàäöàòåðè÷íûé âûâîä  
	int count = 0;
 
	while (InputFile.get(Buffer[count])) {
		if (++count == number_bits) {
			Encipher(InputBuf, OutputBuf, k);               // çàïîëíåíèå âåäóùèìè íóëÿìè:               
			OutputFile << setw(8) << setfill('0') << OutputBuf[0] << ' '
						<< setw(8) << setfill('0') << OutputBuf[1] << ' ';
			count = 0;          
		}     
	}     
	
	if (count) { // çàïîëíåíèå           
		while (count != number_bits) {
			Buffer[count++] = '0';
		}
		Encipher(InputBuf, OutputBuf, k);
		OutputFile << OutputBuf[0] << ' ' << OutputBuf[1] << ' ';
	} 

	system("pause");
	return 0;
}
