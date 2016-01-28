#pragma once
#include <map>
#include <deque>

using namespace std;

class TrieNode
{
	private:
		map<char, TrieNode*>	children;
    bool word;
		
	public:
		TrieNode();
		TrieNode(unsigned int);
		~TrieNode();
		
		TrieNode* get(char);
		TrieNode* put(char);
		deque<char> edges();
		bool has(char);
    void set_word(bool word);
    bool get_word();
};

typedef map<char, TrieNode*>::iterator	TrieNodeIterator;
