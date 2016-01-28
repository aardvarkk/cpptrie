#include "TrieNode.h"

TrieNode::TrieNode()
{
  this->word = false;
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
		return nullptr;
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
	auto thing = children.find(c);
	return children.find(c) != children.end();
}

void TrieNode::set_word(bool word)
{
  this->word = word;
}

bool TrieNode::get_word()
{
  return word;
}
