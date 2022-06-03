#pragma once
#include <optional>

struct QueueFamilyIndices
{
public:
	std::optional<uint32_t> GraphicsFamily;

public:
	bool IsAllFamiliesPresent();
};
