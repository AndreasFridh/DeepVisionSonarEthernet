#include "DVSFileWriter.h"


CDVSFileWriter::CDVSFileWriter(void)
{
}

CDVSFileWriter::~CDVSFileWriter(void)
{
}

bool CDVSFileWriter::Create(const char* fileName, bool left, bool right, float res, int nSamples)
{
	m_file.open(fileName,std::fstream::out);
	if(m_file.is_open()) {
	
		// Version 1
		unsigned int version = 1;
		m_file.write( (char*) &version, sizeof(version) );

		// Write header
		V1_FileHeader header;
		header.sampleRes = res;
		header.nSamples = nSamples;
		header.left = left;
		header.right = right; 
		header.lineRate = float( 750.0 / ( nSamples * res) );
		m_file.write((char*)&header, sizeof(header));

		return true;

	} else {
		return false;

	}
}

void CDVSFileWriter::AddPingData( double lat, double lon, float speed, float heading, BYTE* pLeftData, int nLeft, BYTE* pRightData, int nRight)
{
	// Write position data
	V1_Position pos;
	pos.heading = heading;
	pos.lat = lat;
	pos.lon = lon;
	pos.speed = speed;
	m_file.write((char*)&pos, sizeof(V1_Position));

	if( nLeft )
		m_file.write( pLeftData, nLeft );

	if( nRight )
		m_file.write(  pRightData, nRight );
}
