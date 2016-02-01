#pragma once

#include "types.h"
#include "TrieNode.h"

#include <deque>
#include <ostream>
#include <string>
#include <vector>

class Trie
{
	private:
		TrieNode*	root;
    std::string name;
		TrieNode* reach(std::string const& str) const;
		void		search_recursively(std::string, TrieNode*,
						deque<std::string>*, unsigned int) const;
		
    void anagram_recursively(
			std::vector<string> const& used,
		 	LetterCounts const& unused,
			TrieNode* const root,
			TrieNode* n,
			bool consume_all, 
			size_t* min_wordlet, 
			size_t* max_wordlet, 
			deque<vector<string>>& results
  	) const;
	
		void crossword_recursively(
		 std::vector<string> const& used,
		 std::string str,
		 TrieNode* n,
		 deque<vector<string>>& results
		) const;

	public:
		Trie(std::string const& name);
		~Trie();
		
		void 			insert(std::string);
		bool 			has(std::string);
		void 			remove(std::string);
		deque<std::string>	search(std::string) const;
		deque<std::string>	search(std::string, unsigned int) const;
    
    deque<std::vector<std::string>> anagrams(std::string const& str, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const;

    deque<std::vector<std::string>> box(std::vector<std::string> const& box, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const;
    deque<std::vector<std::string>> crossword(std::string const& str) const;
    std::string get_name() const;

    static void read_static(unsigned char const data[], Trie& t);
};

std::ostream& operator<<(std::ostream& os, Trie const& t);