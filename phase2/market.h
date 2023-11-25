#ifndef MARKET_H
#define MARKET_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
class market
{
public:
	market(int argc, char **argv);
	void start();

	bool check(string a, string b)
	{
		vector<string> A;
		vector<string> B;
		int count = 0;
		string t = "";
		for (char i : a)
		{
			if (i == ' ')
			{
				if (count % 2 == 0)
				{
					t.push_back(i);
					// cout << t << endl;
				}
				else
				{
					A.push_back(t);
					// cout << t << endl;
					t = "";
				}
				count++;
			}
			else
			{
				t.push_back(i);
			}

		}
		A.push_back(t);
		if (count == 0)
		{
			A.push_back(t);
		}
		count = 0;
		t = "";
		for (char i : b)
		{
			if (i == ' ')
			{
				if (count % 2 == 0)
				{
					t.push_back(i);
					// cout << t << endl;
				}
				else
				{
					B.push_back(t);
					// cout << t << endl;
					t = "";
				}
				count++;
			}
			else
			{
				t.push_back(i);
			}
		}
		B.push_back(t);
		if (count == 0)
		{
			B.push_back(t);
		}
		// for(string w :A){
		// 	cout << w << "---";
		// }
		// cout << endl;
		// for(string w :B){
		// 	cout << w << "---";
		// }
		// cout << endl;
		if (A.size() == B.size())
		{
			int i = 0;
			for (string s : A)
			{
				i = 0;
				for (string u : B)
				{
					if (u == s)break;
					i++;					
				}
				if (i == B.size()){
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	int compare(string s1, string s2)
	{
		for (int i = 0; i < s1.size(); i++)
		{
			if (int(s1[i]) > 96)
			{
				s1[i] = char(int(s1[i]) - 32);
			}
		}
		for (int i = 0; i < s2.size(); i++)
		{
			if (int(s2[i]) > 96)
			{
				s2[i] = char(int(s2[i]) - 32);
			}
		}
		for (int i = 0; i < min(s1.size(), s2.size()); i++)
		{
			if (int(s1[i]) < int(s2[i]))
				return -1;
			if (int(s1[i]) > int(s2[i]))
				return 1;
		}
		return (s1.size() - s2.size());
	}

private:
	fstream File;
};
#endif
