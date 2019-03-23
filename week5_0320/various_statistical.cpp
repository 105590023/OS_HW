#include <iostream>
#include <exception>
#include <thread>
#include <mutex>
#include <sstream>

using namespace std;

mutex gMutex;

bool isNum(char* str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

void InputData(int num, char** input, double* data)
{
	if(num <= 0 || !(isNum(input[1])))
	{
		throw "Please enter list of number.";
	}
	else
	{
		for(int i = 1; i <= num; i++)
		{
			*data++ = stod(input[i]);
		}
	}
}

void CountAverage(const int num, double* data)
{
	lock_guard<mutex> mLock(gMutex);
	double total = 0;
	for(int i = 0; i < num; i++)
	{
		total += *(data++);
	}
	cout << "The average value is " << total/num << endl;
}

void FindMaxNum(const int num, double* data)
{
	lock_guard<mutex> mLock(gMutex);
	double MaxNum = *(data++);
	for(int i = 1; i < num; i++)
	{
		if(MaxNum < (*data))
		{
			MaxNum = (*data);
		}
		data++;
	}
	cout << "The maximum value is " << MaxNum << endl;
}

void FindMinNum(const int num, double* data)
{
	lock_guard<mutex> mLock(gMutex);
	double MinNum = *(data++);
	for(int i = 1; i < num; i++)
	{
		if(MinNum > (*data))
		{
			MinNum = (*data);
		}
		data++;
	}
	cout << "The minimum value is " << MinNum << endl;
}

int main(int argc, char** argv)
{
	const int DATA_NUM = argc-1;
	double data[DATA_NUM];
	try
	{
		InputData(DATA_NUM, argv, data);
		
		thread AverageNum(CountAverage, DATA_NUM, &data[0]);
		thread MaxNum(FindMaxNum, DATA_NUM, &data[0]);
		thread MinNum(FindMinNum, DATA_NUM, &data[0]);
		AverageNum.join();
		MaxNum.join();
		MinNum.join();
	}
	catch(const char* error)
	{
		cout << error << endl;
	}
	
	return 0;
}
