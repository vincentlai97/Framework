#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <string>

class Node
{
public:
	Node();
	~Node();

	virtual void AddChild(std::string key, Node *child);
	virtual void RemoveChild(std::string key);

	virtual std::map<std::string, Node*> GetChildNodes();
	virtual Node* GetChildNode(std::string key);

	virtual void AddParent(Node* parent);
	virtual Node* GetParentNode() const;

protected:
	std::map<std::string, Node*> m_childNodes;
	Node *parent;

};

#endif