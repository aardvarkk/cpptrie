#pragma once
#include <map>
#include <deque>

using namespace std;

class TrieNode
{
	private:
		map<char, TrieNode*>	children;
		unsigned int			count;
    bool word;
		
	public:
		TrieNode();
		TrieNode(unsigned int);
		~TrieNode();
		
		TrieNode*		get(char);
		TrieNode*		put(char);
		deque<char>		edges();
		bool			has(char);
		unsigned int	increment();
		unsigned int	decrement();
		unsigned int	get_count();
    void set_word(bool word);
    bool get_word();
};

typedef map<char, TrieNode*>::iterator	TrieNodeIterator;
