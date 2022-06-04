#pragma once
#include <optional>

struct QueueFamilyIndices
{
public:
	std::optional<uint32_t> GraphicsFamily;
	std::optional<uint32_t> PresentationFamily;

public:
	bool IsAllFamiliesPresent();
};
