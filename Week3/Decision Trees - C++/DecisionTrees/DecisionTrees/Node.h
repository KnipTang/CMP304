#pragma once

#include <vector>
#include <functional>

struct TreeData
{
	int resourceCount = 45;
	bool resourcesNearby = false;
};

class Node
{

public:
	// Constructor - saves the custom function passed into the class when created
	Node(std::function<int(TreeData)> new_custom_func) : custom_func(new_custom_func) {}

	// Basic node just calls its custom function when run() is called
	virtual void run(TreeData v) {
		custom_func(v);
	}

	// Adds a child node to a vector
	void addChildNode(Node* new_child) { child_nodes.push_back(new_child); }
protected:
	std::vector<Node*> child_nodes;		// Vector of child nodes (branches or leaves)
	std::function<int(TreeData)> custom_func;	// Custom function that tells the node what to do
};

class DecisionNode : public Node
{
public:
	// Constructor - saves the custom function passed into the class when created
	DecisionNode(std::function<int(TreeData)> new_custom_func) : Node(new_custom_func) {}

	// Override the run() function
	// custom_func() needs to be designed to return an index to which child branch to run
	// Runs that child branch if it can access it
	void run(TreeData v) override {
		int index = custom_func(v);
		if (index >= 0 && index < child_nodes.size())
		{
			Node* child = child_nodes[index];
			child->run(v);
		}
	}
};