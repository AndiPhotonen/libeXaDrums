/*
 * TriggerManager.cpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#include "TriggerManager.h"


#include "../../Util/Enums.h"

#include "Curves/CurveType.h"
#include "TriggerLocation.h"

#include <tinyxml2.h>

#include <algorithm>


using namespace tinyxml2;
using namespace Util;

namespace DrumKit
{

	std::vector<int> TriggerManager::LoadTriggersIds(const std::string& moduleDir)
	{

		// Set default sensors parameters
		IO::SensorsConfig sensorsConfig;
		sensorsConfig.resolution = 12;
		sensorsConfig.samplingRate = 1000000;
		sensorsConfig.sensorType = IO::SensorType::Hdd;

		// Load triggers config with default sensor parameters
		std::vector<TriggerParameters> trigsParams;
		LoadTriggersConfig(moduleDir, sensorsConfig, trigsParams);

		std::vector<int> triggersIds(trigsParams.size());
		std::transform(trigsParams.cbegin(), trigsParams.cend(), triggersIds.begin(), [&](const TriggerParameters& p) { return p.sensorId; });


		return triggersIds;
	}

	void TriggerManager::LoadTriggersConfig(const std::string& moduleDir, const IO::SensorsConfig& sensorsConfig, std::vector<TriggerParameters>& trigsParams)
	{

		trigsParams.clear();

		std::string file(moduleDir + "triggersConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
		{
			throw -1;
		}

		XMLElement* root = doc.RootElement();

		// Look for first trigger
		XMLElement* firstTrigger = root->FirstChildElement("Trigger");

		// Read all triggers
		for(XMLElement* trigger = firstTrigger; trigger != nullptr; trigger = trigger->NextSiblingElement())
		{
			TriggerParameters trigParams;

			// Get trigger id
			trigParams.sensorId = std::atoi(trigger->Attribute("sensorId"));

			// Get trigger type
			trigParams.type = Enums<TriggerType>::ToElement(trigger->Attribute("sensorType"));

			// Read xml elements
			XMLElement* threshold = trigger->FirstChildElement("Threshold");
			XMLElement* scanTime = trigger->FirstChildElement("ScanTime");
			XMLElement* maskTime = trigger->FirstChildElement("MaskTime");
			XMLElement* response = trigger->FirstChildElement("Response");

			trigParams.threshold = (short) std::atoi(threshold->GetText());
			trigParams.scanTime = (unsigned int) std::atoi(scanTime->GetText());
			trigParams.maskTime = std::atoi(maskTime->GetText());
			trigParams.response = Enums<CurveType>::ToElement(response->GetText());


			trigParams.sensorType = sensorsConfig.sensorType;

			trigsParams.push_back(trigParams);
		}


		return;
	}


	void TriggerManager::LoadSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig)
	{

		std::string file(moduleDir + "sensorsConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
		{
			throw -1;
		}

		XMLElement* root = doc.RootElement();

		XMLElement* samplingRate = root->FirstChildElement("SamplingRate");
		XMLElement* resolution = root->FirstChildElement("Resolution");
		XMLElement* type = root->FirstChildElement("Type");

		sensorConfig.samplingRate = std::stoi(samplingRate->GetText());
		sensorConfig.resolution = std::stoi(resolution->GetText());
		sensorConfig.sensorType = Enums<IO::SensorType>::ToElement(type->GetText());

		return;
	}

	void TriggerManager::SaveSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig)
	{

		std::string file(moduleDir + "sensorsConfig.xml");

		XMLDocument doc;

		// Add root element
		XMLElement* root = doc.NewElement("SensorsConfig");
		doc.InsertFirstChild(root);

		// Create Elements
		XMLElement* samplingRate = doc.NewElement("SamplingRate");
		XMLElement* resolution = doc.NewElement("Resolution");
		XMLElement* type = doc.NewElement("Type");

		samplingRate->SetText(sensorConfig.samplingRate);
		resolution->SetText(sensorConfig.resolution);

		std::string typeStr = Enums<IO::SensorType>::ToString(sensorConfig.sensorType);
		type->SetText(typeStr.c_str());

		// Add elements to document
		root->InsertEndChild(samplingRate);
		root->InsertEndChild(resolution);
		root->InsertEndChild(type);

		doc.SaveFile(file.c_str());

		return;
	}


} /* namespace DrumKit */
