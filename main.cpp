#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>
#include "Trie.h"

#define DEFAULT_TEST_SIZE		100000
#define MIN_WORD_LEN			1
#define MAX_WORD_LEN			25
#define DEFAULT_SEARCH_PREFIX	"pre"
#define DEFAULT_SEARCH_SIZE		10

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	string chars = "abcdefghijklmnopqrstuvwxyz 0123456789";
	int test_size = argc < 2 ? DEFAULT_TEST_SIZE : atoi(argv[1]);
	string prefix = argc < 3 ? DEFAULT_SEARCH_PREFIX : argv[2];
	int max_results = argc < 4 ? DEFAULT_SEARCH_SIZE : atoi(argv[3]);
	double start, end, seconds, minutes;
	Trie trie;

	if (test_size < 0)
		test_size = DEFAULT_TEST_SIZE;
	if (max_results < 1)
		max_results = DEFAULT_SEARCH_SIZE;

	cout << "--Inserting data (" << test_size << " entries)..." << endl;

	start = time(NULL);

	for (int i = 0; i < test_size; i++)
	{
		unsigned int word_len = MIN_WORD_LEN + (rand() %
						(int)(MAX_WORD_LEN - MIN_WORD_LEN + 1));

		string entry = "";
		for (unsigned int j = 0; j < word_len; j++)
		{
			int rand_idx = rand() % (int)(chars.length());
			entry += chars.at(rand_idx);
		}

		trie.insert(entry);
	}

	end = time(NULL);

	seconds = end - start;
	minutes = seconds / 60;

	cout << "--Built structure with " << test_size << " entries in " << seconds << " seconds ";
	cout << "(" << minutes << " minutes)" << endl;

	cout << "--Searching for at most " << max_results << " entries starting with '" << prefix << "'... " << endl;

	start = time(NULL);
	
	deque<string> results = trie.search(prefix, max_results);
	
	end = time(NULL);
	
	seconds = end - start;
	minutes = seconds / 60;

	cout << "--Prefix search took " << seconds << " seconds (" << minutes << " minutes)" << endl;
	cout << "--Found " << results.size() << " results:" << endl;

	for (unsigned int i = 0; i < results.size(); i++)
		cout << results.at(i) << endl;

	return 0;
}