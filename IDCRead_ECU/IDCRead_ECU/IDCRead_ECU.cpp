//======================================================================
/*! \file IbeoSdkFileDemo.cpp
*
* \copydoc Copyright
* \author Mario Brumm (mb)
* \date Jun 1, 2012
*
* Demo project for reading IDC files and process the data blocks.
*///-------------------------------------------------------------------

#include <ibeosdk/ecu.hpp>
 
#include <ibeosdk/devices/IdcFile.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseCtrl.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>


#ifdef WITHJPEGSUPPORT
#  include <ibeosdk/jpegsupport/jmemio.h>
#endif // WITHJPEGSUPPORT

#ifdef WITHJPEGSUPPORTDEF
#  include <ibeosdk/jpegsupport/jmemio.h>
#endif

#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

//======================================================================

using namespace ibeosdk;
using namespace cv;

//======================================================================

const ibeosdk::Version::MajorVersion majorVersion(5);
const ibeosdk::Version::MinorVersion minorVersion(2);
const ibeosdk::Version::Revision revision(2);
const ibeosdk::Version::PatchLevel patchLevel;
const ibeosdk::Version::Build build;
const std::string info = "IbeoSdkFileDemo";

ibeosdk::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);

IbeoSDK ibeoSDK;

//======================================================================

void file_demo(const std::string& filename);

//======================================================================

TimeConversion tc;

//======================================================================

