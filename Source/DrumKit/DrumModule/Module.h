/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_


#include "../../Sound/SoundProcessor/SoundProcessor.h"
#include "../../Sound/SoundBank/SoundBank.h"

#include "../Instruments/InstrumentParameters.h"
#include "../KitManager/KitParameters.h"
#include "../Instruments/Instrument.h"
#include "../Instruments/Drum.h"
#include "../Triggers/TriggerType.h"
#include "../Triggers/Trigger.h"
#include "../Triggers/DrumTrigger.h"

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>
#include <functional>
#include <utility>
#include <map>


namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::SoundProcessor> const& soundProc);
		virtual ~Module();

		void LoadKit(std::string fileLoc);

		void Start();
		void Stop();

		void GetDirectory(std::string& dir) const;


	private:

		void Run();

		void CreateTriggers();
		void CreateInstruments();

		KitParams kitParameters;

		IO::SensorType sensorType;

		std::string directory;

		std::vector<InstrumentPtr> instruments;
		std::vector<TriggerParameters> triggersParameters;

		std::thread playThread;
		std::atomic<bool> isPlay;
		std::shared_ptr<Sound::SoundProcessor> soundProc;

		std::map<int, TriggerPtr> triggers;


	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
