#include "Node.h"
#include <iostream>
#include <thread>
using namespace std::chrono_literals;



// TODO - Create functions / lambdas for each unique node in the tree 
int decision_node_resource_count(TreeData td)
{
	if (td.resourceCount < 40)
		return 0;
	else
		return 1;
}

int decision_node_resource_nearby(TreeData td)
{
	if (td.resourcesNearby)
		return 1;
	else
		return 0;
}

int root_node_random(TreeData td) {
	int random = rand() % 100;
	if (random < 40) {
		return 0;
	}
	else {
		return 1;
	}
}

int leaf_node_zero(TreeData td)
{
	std::cout << "Leaf node 0 has been called." << std::endl;
	return 0;
}

int leaf_node_one(TreeData td)
{
	std::cout << "Leaf node 1 has been called." << std::endl;
	return 0;
}

int leaf_node_two(TreeData td)
{
	std::cout << "Leaf node 2 has been called." << std::endl;
	return 0;
}

int leaf_node_three(TreeData td)
{
	std::cout << "Leaf node 3 has been called." << std::endl;
	return 0;
}


int main()
{
	// TreeData stores the data that the tree will use when making its decisions
	TreeData treeData;

	srand(time(NULL));


	// TODO - Create instances of deciusion nodes and leaf nodes as appropriate
	DecisionNode root_node(decision_node_resource_count);

	DecisionNode build_node(root_node_random);
	DecisionNode resource_node(decision_node_resource_nearby);

	Node leaf0(leaf_node_zero);
	Node leaf1(leaf_node_one);
	Node leaf2(leaf_node_two);
	Node leaf3(leaf_node_three);


	// TODO - Add the leaf nodes as children to the connected decision nodes
	root_node.addChildNode(&build_node);
	root_node.addChildNode(&resource_node);

	build_node.addChildNode(&leaf0);
	build_node.addChildNode(&leaf1);
	resource_node.addChildNode(&leaf2);
	resource_node.addChildNode(&leaf3);


	// TODO -  Run the root node of the tree
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		root_node.run(treeData);
	}
	
}