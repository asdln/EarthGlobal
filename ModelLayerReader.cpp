#include "ModelLayerReader.h"

#include <osgDB/Registry>
#include <osgDB/Options>

#include <osgEarth/Registry>

#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarth/Registry>
#include <osgEarth/XmlUtils>

#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>
#include <osgDB/Registry>
#include <string>
#include <sstream>
#include <osgEarthUtil/Common>


ModelLayerReader::ModelLayerReader()
{

}


ModelLayerReader::~ModelLayerReader()
{
}

osgEarth::ModelLayer* ModelLayerReader::CreateModelLayer(const std::string& fullFileName)
{
	osgEarth::ReadResult r = osgEarth::URI(fullFileName).readString(NULL);
	std::stringstream in(r.getString());

	osg::ref_ptr<osgDB::Options> myOptions = osgEarth::Registry::instance()->cloneOrCreateOptions(NULL);
	osgEarth::URIContext(fullFileName).apply(myOptions.get());

	osgEarth::URIContext uriContext(myOptions);
	osg::ref_ptr<osgEarth::XmlDocument> doc = osgEarth::XmlDocument::load(in, uriContext);
	if (!doc.valid())
		return NULL;

	osgEarth::Config docConf = doc->getConfig();
	// 	// support both "map" and "earth" tag names at the top level
	// 
	// 	osgEarth::Config conf;
	// 	if (docConf.hasChild("model"))
	// 		conf = docConf.child("model");
	// 	else
	// 	{
	// 		return;
	// 	}

	osgEarth::ConfigSet models = docConf.children("model");
	for (osgEarth::ConfigSet::const_iterator i = models.begin(); i != models.end(); i++)
	{
		const osgEarth::Config& layerDriverConf = *i;

		osgEarth::ModelLayerOptions layerOpt(layerDriverConf);
		layerOpt.name() = layerDriverConf.value("name");

		layerOpt.driver() = osgEarth::ModelSourceOptions(layerDriverConf);
		osgEarth::ModelLayer* pModelLayer = new osgEarth::ModelLayer(layerOpt);

		return pModelLayer;
	}

	return NULL;
}