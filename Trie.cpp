#include "Trie.h"

#include <cctype>
#include <cstdint>
#include <sstream>

Trie::Trie(std::string const& name) :
  root(new TrieNode),
  name(name)
{
}

Trie::~Trie()
{
	delete this->root;
}

void Trie::insert(std::string str)
{
	TrieNode* n = this->root;
	
	for (unsigned int i = 0; i < str.length(); i ++)
		n = n->put(str.at(i));
	
	n->increment();
}

bool Trie::has(std::string str)
{
	TrieNode* n = this->reach(str);
	return n != 0 && n != this->root && n->get_count() > 0;
}

void Trie::remove(std::string str)
{
	TrieNode* n = this->reach(str);
	// TODO Cleanup! See if this node is still needed, or any of its parents, etc...
	if (n)
		n->decrement();
}

std::deque<std::string> Trie::search(std::string s) const
{
	return this->search(s, 0);
}

std::deque<std::string> Trie::search(std::string s, unsigned int cap) const
{
	std::deque<std::string> results;
	
	TrieNode* n = this->reach(s);
	
	if (n == 0)
		return results;
	
	this->search_recursively(s, n, &results, cap);
	
	return results;
}

void Trie::search_recursively(std::string s, TrieNode* n,
		std::deque<std::string>* results, unsigned int cap) const
{	
	if (n->get_word())
		results->push_back(s);
	
	if (cap && results->size() >= cap)
		return;
	
	std::deque<char> edges = n->edges();
	
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		char next = edges.at(i);
		this->search_recursively(s + next, n->get(next), results, cap);
	}
}

TrieNode* Trie::reach(std::string const& str) const
{
	TrieNode* n = this->root;
	
	for (unsigned int i = 0; i < str.length(); i++)
	{
		char c = str.at(i);
		
		if (!n->has(c))
			return 0;
		
		n = n->get(c);
	}
	
	return n;
}

std::string Trie::get_name() const
{
  return name;
}

void add_node(unsigned char const** pdata, TrieNode* root)
{
  uint8_t children = **pdata; (*pdata)++;
  for (uint8_t i = 0; i < children; ++i) {
    auto c = **pdata;
    auto child = root->put(std::tolower(c)); (*pdata)++;
    child->set_word(std::isupper(c) != 0);
    root->increment();
    add_node(pdata, child);
  }
}

void Trie::read_static(unsigned char const data[], Trie& t)
{
  uint8_t len = *data++;
  std::string name = "";
  for (uint8_t i = 0; i < len; ++i) {
    name += *data++;
  }

  t.name = name;
  int words = *reinterpret_cast<int const*>(data); data += sizeof(int);
  
  add_node(&data, t.root);
}

std::ostream& operator<<(std::ostream& os, Trie const& t)
{
  return os;
}

std::deque<std::vector<std::string>> Trie::anagrams(std::string const& str, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  std::deque<std::vector<std::string>> results;
  return results;
}

std::deque<std::vector<std::string>> Trie::box(std::vector<std::string> const& box, bool consume_all, size_t* min_wordlet, size_t* max_wordlet) const
{
  std::deque<std::vector<std::string>> results;
  return results;
}