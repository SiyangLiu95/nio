// Siyang Liu (6796)
// Nio Automotives
// 2018-06-27
// IDCRead.cpp: parse idc file from a single Scala into structs suitable for fusion


#include <ibeosdk/scala.hpp>

#include <ibeosdk/devices/IdcFile.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseCtrl.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>

#include <iostream>
#include <cstdlib>

//======================================================================

using namespace ibeosdk;

//======================================================================

const ibeosdk::Version::MajorVersion majorVersion(5);
const ibeosdk::Version::MinorVersion minorVersion(2);
const ibeosdk::Version::Revision revision(2);
const ibeosdk::Version::PatchLevel patchLevel;
const ibeosdk::Version::Build build;
const std::string info = "ScalaFileRead";

ibeosdk::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);

IbeoSDK ibeoSDK;

//======================================================================

void file_demo(const std::string& filename);

//======================================================================

TimeConversion tc;

//======================================================================

struct scanPoints
{
	uint16_t  scanNumber;  // Num of this scan.
	uint16_t  scannerStatus;
	/*  SS_MotorOn = 0x0001,
	SS_Laser1On = 0x0002,
	SS_DemoModeOn = 0x0004,
	SS_FrequencyLocked = 0x0008,
	SS_Laser2On = 0x0080,
	SS_MotorDirectionConterClockwise = 0x0100
	*/
	uint16_t deviceId; //ID of this scanner
	std::string startScanTimestamp;
	std::string endScanTimestamp;
	int16_t startScanAngle;
	int16_t endScanAngle;
	uint8_t mirrorSide; //Bit0: 0=front mirror side; 1= rear mirror side
	uint16_t mirrorTilt; // current mirror plane relative to roattion axis; unit = 1/1000 deg
	uint32_t numScanPoints;
	// Scan points data
	std::vector<uint8_t> echoId; //Echo number of this point (zero-based). 0..3
	std::vector<uint8_t> layerId; //Scan layer of this point (zero-based).
	std::vector<uint16_t> flags;
	/*SPFML_Transparent   = 0x0001,
	SPFML_Rain          = 0x0002,
	SPFML_Ground        = 0x0004,
	SPFML_Dirt          = 0x0008,

	SPFML_HighThreshold = 0x0010,
	SPFML_Noise         = 0x0020,
	SPFML_NearRange     = 0x0040,
	SPFML_Marker        = 0x0080,

	SPFML_Blooming      = 0x0100,
	SPFML_Background    = 0x0200,
	SPFML_Reserved3     = 0x0400,
	SPFML_Reserved4     = 0x0800,

	SPFML_Reflector     = 0x1000,
	SPFML_Reserved5     = 0x2000,
	SPFML_InterlacingPt = 0x4000, // only for A1 prototype
	SPFML_Reserved7     = 0x8000
	*/
	std::vector<int16_t> horizontalAngle; //Angle of this point in angle ticks in the scanner coordinate system
	std::vector<uint16_t> radialDistance; //Distance of this point in the scanner coordinate system in cm
	std::vector<uint16_t> echoPulseWidth; //Detected width of this echo pulse in cm

										  //scanPoints(
										  //	uint16_t  scanNumber,uint16_t  scannerStatus,uint16_t deviceId,
										  //	NTPTime startScanTimestamp,NTPTime endScanTimestamp,
										  //	int16_t startScanAngle,int16_t endScanAngle,
										  //	uint8_t mirrorSide,uint16_t mirrorTilt,uint32_t numScanPoints
										  //	) {
										  //	this->scanNumber = scanNumber;
										  //	this->scannerStatus = scannerStatus;
										  //	this->deviceId = deviceId;
										  //	this->startScanTimestamp = tc.toString(startScanTimestamp.toPtime(), 3);
										  //	this->endScanTimestamp = tc.toString(endScanTimestamp.toPtime(), 3); ;
										  //	this->startScanAngle = startScanAngle;
										  //	this->endScanAngle = endScanAngle;
										  //	this->mirrorSide = mirrorSide;
										  //	this->mirrorTilt = mirrorTilt;
										  //	this->numScanPoints = numScanPoints;
										  //	}

	void addScanPoint(
		uint8_t echoId, uint8_t layerId, uint16_t flags,
		int16_t horizontalAngle, uint16_t radialDistance, uint16_t echoPulseWidth
	) {
		this->echoId.push_back(echoId);
		this->layerId.push_back(layerId);
		this->flags.push_back(flags);
		this->horizontalAngle.push_back(horizontalAngle);
		this->radialDistance.push_back(radialDistance);
		this->echoPulseWidth.push_back(echoPulseWidth);
	}
};

//======================================================================

std::vector<scanPoints> allScanPoints;

//======================================================================

