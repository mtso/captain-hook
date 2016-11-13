#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

const string DATAFILENAME = "./taskdata.txt";

void appendDate();
void resolveDatafile();

int main(int argc, char** argv)
{
	if (argc > 1) {
		if (strcmp(argv[1], "--resolve") == 0)
		{
			resolveDatafile();
		}
	}
	else {
		appendDate();
	}

	return 0;
}

void appendDate()
{
	ofstream output;
	output.open(DATAFILENAME, ios::app);

	time_t t = time(0);
	struct tm now;
	char datetime[32];

	localtime_s(&now, &t);
	asctime_s(datetime, &now);

	output << datetime << endl;
	output.close();

	cout << "Wrote " << datetime << "to ./taskdata.txt";
}

void resolveDatafile()
{
	vector<string> datalog;
	string input;
	bool containedConflict = false;

	ifstream data;
	data.open(DATAFILENAME);
	while (!data.eof()) 
	{
		getline(data, input);

		if (input.find("<<<<<<<") == string::npos &&
			input.find("=======") == string::npos &&
			input.find(">>>>>>>") == string::npos)
		{
			datalog.insert(datalog.begin(), input);
		}
		else
		{
			containedConflict = true;
		}
	}
	data.close();

	// Overwrite data file with clean task log
	ofstream overwrite;
	overwrite.open(DATAFILENAME);
	while (!datalog.empty()) {
		overwrite << datalog.at(datalog.size() - 1) << endl;
		datalog.pop_back();
	}
	overwrite.close();

	cout << (containedConflict ? "Cleaned task log of conflicts." : "Task log was clean.") << endl;
}