#include "QueueFamilyIndices.h"

bool QueueFamilyIndices::IsAllFamiliesPresent() const
{
    return GraphicsFamily.has_value() 
        && PresentationFamily.has_value();
}

void QueueFamilyIndices::IndicesToSet(std::set<uint32_t>& set) const
{
    set.insert(GraphicsFamily.value());
    set.insert(PresentationFamily.value());
}
