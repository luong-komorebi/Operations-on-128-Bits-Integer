#include"Qint.h"

Qint::Qint()
{
	arrayBits[0] = 0;
	arrayBits[1] = 0;
	overFlow = false;
}

Qint::Qint(string num, int type)
{
	overFlow = false;
	if (type == 2)
	{
		if (num.size() > 128)
			overFlow = true;
		int Size = num.size();
		if (Size <= 64)
		{
			arrayBits[0] = 0;
			bitset<64> store(num);
			arrayBits[1] = store.to_ullong();
		}
		else
		{
			int over = Size - 64;
			string first = num.substr(0, over),second=num.substr(0 + over, 64);
			bitset<64> store(first), store1(second);
			arrayBits[0] = store.to_ullong();
			arrayBits[1] = store1.to_ullong();
		}
	}
	else if (type == 10)
	{
		stringstream ss;
		int128_t num1;
		ss << num;
		ss >> num1;
		arrayBits[0] = (long long)(num1 >> 64);
		arrayBits[1] = (long long)num1;
	}
	else if (type == 16)
	{
		
		string BinString;
		int Size = num.size();
		//change hex to binary
		for (int i = 0;i < Size;i++)
		{
			int temp;
			if (num[i] == 'F')
				temp = 15;
			else if (num[i] == 'E')
				temp = 14;
			else if (num[i] == 'D')
				temp = 13;
			else if (num[i] == 'C')
				temp = 12;
			else if (num[i] == 'B')
				temp = 11;
			else if (num[i] == 'A')
				temp = 10;
			else
				temp = int(num[i]) - int('0');
			bitset<4> tempBin(temp);
			string tempString= tempBin.to_string();
			BinString += tempString;
		}
		int Size1 = BinString.size();
		if (Size1 > 64)
		{
			string second = BinString.substr(Size1 - 64, 64),
				first = BinString.substr(0, Size1 - 64);
			bitset<64> val1Bin(first), val2Bin(second);
			arrayBits[0] = val1Bin.to_ullong();
			arrayBits[1] = val2Bin.to_ullong();
		}
		else
		{
			arrayBits[0] = 0;
			bitset<64> val2Bin(BinString);
			arrayBits[1] = val2Bin.to_ullong();
		}
	}
}

Qint::Qint(long long val1,long long val2)
{
	overFlow = false;
	arrayBits[0] = val1;
	arrayBits[1] = val2;
}

Qint::Qint(long long val1, long long val2, bool over)
{
	arrayBits[0] = val1;
	arrayBits[1] = val2;
	overFlow = over;
}
//change intger to Qint
Qint::Qint(int n)
{
	overFlow = false;
	arrayBits[0] = 0;
	arrayBits[1] = n;
}


//check overflow
bool Qint::isOverFlow()
{
	return overFlow;
}

