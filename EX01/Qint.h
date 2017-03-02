#pragma once
#include<math.h>
#include<stack>
#include<string>
#include<bitset>
#include<iostream>
#include<sstream>
#include<boost\multiprecision\cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;
class Qint
{
private:
	long long arrayBits[2];
public:
	bool overFlow;
	Qint(long long val1, long long val2);
	Qint(long long val1, long long val2, bool over);
	Qint(int n);
	Qint();
	Qint(string array, int type);//type =2:string of binary 
								//type=10:string of decimal
								//type=16:string of heximal

	//Check overflow
	bool isOverFlow();
	//set overflow
	void setOverFlow(bool value);

	//Qint operation
	Qint operator+(const Qint& num);
	Qint operator-(const Qint& num);
	Qint operator*(const Qint& num);
	Qint operator/( Qint&num);
	Qint operator=(const Qint& num);
	Qint operator&(const Qint& num);
	Qint operator|(const Qint& num);
	Qint operator^(const Qint& num);
	Qint operator>>(const int & num);
	Qint operator<<(const int & num);
	Qint ror();
	Qint rol();
	Qint operator~();
	bool Qint::compare2binary (const Qint&num);
	bool operator==(const Qint& num);//compare 2 numbers equal
	//Qint print functions
	//Print in decimal
	int256_t PrintDec();
	//Print in binary
	string PrintBin();
	//Print in hex
	string PrintHex();
};

//add 2 bitset size 128
bitset<128> sum(bitset<128> temp1, bitset<128> temp2,Qint & num);
bitset<64> sum1(bitset<64> temp1, bitset<64> temp2);