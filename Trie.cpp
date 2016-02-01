#include <cctype>
#include <cstdint>
#include <sstream>

#include "string_utils.h"
#include "Trie.h"

// Anagrams: Order doesn't matter, just letter counts
// - Word boundaries are branches -> have to check longer words as well as start new words
// Crossword: Order matters, always consume all input

Trie::Trie(string const& name) :
  root(new TrieNode),
  name(name)
{
}

Trie::~Trie()
{
	delete this->root;
}

void Trie::insert(string str)
{
	TrieNode* n = this->root;
	
	for (unsigned int i = 0; i < str.length(); i ++)
		n = n->put(str.at(i));
	
	n->set_word(true);
}

bool Trie::has(string str)
{
	TrieNode* n = this->reach(str);
	return n && n != this->root;
}

void Trie::remove(string str)
{
	TrieNode* n = this->reach(str);
}

deque<string> Trie::search(string s) const
{
	return this->search(s, 0);
}

deque<string> Trie::search(string s, unsigned int cap) const
{
	deque<string> results;
	
	TrieNode* n = this->reach(s);

	if (n) {
		this->search_recursively(s, n, &results, cap);
	}
	
	return results;
}

void Trie::search_recursively(string s, TrieNode* n,
		deque<string>* results, unsigned int cap) const
{	
	if (n->get_word())
		results->push_back(s);
	
	if (cap && results->size() >= cap)
		return;
	
	deque<char> edges = n->edges();
	
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		char next = edges.at(i);
		this->search_recursively(s + next, n->get(next), results, cap);
	}
}

TrieNode* Trie::reach(string const& str) const
{
	TrieNode* n = this->root;
	
	for (unsigned int i = 0; i < str.length(); i++)
	{
		char c = str.at(i);
		
		if (!n->has(c))
			return nullptr;
		
		n = n->get(c);
	}
	
	return n;
}

string Trie::get_name() const
{
  return name;
}

void add_node(unsigned char const** pdata, TrieNode* root)
{
  uint8_t children = **pdata; (*pdata)++;
  for (uint8_t i = 0; i < children; ++i) {
    auto c = **pdata;
    auto child = root->put(tolower(c)); (*pdata)++;
    child->set_word(isupper(c) != 0);
    add_node(pdata, child);
  }
}

void Trie::read_static(unsigned char const data[], Trie& t)
{
  uint8_t len = *data++;
  string name = "";
  for (uint8_t i = 0; i < len; ++i) {
    name += *data++;
  }

  t.name = name;
  int words = *reinterpret_cast<int const*>(data); data += sizeof(int);
  
  add_node(&data, t.root);
}

ostream& operator<<(ostream& os, Trie const& t)
{
  return os;
}

void Trie::anagram_recursively(
	vector<string> const& used,
	LetterCounts const& unused,
	TrieNode* const root,
	TrieNode* n,
	bool consume_all,
	size_t* min_wordlet, 
	size_t* max_wordlet, 
	deque<vector<string>>& results
) const {

	// BIG speed saver that also helps stop us from getting duplicate results
	// We should never be currently working on a word lexically < our last found word!
	if (used.size() > 1) {
		string const& cur = * used.rbegin();
		string const& prv = *(used.rbegin()+1);
		if (!StringUtils::in_search_order(prv, cur)) {
			return;
		}
	}
	
	// We're at a word boundary... have to branch
	// Want to check longer words using this as stem, and also just grab this word and use remaining
	if (n->get_word()) {
		if (!consume_all || (consume_all && unused.empty())) {
			results.push_back(used);
		}
		if (!unused.empty()) {
			auto new_used = used;
			new_used.push_back("");
			anagram_recursively(new_used, unused, root, root, consume_all, min_wordlet, max_wordlet, results);
		}
	}

	// Go through all unused string characters
	for (auto& lc : unused) {
		if (!n->has(lc.first)) continue;
			
		// Our new_used has an extra character being worked on
		auto new_used = used;
		new_used.back() += lc.first;
		
		// Our new unused no longer has this letter
		auto new_unused = unused;
		new_unused[lc.first]--;
		if (new_unused[lc.first] <= 0) new_unused.erase(lc.first);
		
		// Go one level deeper!
		anagram_recursively(
			new_used,
			new_unused,
			root,
			n->get(lc.first),
			consume_all,
			min_wordlet,
			max_wordlet,
			results
			);
	}
}

void get_letter_counts(string const& str, LetterCounts& counts) {
	counts.clear();
	for (char c : str) {
		counts[c]++;
	}
}

deque<vector<string>> Trie::anagrams(string const& str, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  deque<vector<string>> results;
	
	LetterCounts counts;
	get_letter_counts(str, counts);

	anagram_recursively({ "" }, counts, root, root, consume_all, min_wordlet, max_wordlet, results);

  return results;
}

deque<vector<string>> Trie::box(vector<string> const& box, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  deque<vector<string>> results;
  return results;
}

void Trie::crossword_recursively(
	std::vector<string> const& used,
	std::string str,
	TrieNode* n,
	deque<vector<string>>& results
	) const
{
	// More letters left to find
	if (!str.empty()) {
		string newstr;
		if (str.length() > 1) {
			newstr = str.substr(1, str.length()-1);
		}
		
		auto ch = str.front();
		
		// if wildcard, go through all edges
		if (ch == '?') {
			for (auto c : n->edges()) {
				auto new_used = used;
				new_used.back() += c;
				crossword_recursively(new_used, newstr, n->get(c), results);
			}
		}
		// does this edge exist?
		else if (n->has(ch)) {
			auto new_used = used;
			new_used.back() += ch;
			crossword_recursively(new_used, newstr, n->get(ch), results);
		}
		// can't exhaust the letters, so we fail
		else {
			return;
		}
	}
	// We're all done!
	else {
		if (n->get_word()) {
			results.push_back(used);
		}
	}
}

deque<vector<string>> Trie::crossword(string const& str) const {
  deque<vector<string>> results;
	
	crossword_recursively({ "" }, str, root, results);
	
  return results;	
}