//set overFlow
void Qint::setOverFlow(bool value)
{
	overFlow = value;
}
//operator &
Qint Qint::operator&(const Qint& num)
{
	long long temp[2];
	temp[0] = arrayBits[0] & num.arrayBits[0]; //AND with the first 64 bits
	temp[1] = arrayBits[1] & num.arrayBits[1]; //AND with the last 64 bits
	Qint cur(temp[0],temp[1]);
	return cur;
}
//copy operator
Qint Qint::operator=(const Qint& num)
{
	arrayBits[0] = num.arrayBits[0]; // Assign first 64 bits;
	arrayBits[1] = num.arrayBits[1]; // Assign last 64 bits;
	overFlow = num.overFlow;//assign bool overflow
	return *this;
}
//operator |
Qint Qint::operator|(const Qint& num)
{
	long long val1 = arrayBits[0] | num.arrayBits[0];// OR with the first 64 bits
	long long val2 = arrayBits[1] | num.arrayBits[1];// OR with the last 64 bits
	Qint cur(val1, val2);
	return cur;
}
//operator ^
Qint Qint::operator^(const Qint& num)
{
	long long val1 = arrayBits[0] ^ num.arrayBits[0];//XOR with the first 64 bits;
	long long val2 = arrayBits[1] ^ num.arrayBits[1];//XOR with the last 64 bits;
	Qint cur(val1, val2);
	return cur;
}
//NOT operator
Qint Qint::operator~()
{
	long long val1 = ~arrayBits[0];
	long long val2 = ~arrayBits[1];
	Qint cur(val1, val2);
	return cur;
}
//operator +
Qint Qint::operator+(const Qint& num)
{
	bitset<64> store(arrayBits[0]), store1(arrayBits[1]), store2(num.arrayBits[0]), store3(num.arrayBits[1]), sum1, sum2;
	bitset<1> c;
	for (int i = 0; i < 64; i++) 
	{
		sum2[i] = ((store1[i] ^ store3[i]) ^ c[0]); // c is carry
		c = ((store1[i] & store3[i]) | (store1[i] & c[0])) | (store3[i] & c[0]);
	}
	for (int i = 0; i < 64; i++) 
	{
		sum1[i] = ((store[i] ^ store2[i]) ^ c[0]); // c is carry
		c = ((store[i] & store2[i]) | (store[i] & c[0])) | (store2[i] & c[0]);
		if (i == 63 && c == 1)
			overFlow = true;
	}
	long long val1 = sum1.to_ullong(), val2 = sum2.to_ullong();
	Qint cur(val1, val2,this->overFlow);
	if (num.overFlow == true || this->overFlow == true)
		cur.overFlow = true;
	return cur;
}

//operator -
Qint Qint::operator-(const Qint& num)
{
	long long val1 = ~num.arrayBits[0], val2 = ~num.arrayBits[1];
	Qint cur(val1, val2);
	cur = cur + 1;
	cur = (*this) + cur;
	return cur;
}

//Operator *
Qint Qint::operator*(const Qint&num)
{
	bitset<128> store1(arrayBits[1]), temp1(arrayBits[0]), store2(num.arrayBits[1]), temp2(num.arrayBits[0]);
	bitset<128> mul;
	temp1 = temp1 << 64;
	temp2 = temp2 << 64;
	store1 = sum(store1, temp1,*this);
	store2 = sum(store2, temp2,*this);
	for (int i = 0;i < 128;i++)
	{
		if (store2.test(i))
		{
			bitset<128> temp3 = store1 << i;
			mul = sum(mul, temp3, *this);
		}
	}
	string cur = mul.to_string(), cur1= cur.substr(0,64);
	cur.erase(cur.begin(), cur.begin() + 64);
	bitset<64> Curbit(cur), cur1bit(cur1);
	long long val1 = cur1bit.to_ullong(), val2 = Curbit.to_ullong();
	Qint ret(val1, val2, this->overFlow);
	return ret;
}
//operator /
bool Qint::compare2binary (const Qint&num) {
	long long val1 = ~num.arrayBits[0];
	long long val2 = ~num.arrayBits[1];
	Qint cur(val1, val2);
	cur = cur + 1;
	cur = (*this) + cur;
	bitset<64> store1(cur.arrayBits[0]);
	if (store1.test(63)) {
		return false;
	}
	else return true;
}
Qint Qint::operator/( Qint&num) {
	if (this->compare2binary(num) == false){
		long long dummy1 = 0;
		long long dummy2 = 0;
		Qint ret(dummy1, dummy2);
		return ret;
	}
	int256_t a = this->PrintDec();
	// cout << a << endl;
	int256_t b = num.PrintDec();
	// cout << b << endl;
	int256_t result = a / b;
	long long dummy1 = 0;
	long long dummy2 = 0;
	// cout << result;
	Qint ret(dummy1, dummy2);
	ret.arrayBits[0] = (long long)(result >> 64);
	ret.arrayBits[1] = (long long)result;
	return ret;

}

