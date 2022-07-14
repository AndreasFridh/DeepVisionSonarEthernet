#include "JSONFileWriter.h"
#include <iomanip>
#include <string>
#include <ctime>


JSONFileWriter::JSONFileWriter(void)
{
}

JSONFileWriter::~JSONFileWriter(void)
{
}

bool JSONFileWriter::Create(const char* fileName, bool left, bool right, float res, int nSamples)
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	m_file.open(fileName,std::fstream::out);
	if(m_file.is_open()) {
		
		// Write header
		m_file << "{" << "\n";	
		m_file << "\"Timestamp\":\"" << std::put_time(&tm, "%d-%m-%YT%H:%M:%S.000Z") << "\",\n";
		m_file << "\"version\":" << 1 << ",\n";
		m_file << "\"resolution\":" << res << ",\n";
		m_file << "\"samples\":" << nSamples << ",\n";
		m_file << "\"left\":" << left << ",\n";
		m_file << "\"right\":" << right ;
		
		return true;

	} else {
		return false;
	}
}

void JSONFileWriter::AddPingData( double lat, double lon, float speed, float heading, BYTE* pLeftData, int nLeft, BYTE* pRightData, int nRight)
{
	// Write position data
	V1_Position pos;
	
	m_file << ",\n" <<"\"lat\":" << lat << ",\n";
	m_file << "\"lon\":" << lon << ",\n";
	
	if( nLeft )
		m_file << "\"pLeftData\": [";
		//m_file << pLeftData << ", ";
		for(int i = 0; i<nLeft ;i++){
			m_file << std::setprecision(2) << (int)pLeftData[i];
			if (i!=(nLeft-1)){
				m_file << ",";
			}
		}
		m_file << "],\n";

	if( nRight )
	
		m_file << "\"pRightData\": [";
		//m_file << pRightData << ", ";
		for(int i = 0; i<nRight ;i++){
			m_file << std::setprecision(2) <<  (int)pRightData[i];
			if (i!=(nRight-1)){
				m_file << ",";
			}
		}
		m_file << "]";
}

bool JSONFileWriter::EndFile()
{

	if(m_file.is_open()) {
		

		m_file << "\n" << "}" << "\n";	

		return true;

	} else {
		return false;

	}
}
