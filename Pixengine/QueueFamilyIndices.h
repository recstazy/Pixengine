#pragma once
#include <optional>
#include <set>

struct QueueFamilyIndices
{
public:
	std::optional<uint32_t> GraphicsFamily;
	std::optional<uint32_t> PresentationFamily;

public:
	bool IsAllFamiliesPresent() const;
	void IndicesToSet(std::set<uint32_t>& set) const;
};