//compare 2 numbers equal
bool Qint::operator==(const Qint& num)
{
	if (arrayBits[0] == num.arrayBits[0] && arrayBits[1] == num.arrayBits[1])
		return true;
	return false;
}
//Operator shift left
Qint Qint::operator<<(const int& num)
{
	bitset<64> cur(arrayBits[0]), cur1(arrayBits[1]);
	string temp = cur1.to_string();
	if (num >= 64)
	{
		cur1 = cur1 << num;
		int left = num - 64;
		if (left >= 64)
			cur = cur << left;
		else
		{
			temp = temp.substr(left, 64 - left);
			bitset<64> cur2(temp);
			cur = cur2 << (64 - left);
		}
		arrayBits[0] = cur.to_ullong();
		arrayBits[1] = cur1.to_ullong();
		return *this;
	}
	cur1 = cur1 << num;
	temp = temp.substr(0, num);
	bitset<64> cur2(temp);
	cur = cur << num;
	cur = sum1(cur, cur2);
	arrayBits[0] = cur.to_ullong();
	arrayBits[1] = cur1.to_ullong();
	return *this;
}

//Operator shift right
Qint Qint::operator >> (const int& num)
{
	bitset<64> cur(arrayBits[0]), cur1(arrayBits[1]);
	string temp = cur.to_string();
	if (num >= 64)
	{
		cur = cur >> num;
		int left = num - 64;
		if (left >= 64)
			cur1 = cur1 >> left;
		else
		{
			temp = temp.substr(0,64-left);
			bitset<64> cur2(temp);
			cur1 = cur2;
		}
		arrayBits[0] = cur.to_ullong();
		arrayBits[1] = cur1.to_ullong();
		return *this;
	}
	cur = cur >> num;
	temp = temp.substr(64-num, num);
	bitset<64> cur2(temp);
	cur1 = cur1 >> num;
	cur2 = cur2 << (63 - num);
	cur1 = sum1(cur1, cur2);
	arrayBits[0] = cur.to_ullong();
	arrayBits[1] = cur1.to_ullong();
	return *this;
}

//Operator ror
Qint Qint::ror()
{
	bitset<64> cur(arrayBits[0]), cur1(arrayBits[1]);
	bitset<1> temp1 = cur[0], temp2 = cur1[0];
	cur = cur >> 1;
	cur1 = cur1 >> 1;
	cur1[63] = temp1[0];
	cur[63] = temp2[0];
	arrayBits[0] = cur.to_ullong();
	arrayBits[1] = cur1.to_ullong();
	return *this;
}

//operator rol
Qint Qint::rol()
{
	bitset<64> cur(arrayBits[0]), cur1(arrayBits[1]);
	bitset<1> temp1 = cur[63], temp2 = cur1[63];
	cur = cur << 1;
	cur1 = cur1 << 1;
	cur1[0] = temp1[0];
	cur[0] = temp2[0];
	arrayBits[0] = cur.to_ullong();
	arrayBits[1] = cur1.to_ullong();
	return *this;
}
//Add 2 bitset size 128
bitset<128> sum(bitset<128> temp1, bitset<128> temp2, Qint &num)
{
	bitset<1> c;
	bitset<128> sum2;
	for (int i = 0; i < 128; i++) 
	{
		sum2[i] = ((temp1[i] ^ temp2[i]) ^ c[0]); // c is carry
		c = ((temp1[i] & temp2[i]) | (temp1[i] & c[0])) | (temp2[i] & c[0]);
		if (i == 127 && c == 1)
			num.setOverFlow(true);
	}
	return sum2;
}
//Add 2 bitset size 64
bitset<64> sum1(bitset<64> temp1, bitset<64> temp2)
{
	bitset<1> c;
	bitset<64> sum2;
	for (int i = 0; i < 64; i++)
	{
		sum2[i] = ((temp1[i] ^ temp2[i]) ^ c[0]); // c is carry
		c = ((temp1[i] & temp2[i]) | (temp1[i] & c[0])) | (temp2[i] & c[0]);
	}
	return sum2;
}
//Print binary
string Qint::PrintBin()
{
	string ret;
	bitset<64> out1(arrayBits[0]), out2(arrayBits[1]);
	string temp = out1.to_string(), temp2 = out2.to_string();
	long long test = out1.to_ullong();
	if (temp[0] == 1)
	{
		ret += temp + temp2;
		return ret;
	}
	if (test != 0)
	{
		int pos = 0;
		for (int i = 0;i < 64;i++)
		{
			if (temp[i] == '1')
			{
				pos = i;
				temp.erase(temp.begin(), temp.begin() + pos );
				break;
			}
		}
		ret += temp + temp2;
		return ret;
	}
	for (int i = 0;i < 64;i++)
	{
		temp = out2.to_string();
		if (temp[i] == '1')
		{
			temp.erase(temp.begin(), temp.begin() + i );
			break;
		}
	}
	return temp;
}