class AllListener : public ibeosdk::DataListener<FrameEndSeparator>,
	public ibeosdk::DataListener<ScanLux>,
	public ibeosdk::DataListener<Scan2208>,
	public ibeosdk::DataListener<ObjectListLux>,
	public ibeosdk::DataListener<ObjectListScala>,
	public ibeosdk::DataListener<ObjectListScala2271>,
	public ibeosdk::DataListener<MeasurementList2821>,
	public ibeosdk::DataListener<VehicleStateBasicLux>,
	public ibeosdk::DataListener<DeviceStatus>,
	public ibeosdk::DataListener<DeviceStatus6303>,
	public ibeosdk::DataListener<LogMessageError>,
	public ibeosdk::DataListener<LogMessageWarning>,
	public ibeosdk::DataListener<LogMessageNote>,
	public ibeosdk::DataListener<LogMessageDebug> {
public:
	virtual ~AllListener() {}

public:
	//========================================
	void onData(const FrameEndSeparator* const fes)
	{
		logInfo << std::setw(5) << fes->getSerializedSize() << " Bytes  "
			<< "Frame received: # " << fes->getFrameId()
			<< "  Frame time: " << tc.toString(fes->getHeaderNtpTime().toPtime())
			<< std::endl;
	}

	//========================================
	void onData(const ScanLux* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "ScanLux received: # " << scan->getScanNumber()
			<< "  ScanStart: " << tc.toString(scan->getStartTimestamp().toPtime())
			<< std::endl;
	}

	//========================================
	void onData(const Scan2208* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "Scan2208 received: # " << scan->getScanNumber()
			// << "  #SubScans: " << scan->getNbOfSubScans()
			<< "  #Pts: " << scan->getSubScans().at(0).getNbOfPoints()
			//<< "  ScanStart: " << tc.toString(scan->getSubScans().at(0).getStartScanTimestamp().toPtime(), 3)
			<< std::endl;
		scanPoints currentScanPoint = {
			scan->getScanNumber(),
			scan->getScannerStatus(),
			scan->getDeviceId(),
			tc.toString(scan->getSubScans().at(0).getStartScanTimestamp().toPtime(), 3),
			tc.toString(scan->getSubScans().at(0).getEndScanTimestamp().toPtime(), 3),
			scan->getSubScans().at(0).getStartScanAngle(),
			scan->getSubScans().at(0).getEndScanAngle(),
			scan->getSubScans().at(0).getMirrorSide(),
			scan->getSubScans().at(0).getMirrorTilt(),
			scan->getSubScans().at(0).getNbOfPoints(),
		};

		std::cerr << "Flag";
		for (unsigned int i = 0; i < currentScanPoint.numScanPoints; i++) {
			currentScanPoint.addScanPoint(
				scan->getSubScans().at(0).getScanPoints().at(i).getEchoId(),
				scan->getSubScans().at(0).getScanPoints().at(i).getLayerId(),
				scan->getSubScans().at(0).getScanPoints().at(i).getFlags(),
				scan->getSubScans().at(0).getScanPoints().at(i).getHorizontalAngle(),
				scan->getSubScans().at(0).getScanPoints().at(i).getRadialDistance(),
				scan->getSubScans().at(0).getScanPoints().at(i).getEchoPulseWidth()
			);
			if (i % 500 == 0) {
				std::cerr << std::hex << (scan->getSubScans().at(0).getScanPoints().at(i).getFlags()) << " ";
			}
		}
		std::cerr << std::endl;

		//Store history of all scan points
		//allScanPoints.push_back(currentScanPoint);

		//Show flags
		//logInfo << "Added one scan to allScanPoints array, "
		//	<< "Current array size: " << allScanPoints.size() << std::endl;

		/*
		std::vector<SubScan2208> SubScans = scan->getSubScans();
		std::vector<ScanPoint2208> ScanPoints = SubScans.at(0).getScanPoints();
		for (unsigned int i = 0; i < subscans.size(); i++) {
		scanpoints = subscans.at(i).getscanpoints();
		for (unsigned int j = 0; j < scanpoints.size(); j++) {

		loginfo << "angel(" << i << "," << j << ") = " << scanpoints.at(j).gethorizontalangle()
		<< "dist(" << i << "," << j << ") = " << scanpoints.at(j).getradialdistance();

		}
		loginfo << std::endl;
		}*/
	}

	//========================================
	void onData(const ObjectListLux* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListLux received: # " << objList->getNumberOfObjects() << std::endl;
	}

	//========================================
	void onData(const ObjectListScala* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListScala received: # " << objList->getNumberOfObjects() << std::endl;
	}

	//========================================
	void onData(const ObjectListScala2271* const objs)
	{
		logInfo << std::setw(5) << objs->getSerializedSize() << " Bytes  "
			<< "ObjectList 2271 received. Scan: " << objs->getScanNumber()
			<< "  ObjLstId: " << int(objs->getObjectListId())
			<< "  #Obj:" << objs->getNumberOfObjects()
			<< std::endl;
	}

	//========================================
	void onData(const VehicleStateBasicLux* const vsb)
	{
		logInfo << std::setw(5) << vsb->getSerializedSize() << " Bytes  " << "VSB (LUX) received: time: " << tc.toString(vsb->getTimestamp().toPtime()) << std::endl;
	}

	void onData(const MeasurementList2821* const ml)
	{
		logInfo << std::setw(5) << ml->getSerializedSize() << " Bytes  "
			<< "MeasurementList received: time: " << tc.toString(ml->getTimestamp().toPtime())
			<< " LN: '" << ml->getListName() << "' GN: '" << ml->getGroupName() << "'" << "Num: " << ml->getMeasList().getSize()
			<< std::endl;

		//typedef std::vector<Measurement> MLVector;

		//MLVector::const_iterator itMl = ml->getMeasList().getMeasurements().begin();
		//int ctr = 0;
		//for (; itMl != ml->getMeasList().getMeasurements().end(); ++itMl, ++ctr)
		//{
		//	logInfo << " M" << ctr << ":" << (*itMl) << std::endl;
		//}
	}

	//========================================
	void onData(const DeviceStatus* const devStat)
	{
		logInfo << std::setw(5) << devStat->getSerializedSize() << " Bytes  "
			<< "DevStat received"
			<< std::endl;
	}

	//========================================
	void onData(const DeviceStatus6303* const devStat)
	{
		logInfo << std::setw(5) << devStat->getSerializedSize() << " Bytes  "
			<< "DevStat 0x6303 received"
			<< std::endl;
	}

	//========================================
	void onData(const LogMessageError* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Error) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	void onData(const LogMessageWarning* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Warning) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	void onData(const LogMessageNote* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Note) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	void onData(const LogMessageDebug* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Debug) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
	//========================================
}; // AllListener

   //======================================================================
   //======================================================================
   //======================================================================

