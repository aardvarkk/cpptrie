#include "Trie.h"

Trie::Trie()
{
	this->root = new TrieNode();
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
	
	n->increment();
}

bool Trie::has(string str)
{
	TrieNode* n = this->reach(str);
	return n != 0 && n != this->root && n->get_count() > 0;
}

void Trie::remove(string str)
{
	TrieNode* n = this->reach(str);
	// TODO Cleanup! See if this node is still needed, or any of its parents, etc...
	if (n)
		n->decrement();
}

deque<string> Trie::search(string s)
{
	return this->search(s, 0);
}

deque<string> Trie::search(string s, unsigned int cap)
{
	deque<string> results;
	
	TrieNode* n = this->reach(s);
	
	if (n == 0)
		return results;
	
	this->search_recursively(s, n, &results, cap);
	
	return results;
}

void Trie::search_recursively(string s, TrieNode* n,
		deque<string>* results, unsigned int cap)
{	
	if (n->get_count() > 0)
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

TrieNode* Trie::reach(string str)
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