//Print Hex:: Not yet
string Qint::PrintHex()
{
	string ret;
	bitset<64> store(arrayBits[0]), store1(arrayBits[1]);
	string temp = store.to_string(), temp1 = store1.to_string();
	for (int i = 0;i <= 60;i += 4)
	{
		string temp2 = temp.substr(i, 4);
		if (temp2 == "0000")
			ret += '0';
		else if (temp2 == "0001")
			ret += '1';
		else if (temp2 == "0010")
			ret += '2';
		else if (temp2 == "0011")
			ret += '3';
		else if (temp2 == "0100")
			ret += '4';
		else if (temp2 == "0101")
			ret += '5';
		else if (temp2 == "0110")
			ret += '6';
		else if (temp2 == "0111")
			ret += '7';
		else if (temp2 == "1000")
			ret += '8';
		else if (temp2 == "1001")
			ret += '9';
		else if (temp2 == "1010")
			ret += 'A';
		else if (temp2 == "1011")
			ret += 'B';
		else if (temp2 == "1100")
			ret += 'C';
		else if (temp2 == "1101")
			ret += 'D';
		else if (temp2 == "1110")
			ret += 'E';
		else if (temp2 == "1111")
			ret += 'F';
	}
	for (int i = 0;i <= 60;i += 4)
	{
		string temp2 = temp1.substr(i, 4);
		if (temp2 == "0000")
			ret += '0';
		else if (temp2 == "0001")
			ret += '1';
		else if (temp2 == "0010")
			ret += '2';
		else if (temp2 == "0011")
			ret += '3';
		else if (temp2 == "0100")
			ret += '4';
		else if (temp2 == "0101")
			ret += '5';
		else if (temp2 == "0110")
			ret += '6';
		else if (temp2 == "0111")
			ret += '7';
		else if (temp2 == "1000")
			ret += '8';
		else if (temp2 == "1001")
			ret += '9';
		else if (temp2 == "1010")
			ret += 'A';
		else if (temp2 == "1011")
			ret += 'B';
		else if (temp2 == "1100")
			ret += 'C';
		else if (temp2 == "1101")
			ret += 'D';
		else if (temp2 == "1110")
			ret += 'E';
		else if (temp2 == "1111")
			ret += 'F';
	}
	if (ret[0] != '0')
		return ret;
	int siz = ret.size();
	for (int i = 1;i < siz;i++)
	{
		if (ret[i] != '0')
		{
			ret.erase(ret.begin(), ret.begin() + i );
			break;
		}
	}
	return ret;
}

//Print to Decimal
int256_t Qint::PrintDec()
{
	//store the binary to string
	bitset<128> store(arrayBits[0]), store1(arrayBits[1]);
	store = store << 64;
	store = sum(store, store1, *this);
	string binNum = store.to_string();
	//Calculate from string of binary to decimal number using boost library
	int256_t v;
	int binLength = binNum.length();
	bool checkNeg = false;
	if (binLength == 128 && binNum[0] == '1') { // deal with negative value
		checkNeg = true;

		for (int i = binLength - 1; i >= 0; i--) { // minus 1

			if (binNum[i] == '0') binNum[i] = '1';

			else {
				binNum[i] = '0';
				break;
			}
		}
		for (int k = binLength - 1; k >= 0; k--) { // reverse the whole string from 0 to 1 and from 1 to 0

			if (binNum[k] == '0') binNum[k] = '1';
			else binNum[k] = '0';

		}
	}

	for (int j = binLength - 1; j >= 0; j--) { // normal bin to dec
		int128_t num4Char = binNum[j] - '0';
		int128_t fixCasting = (int128_t)pow(2.0, (binLength - 1 - j));
		num4Char = num4Char * fixCasting;
		v = v + num4Char;
		
	}
	if (checkNeg)
		v = v * (-1);

	return v;
}