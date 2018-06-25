#pragma once

#include <string>
#include <sstream>

#include <osgEarth/ModelLayer>

class ModelLayerReader
{
public:
	ModelLayerReader();
	~ModelLayerReader();

	osgEarth::ModelLayer* CreateModelLayer(const std::string& fullFileName);
};

