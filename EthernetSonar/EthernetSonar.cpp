
//=============================================================================
// Built on exmaplecode from Deepvision.
//-----------------------------------------------------------------------------


#include "EthernetSonarAPI.h"
#include "DVSFileWriter.h"
#include "JSONFileWriter.h"
#include "DSSPParser.h"
#include <stdlib.h>

#define BUFFERSIZE 2048

int main(int argc, char* argv[]) {

	if (argc <= 3) {
		std::cout << "Input arg missing. \nCommand is: ./EthernetSonar [RANGE] [FILENAME] [PINGS]" << std::endl;
		return 0;
	}

	CEthernetSonarAPI Sonar("192.168.2.62", 0xE001);


	CDVSFileWriter DVSFile;
	JSONFileWriter JSONFile;
	CDSSPParser parser;

	int int_range = strtol(argv[1], NULL, 0);
	int int_pings = strtol(argv[3], NULL, 0);
	
	char filename_json[256];
	char filename_dvs[256];

	// Skipping the input filename, for simplication when run as a file sharing service. 
	/*
	strcat(filename_json, argv[2]);
	strcat(filename_dvs, argv[2]);
	*/

	strcat(filename_json, "output/output.json");
	strcat(filename_dvs, "output/output.dvs");
	
	float range = (float)int_range;							
	int nSamples = 500;										

	int nPeriods = 32;										
	float startFreq = 320000;								
	float deltaFreq = 40000;								
	bool leftActive = true;									
	bool rightActive = true;								
	float resolution = (float)(range * 1.0) / nSamples;		


	Sonar.DSSP_SetPulseDual(nPeriods, startFreq, deltaFreq, nPeriods, startFreq, deltaFreq);

	Sonar.DSSP_SetSampling(nSamples, leftActive, rightActive, false);

	Sonar.StartRec(range);

	char sonarData[BUFFERSIZE];

	int receivedSamples = Sonar.GetData(sonarData, BUFFERSIZE);	
	while (receivedSamples <= 0) {

		Sonar.StartRec(range);
		usleep(50000);

		receivedSamples = Sonar.GetData(sonarData, BUFFERSIZE);

		usleep(50000);

		if (receivedSamples <= 0) {
			std::cout << "No data from sonar, check connection." << std::endl;
			return -1;
		}
	}

	std::cout << "Sonar connected successfully." << std::endl;
	std::cout << "Range set to: " << range << "m" << std::endl;

	std::cout << "Getting new data" << std::endl;
	
	DVSFile.Create("output.dvs", leftActive, rightActive, resolution, nSamples);
	JSONFile.Create("output.json", leftActive, rightActive, resolution, nSamples);

	int pings = int_pings;

	pings = 1;
	int n = 0;

	while (pings > 0) {
		
		receivedSamples = Sonar.GetData(sonarData, BUFFERSIZE);	
		if (receivedSamples > 0) {
			for (int i = 0; i < receivedSamples; i++) {			
				
				if (parser.Add(sonarData[i])) {
				
					char* data0;
					char* data1;
					int size0 = 0;
					int size1 = 0;

					parser.GetChannelData(data0, &size0, data1, &size1);

					DVSFile.AddPingData(0.0, 0.0, 0.0, 0.0, data0, size0, data1, size1);

					JSONFile.AddPingData(0.0, 0.0, 0.0, 0.0, data0, size0, data1, size1);

					std::cout << "Size0: " << size0 << ", size1: " << size1 << ", n=" << n++ << std::endl;
					pings--;
				}
			}
		}
	}

	JSONFile.EndFile();
	
	return 1;
}
