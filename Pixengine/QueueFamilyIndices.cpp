#include "QueueFamilyIndices.h"

bool QueueFamilyIndices::IsAllFamiliesPresent()
{
    return GraphicsFamily.has_value();
}
