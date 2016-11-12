#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
	ofstream output;
	output.open("./taskdata.txt", ios::app);

	time_t t = time(0);
	struct tm now;
	char datetime[32]; 
	
	localtime_s(&now, &t);
	asctime_s(datetime, &now);

	output << datetime << endl;
	output.close();

	cout << "Wrote " << datetime << "to ./taskdata.txt";
	return 0;
}