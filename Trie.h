#pragma once
#include <string>
#include <deque>
#include "TrieNode.h"

using namespace std;

class Trie
{
	private:
		TrieNode*	root;
		TrieNode*	reach(string);
		void		search_recursively(string, TrieNode*,
						deque<string>*, unsigned int);
		
	public:
		Trie();
		~Trie();
		
		void 			insert(string);
		bool 			has(string);
		void 			remove(string);
		deque<string>	search(string);
		deque<string>	search(string, unsigned int);
};
