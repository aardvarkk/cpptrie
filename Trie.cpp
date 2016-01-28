#include "Trie.h"

#include <cctype>
#include <cstdint>
#include <sstream>

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
	string const& unused,
	TrieNode* n, 
	bool consume_all, 
	size_t* min_wordlet, 
	size_t* max_wordlet, 
	deque<vector<string>>& results
) const {

	if (n->get_word()) {
		results.push_back(used);
	}

	// Go through all unused string characters
	for (char c : unused) {

		auto new_n = n->get(c);

		if (new_n) {

			// Our new_used has an extra character being worked on
			auto new_used = used;
			new_used.back() += c;

			// Our new unused no longer has this letter
			auto new_unused = unused;
			new_unused.erase(find(new_unused.begin(), new_unused.end(), c));

			// Go one level deeper!
			anagram_recursively(
				new_used,
				new_unused,
				new_n,
				consume_all,
				min_wordlet,
				max_wordlet,
				results
			);
		}

	}
}

deque<vector<string>> Trie::anagrams(string const& str, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  deque<vector<string>> results;

	anagram_recursively({ "" }, str, root, consume_all, min_wordlet, max_wordlet, results);

  return results;
}

deque<vector<string>> Trie::box(vector<string> const& box, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  deque<vector<string>> results;
  return results;
}

deque<vector<string>> Trie::crossword(string const& str) const {
  deque<vector<string>> results;
  return results;	
}
