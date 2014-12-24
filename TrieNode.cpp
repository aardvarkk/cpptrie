#include "TrieNode.h"

TrieNode::TrieNode()
{
	this->count = 0;
  this->word = false;
}

TrieNode::TrieNode(unsigned int num)
{
	this->count = num;
}

TrieNode::~TrieNode()
{
	for (TrieNodeIterator it = this->children.begin();
			it != this->children.end(); ++it)
		delete it->second;
}

TrieNode* TrieNode::get(char c)
{
	if (this->has(c))
		return this->children[c];
	else
		return 0;
}

TrieNode* TrieNode::put(char c)
{
	if (!this->has(c))
		this->children[c] = new TrieNode();
	
	return this->children[c];
}

deque<char> TrieNode::edges()
{
	deque<char> keys;
	
	for (TrieNodeIterator it = this->children.begin();
			it != this->children.end(); ++it)
		keys.push_back(it->first);
	
	return keys;
}

bool TrieNode::has(char c)
{
	return this->children.count(c) > 0;
}

unsigned int TrieNode::increment()
{
	return ++this->count;
}

unsigned int TrieNode::decrement()
{
	return this->count == 0 ? 0 : --this->count;
}

unsigned int TrieNode::get_count()
{
	return this->count;
}

void TrieNode::set_word(bool word)
{
  this->word = word;
}

bool TrieNode::get_word()
{
  return word;
}
