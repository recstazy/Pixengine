#pragma once
#include <vector>

class ValidationLayers
{
public:
	const std::vector<const char*> VALIDATION_LAYERS = 
	{
		"VK_LAYER_KHRONOS_validation"
	};

public:
	bool IsGlobalValidationEnabled();
	bool IsAllLayersSupported();
};

