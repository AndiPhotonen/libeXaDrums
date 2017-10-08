/*
 * Config_api.h
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_CONFIG_API_H_
#define SOURCE_API_CONFIG_CONFIG_API_H_

#include "AlsaParams_api.h"
#include "../../IO/SensorsConfig.h"

#include <vector>
#include <string>

namespace DrumKit { class Module; }
namespace eXaDrumsApi{ class eXaDrums; struct TriggerParameters; }

namespace eXaDrumsApi
{

	class Config
	{

	public:

		explicit Config(eXaDrums& drums);
		virtual ~Config() = default;

		void RefreshSensorsConfig();
		void SaveSensorsConfig();
		void SaveTriggersConfig();
		void LoadTriggersConfig();
		void SaveCurrentAudioDeviceConfig();
		void SaveAudioDeviceConfig(const AlsaParamsApi& params);
		void ResetAudioDevice();

		// Mutators
		void SetSensorsSamplingRate(int sRate) { sensorsConfig.samplingRate = sRate; }
		void SetSensorsResolution(int res) { sensorsConfig.resolution = res; }
		void SetSensorsType(const std::string& type);
		void SetSensorsDataFolder(const std::string& folder);
		void SetAudioDeviceParameters(const AlsaParamsApi& params);
		void SetTriggersParameters(const std::vector<TriggerParameters>& params);

		// Accessors
		std::vector<std::string> GetSensorsTypes();
		std::vector<std::string> GetTriggersTypes();
		std::vector<std::string> GetTriggersResponses();
		std::vector<std::string> GetAudioDevicesNames();
		std::vector<TriggerParameters> GetTriggersParameters() const;

		std::string GetSensorsType();
		std::string GetSensorsDataFolder() const;
		std::string GetAudioDeviceName();
		AlsaParamsApi GetAudioDeviceParams() const;

		int GetSensorsSamplingRate() const { return sensorsConfig.samplingRate; }
		int GetSensorsResolution() const { return sensorsConfig.resolution; }

	private:

		void RestartModule();

		void SetSensorsType_(const char* type);
		void SetSensorsDataFolder_(const char* folder);
		void SetAudioDeviceParameters_(const char* name);
		void SetTriggersParameters_(const TriggerParameters* params, unsigned int size);
		void SetAudioDeviceParameters_(const AlsaParamsApi& params);

		const char* GetSensorsType_();
		const char* GetSensorsDataFolder_() const;
		const char* GetAudioDeviceName_();

		AlsaParamsApi GetAudioDeviceParams_() const;

		void GetSensorsTypes_(const char** types, unsigned int& size);
		void GetTriggersTypes_(const char** types, unsigned int& size);
		void GetTriggersResponses_(const char** responses, unsigned int& size);
		void GetAudioDevicesNames_(const char** devices, unsigned int& size);
		void GetTriggersParameters_(TriggerParameters* const triggers, unsigned int& size) const;

		eXaDrums& drumKit;
		DrumKit::Module& module;

		// Alsa config
		mutable AlsaParamsApi alsaParams;

		// Sensors config
		IO::SensorsConfig sensorsConfig;

		// Triggers config
		std::vector<TriggerParameters> triggersParameters;

		// Local copies of items
		std::string sensorType;
		std::string audioDeviceName;

		// Local copies of enums
		std::vector<std::string> sensorsTypes;
		std::vector<std::string> triggersTypes;
		std::vector<std::string> triggersResponses;
		std::vector<std::pair<std::string, std::string>> audioDevices;

	};

}

#include "Config_api.hpp"

#endif /* SOURCE_API_CONFIG_CONFIG_API_H_ */