class AllListener : 
	public ibeosdk::DataListener<ScanEcu>,
	public ibeosdk::DataListener<Scan2208>,
	public ibeosdk::DataListener<ObjectListEcu>,
	public ibeosdk::DataListener<ObjectListEcuEt>,
	public ibeosdk::DataListener<ObjectListEcuEtDyn>,
	public ibeosdk::DataListener<RefObjectListEcuEtDyn>,
	public ibeosdk::DataListener<PositionWgs84_2604>,
	public ibeosdk::DataListener<MeasurementList2821>,
	public ibeosdk::DataListener<VehicleStateBasicEcu2806>,
	public ibeosdk::DataListener<VehicleStateBasicEcu>,
	public ibeosdk::DataListener<ObjectAssociationList4001>,
	public ibeosdk::DataListener<DeviceStatus>,
	public ibeosdk::DataListener<DeviceStatus6303>,
	public ibeosdk::DataListener<LogMessageError>,
	public ibeosdk::DataListener<LogMessageWarning>,
	public ibeosdk::DataListener<LogMessageNote>,
	public ibeosdk::DataListener<LogMessageDebug>,
	public ibeosdk::DataListener<Odometry9002>,
	public ibeosdk::DataListener<GpsImu9001>,
	public ibeosdk::DataListener<SystemMonitoringCanStatus6700>,
	public ibeosdk::DataListener<SystemMonitoringDeviceStatus6701>,
	public ibeosdk::DataListener<SystemMonitoringSystemStatus6705> {
public:
	virtual ~AllListener() {}

public:

	//========================================
	void onData(const ScanEcu* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "ScanEcu received: # " << scan->getScanNumber()
			<< "  #Pts: " << scan->getNumberOfScanPoints()
			<< "  ScanStart: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	void onData(const Scan2208* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "Scan2208 received: # " << scan->getScanNumber()
			<< "  #Pts: " << scan->getSubScans().at(0).getNbOfPoints()
			<< "  ScanStart: " << tc.toString(scan->getSubScans().at(0).getStartScanTimestamp().toPtime(), 3)
			<< std::endl;
		//for (unsigned int i = 0; i < scan->getScanNumber; ++i) {
		//	std::cerr << "Scan " << i << scan->getSubScans.get << std::endl;
		//}
	}

	//========================================
	void onData(const ObjectListEcu* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListEcu received: # " << objList->getNumberOfObjects() << std::endl;
	}

	//========================================
	void onData(const ObjectListEcuEt* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListEcUEts received: # " << objList->getNbOfObjects() << std::endl;
		for (unsigned int i = 0; i < objList->getNbOfObjects(); ++i) {
			logInfo << "Scan " << i << objList->getObjects().at(i).getAbsVelocity() << std::endl;
		}
	}

	//========================================
	void onData(const ObjectListEcuEtDyn* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListEcuEtDyn received: # " << objList->getNbOfObjects()
			<< std::endl
			<< "  ObjListId: " << toHex(objList->getObjectListId())
			<< "  DevIntfVr: " << toHex(objList->getDeviceInterfaceVersion())
			<< "  ObjListId: " << toHex(int(objList->getDeviceType()))
			<< std::endl;
	}

	//========================================
	void onData(const RefObjectListEcuEtDyn* const refObjList)
	{
		logInfo << std::setw(5) << refObjList->getSerializedSize() << " Bytes  " << "RefObjectListEcuEtDyn received: # " << refObjList->getNbOfObjects()
			<< std::endl
			<< "  ObjListId: " << toHex(refObjList->getObjectListId())
			<< "  DevIntfVr: " << toHex(refObjList->getDeviceInterfaceVersion())
			<< "  ObjListId: " << toHex(refObjList->getDeviceType())
			<< std::endl;
	}



	//========================================
	void onData(const PositionWgs84_2604* const wgs84)
	{
		logInfo << std::setw(5) << wgs84->getSerializedSize() << " Bytes  "
			<< "PositionWGS84 received: time: " << tc.toString(wgs84->getPosition().getTimestamp().toPtime())
			<< std::endl;
	}

	//========================================
	void onData(const VehicleStateBasicEcu2806* const vsb)
	{
		logInfo << std::setw(5) << vsb->getSerializedSize() << " Bytes  "
			<< "VSB (ECU;old) received: time: " << tc.toString(vsb->getTimestamp().toPtime())
			<< std::endl;
	}

	//========================================
	void onData(const VehicleStateBasicEcu* const vsb)
	{
		logInfo << std::setw(5) << vsb->getSerializedSize() << " Bytes  "
			<< "VSB (ECU) received: time: " << tc.toString(vsb->getTimestamp().toPtime())
			<< std::endl;
	}
	//========================================
	void onData(const MeasurementList2821* const ml)
	{
		logInfo << std::setw(5) << ml->getSerializedSize() << " Bytes  "
			<< "MeasurementList received: time: " << tc.toString(ml->getTimestamp().toPtime())
			<< " LN: '" << ml->getListName() << "' GN: '" << ml->getGroupName() << "'" << "Num: " << ml->getMeasList().getSize()
			<< std::endl;

		typedef std::vector<Measurement> MLVector;

		MLVector::const_iterator itMl = ml->getMeasList().getMeasurements().begin();
		int ctr = 0;
		for (; itMl != ml->getMeasList().getMeasurements().end(); ++itMl, ++ctr)
		{
			logInfo << " M" << ctr << ":" << (*itMl) << std::endl;
		}
	}

	//========================================
	void onData(const ObjectAssociationList4001* const oaList)
	{
		logInfo << std::setw(5) << oaList->getSerializedSize() << " Bytes  "
			<< "ObjectAssociationList4001 received"
			<< std::endl
			<< "  RObjListId: " << toHex(oaList->getRefObjListId())
			<< "  RDevIntfVr: " << toHex(oaList->getRefDevInterfaceVersion())
			<< "  DevType: " << toHex(oaList->getRefDevType())
			<< std::endl
			<< "  DObjListId: " << toHex(oaList->getDutObjListId())
			<< "  DDevIntfVr: " << toHex(oaList->getDutDevInterfaceVersion())
			<< "  DevType: " << toHex(oaList->getDutDevType())
			<< "  # of associations: " << oaList->getObjectAssociations().size()
			<< std::endl;
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
	void onData(const TimeRecord9000* const tim)
	{
		logInfo << std::setw(5) << tim->getSerializedSize() << " Bytes  "
			<< "Internal Clock Times Received with size: " << tim->getInternalClockTimes().size()
			<< "External Clock Times Received with size: " << tim->getExternalClockTimes().size()
			<< std::endl;
	}
	//========================================
	void onData(const Odometry9002* const odo)
	{
		logInfo << std::setw(5) << odo->getSerializedSize() << " Bytes  "
			<< "Steering angle: " << odo->getSteeringAngle()
			<< std::endl;
	}
	//========================================
	void onData(const GpsImu9001* const gpsImu)
	{
		logInfo << std::setw(5) << gpsImu->getSerializedSize() << " Bytes  "
			<< "GpsImu9001 received: time: " << tc.toString(gpsImu->getTimestamp().getReceivedTimeEcu().toPtime())
			<< " " << "Source: " << GpsImu9001::toString(gpsImu->getSource()) << "  "
			<< std::endl;
	}
	//========================================
	void onData(const SystemMonitoringCanStatus6700* const canStatus)
	{
		logInfo << std::setw(5) << canStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringCANStatus6700 received: "
			<< canStatus->toString() << "  "
			<< std::endl;
	}
	//========================================
	void onData(const SystemMonitoringDeviceStatus6701* const deviceStatus)
	{
		logInfo << std::setw(5) << deviceStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringDeviceStatus6701 received: "
			<< deviceStatus->toString() << "  "
			<< std::endl;
	}
	//========================================
	void onData(const SystemMonitoringSystemStatus6705* const systemStatus)
	{
		logInfo << std::setw(5) << systemStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringSystemStatus6705 received: "
			<< systemStatus->toString() << "  "
			<< std::endl;
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
	const ibeosdk::LogLevel ll = ibeosdk::logLevelFromString("Debug");
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

	Mat image = imread("C:\\Users\\siyang.liu\\Desktop\\linux_common_commands.jpg"); 
	imshow("显示图像", image);
	waitKey(0);

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
