#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <map> 
#include <set> 
#include <string>
#include<vector>
#include<algorithm>
#include<cctype>
using namespace std;
bool pred(const pair< string, int >& a, const pair< string, int >& b)
{
	return a.second < b.second;
}
void main()
{
	fstream fs;
	string story = "Story.txt", story_sorted = "Story_sorted.txt";
	char punct[7] = { ':','.',';', ',','?','\0','!' };
	set<char> punctuation(punct, punct + 7);
	fs.open(story, fstream::in | fstream::out | fstream::app);
	if (!fs) { cout << "File not found\n"; exit; }
	map<string, int> word_count;
	string str;
	while (fs >> str)
	{
		transform(str.begin(), str.end(), str.begin(), tolower);
		int n = str.size();
		if (punctuation.count(str[n - 1]))
			str.erase(n - 1, n);
		++word_count[str];
	}
	fs.close();
	fs.open(story_sorted, fstream::in | fstream::out);
	if (!fs) { cout << "File not found\n"; exit; }
	vector< pair< string, int > > vec(word_count.begin(), word_count.end());
	sort(vec.rbegin(), vec.rend(), pred);
	vector< pair< string, int > >::iterator it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		fs << setw(20) << left << it->first << setw(4) << right << it->second << endl;
		cout << left << setw(20) << it->first << setw(5) << it->second << endl;
	}
	fs.close();
}