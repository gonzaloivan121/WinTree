#pragma once

#include "Walnut/Image.h"

#include <string>
#include <vector>

struct Node {
	std::shared_ptr<Walnut::Image> Icon;
	std::string Name;
	std::string Type;
	int Size;
	std::vector<Node> Children;
};