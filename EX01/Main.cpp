#include<iostream>
#include<vector>
#include"Qint.h"
#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	stringstream ss;
	string readIn;
	ifstream in;
	ofstream out;
	out.open("output.txt");
	for (int i = 1;i <= 20;i++)
	{
		string Fname = to_string(i) + ".txt";
		in.open(Fname);

		while (!in.eof())
		{
			getline(in, readIn);
			ss << readIn;
			int Size = readIn.size(), countBlank = 0;
			for (int i = 0;i < Size;i++)
			{
				if (readIn[i] == ' ')
					countBlank++;
			}
			if (countBlank == 2)
			{
				int type;
				string num, sign1;
				ss >> type >> sign1 >> num;
				Qint val(num, type);
				if (sign1 == "~")
				{
					val = ~val;
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type == 16)
						out << val.PrintHex() << endl;
				}
				else if (sign1 == "ror")
				{
					val = val.ror();
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type == 16)
						out << val.PrintHex() << endl;
				}
				else if (sign1 == "rol")
				{
					val = val.rol();
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type == 16)
						out << val.PrintHex() << endl;
				}
				else
				{
					int sign2 = stoi(sign1);
					if (sign2 == 2)
						out << val.PrintBin() << endl;
					else if (sign2 == 10)
						out << val.PrintDec() << endl;
					else if (sign2 == 16)
						out << val.PrintHex() << endl;
				}
			}
			else if (countBlank == 3)
			{
				int type, shift;
				string sign1, num, num1;
				ss >> type >> num >> sign1 >> num1;
				if (sign1 == "<<")
				{
					shift = stoi(num1);
					Qint val(num, type);
					val = val << shift;
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type == 16)
						out << val.PrintHex() << endl;
				}
				else if (sign1 == ">>")
				{
					shift = stoi(num1);
					Qint val(num, type);
					val = val >> shift;
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type == 16)
						out << val.PrintHex() << endl;
				}
				else if (sign1 == "~")
				{
					Qint val(num1, type);
					val = ~val;
					if (num == "2")
						out << val.PrintBin() << endl;
					else if (num == "10")
						out << val.PrintDec() << endl;
					else if (num == "16")
						out << val.PrintHex() << endl;
				}
				else
				{
					string temp = '-' + num, temp2 = '-' + num1;
					bool error = false, opposite = false;
					Qint val(num, type);
					Qint val1(num1, type);
					Qint result;
					if (sign1 == "+")
					{
						result = val + val1;
						if (temp2 == num || temp == num1)
						{
							result = 0;
						}
					}
					else if (sign1 == "-")
						result = val - val1;
					else if (sign1 == "*")
					{
						result = val*val1;
						if (num == "-1")
						{
							result = (Qint)0 - val1;
						}
						else if (num1 == "-1")
						{
							result = (Qint)0 - val;
						}
					}
					else if (sign1 == "/")
					{
						if (val1 == 0)
						{
							error = true;
						}
						else
						{
							result = val / val1;
						}
					}
					else if (sign1 == "&")
						result = val & val1;
					else if (sign1 == "|")
						result = val | val1;
					else if (sign1 == "^")
						result = val ^ val1;
					if (result.isOverFlow())
					{
						out << "OVERFLOW ";
					}
					if (error == true)
					{
						out << "Error (divide 0)" << endl;
					}
					else if (result == 0)
					{
						out << 0 << endl;
					}
					else if (type == 2)
						out << result.PrintBin() << endl;
					else if (type == 10)
					{
						out << result.PrintDec() << endl;
						cout << result.PrintDec() << endl;
						cout << result.PrintBin() << endl;
					}
					else if (type = 16)
						out << result.PrintHex() << endl;
				}

			}
			else if (countBlank == 4)
			{
				int type, shift, type1;
				string sign1, num, num1;
				ss >> type>>type1 >> num >> sign1 >> num1;
				if (sign1 == "<<")
				{
					shift = stoi(num1);
					Qint val(num, type);
					val = val << shift;
					if (type == 2)
						out << val.PrintBin() << endl;
					else if (type == 10)
						out << val.PrintDec() << endl;
					else if (type = 16)
						out << val.PrintHex() << endl;
				}
				else if (sign1 == ">>")
				{
					shift = stoi(num1);
					Qint val(num, type);
					val = val >> shift;
					if (type1 == 2)
						out << val.PrintBin() << endl;
					else if (type1 == 10)
						out << val.PrintDec() << endl;
					else if (type1 = 16)
						out << val.PrintHex() << endl;
				}
				else
				{
					string temp = '-' + num, temp2 = '-' + num1;
					bool error = false, opposite = false;
					Qint val(num, type);
					Qint val1(num1, type);
					Qint result;
					if (sign1 == "+")
					{
						result = val + val1;
						if (temp2 == num || temp == num1)
						{
							result = 0;
						}
					}
					else if (sign1 == "-")
						result = val - val1;
					else if (sign1 == "*")
					{
						result = val*val1;
						if (num == "-1")
						{
							result = (Qint)0 - val1;
						}
						else if (num1 == "-1")
						{
							result = (Qint)0 - val;
						}
					}
					else if (sign1 == "/")
					{
						if (val1 == 0)
						{
							error = true;
						}
						else
						{
							result = val / val1;
						}
					}
					else if (sign1 == "&")
						result = val & val1;
					else if (sign1 == "|")
						result = val | val1;
					else if (sign1 == "^")
						result = val ^ val1;
					if (result.isOverFlow())
					{
						out << "OVERFLOW ";
					}
					if (error == true)
					{
						out << "Error (divide 0)" << endl;
					}
					else if (result == 0)
					{
						out << 0 << endl;
					}
					else if (type1 == 2)
						out << result.PrintBin() << endl;
					else if (type1 == 10)
					{
						out << result.PrintDec() << endl;
						cout << result.PrintDec() << endl;
						cout << result.PrintBin() << endl;
					}
					else if (type1 = 16)
						out << result.PrintHex() << endl;
				}
			}
			ss.clear();
		}
		in.close();
	}
	out.close();
	system("pause");
	return 0;
}