class CustomLogStreamCallbackExample : public CustomLogStreamCallback {
public:
	virtual ~CustomLogStreamCallbackExample() {}
public:
	virtual void onLineEnd(const char* const s, const int)
	{
		std::cerr << s << std::endl;
	}
}; // CustomLogStreamCallback


   //======================================================================
   //======================================================================
   //======================================================================

int checkArguments(const int argc, const char** argv, bool& hasLogFile)
{
	const int minNbOfNeededArguments = 2;
	const int maxNbOfNeededArguments = 3;

	bool wrongNbOfArguments = false;
	if (argc < minNbOfNeededArguments) {
		std::cerr << "Missing argument" << std::endl;
		wrongNbOfArguments = true;
	}
	else if (argc > maxNbOfNeededArguments) {
		std::cerr << "Too many argument" << std::endl;
		wrongNbOfArguments = true;
	}

	if (wrongNbOfArguments) {
		std::cerr << argv[0] << " " << " INPUTFILENAME [LOGFILE]" << std::endl;
		std::cerr << "\tINPUTFILENAME Name of the file to use as input instead of a sensor." << std::endl;
		std::cerr << "\tLOGFILE name of the log file. If ommitted, the log output will be performed to stderr." << std::endl;
		return 1;
	}

	hasLogFile = (argc == maxNbOfNeededArguments);
	return 0;
}

//======================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	bool hasLogFile;
	const int checkResult = checkArguments(argc, argv, hasLogFile);
	if (checkResult != 0)
		exit(checkResult);
	int currArg = 1;

	std::string filename = argv[currArg++];

	const off_t maxLogFileSize = 1000000;

	LogFileManager logFileManager;
	ibeosdk::LogFile::setTargetFileSize(maxLogFileSize);

	if (hasLogFile) {
		ibeosdk::LogFile::setLogFileBaseName(argv[currArg++]);
	}
	const ibeosdk::LogLevel ll = ibeosdk::logLevelFromString("Debug2");
	ibeosdk::LogFile::setLogLevel(ll);

	static CustomLogStreamCallbackExample clsce;

	if (!hasLogFile)
		LogFile::setCustomLogStreamCallback(&clsce);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
			<< "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	file_demo(filename);

	exit(0);
}

//======================================================================

void file_demo(const std::string& filename)
{
	IdcFile file;
	file.open(filename);
	if (file.isOpen()) {
		AllListener allListener;

		file.registerListener(&allListener);

		const DataBlock* db = NULL;
		unsigned short nbMessages = 0; // # of messages we parsed

		while (file.isGood()) {
			db = file.getNextDataBlock();
			if (db == NULL) {
				continue; // might be eof or unknown file type
			}
			file.notifyListeners(db);
			++nbMessages;
		}

		logDebug << "EOF reached. " << nbMessages << " known blocks found." << std::endl;
	}
	else {
		logError << "File not readable." << std::endl;
	}
}

//======================================================================
