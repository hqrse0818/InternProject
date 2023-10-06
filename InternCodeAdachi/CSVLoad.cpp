#include "CSVLoad.h"

using namespace std;

std::string ReadDataFromCSV(const char* _FileName, unsigned int ReadRow)
{
	// �t�@�C�������݂��邩�m�F
	ifstream Check(_FileName);
	bool fileIsEmpty = Check.peek() == ifstream::traits_type::eof();
	if (fileIsEmpty)
	{
		cout << "�t�@�C�����J���܂���ł���" << endl;
	}

	string line;
	int currentRow = 0;
	while (getline(Check, line))
	{
		if (currentRow == ReadRow)
		{
			Check.close();
			return line;
		}
		currentRow++;
	}

	return "";
}
