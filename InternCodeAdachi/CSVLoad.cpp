#include "CSVLoad.h"

using namespace std;

std::string ReadDataFromCSV(const char* _FileName, unsigned int ReadRow)
{
	// ファイルが存在するか確認
	ifstream Check(_FileName);
	bool fileIsEmpty = Check.peek() == ifstream::traits_type::eof();
	if (fileIsEmpty)
	{
		cout << "ファイルを開けませんでした" << endl;
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
