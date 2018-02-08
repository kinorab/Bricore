#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class RenderNode {
	std::vector<std::unique_ptr<RenderNode>> children;
};
