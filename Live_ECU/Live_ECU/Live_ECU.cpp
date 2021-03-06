// Siyang Liu (6796)
// Nio Automotives
// 2018-07-09
// entry point
// Live_ECU.cpp: Read ECU live + input to Genesis + Visualization

#include <ibeosdk/ecu.hpp>

#include <ibeosdk/IpHelper.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseCtrl.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>

#include <ibeosdk/listener/DataListener.hpp>

#include "IbeoDraw.h"


//======================================================================

using namespace ibeosdk;

//======================================================================

const ibeosdk::Version::MajorVersion majorVersion(5);
const ibeosdk::Version::MinorVersion minorVersion(2);
const ibeosdk::Version::Revision revision(2);
const ibeosdk::Version::PatchLevel patchLevel;
const ibeosdk::Version::Build build;
const std::string info = "Live ECU visualization";

ibeosdk::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);

IbeoSDK ibeoSDK;

//======================================================================

void live_read(LogFileManager& logFileManager, std::string ip);

//======================================================================

TimeConversion tc;

//======================================================================

class AllEcuListener : public ibeosdk::DataListener<ibeosdk::ScanEcu>,
	public ibeosdk::DataListener<ObjectListEcu>,
	public ibeosdk::DataListener<ObjectListEcuEt>,
	public ibeosdk::DataListener<Image>,
	public ibeosdk::DataListener<PositionWgs84_2604>,
	public ibeosdk::DataListener<VehicleStateBasicEcu2806>,
	public ibeosdk::DataListener<VehicleStateBasicEcu>,
	public ibeosdk::DataListener<MeasurementList2821>,
	public ibeosdk::DataListener<DeviceStatus>,
	public ibeosdk::DataListener<DeviceStatus6303>,
	public ibeosdk::DataListener<LogMessageError>,
	public ibeosdk::DataListener<LogMessageDebug>,
	public ibeosdk::DataListener<LogMessageNote>,
	public ibeosdk::DataListener<LogMessageWarning> {
public:
	virtual ~AllEcuListener() {}

public:
	//========================================
	//Scan points
	virtual void onData(const ScanEcu* const scan)
	{
		logInfo << "Scan received: # " << scan->getScanNumber()
			<< "  time: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	//Deprecated
	virtual void onData(const ObjectListEcu* const objectList)
	{
		logInfo << "Objects received: # " << objectList->getNumberOfObjects() << std::endl;
	}

	//========================================
	// Obj List
	IbeoECUObjList parseObjList(const ObjectListEcuEt* const objList) { //Parse Ibeo data block into struct

		//std::cerr << "Object List DataBlock received" << std::endl;
		IbeoECUObjList currentObjectList = {
			objList->getTimestamp().getMilliseconds(), // put in milliseconds
			objList->getNbOfObjects()
		};
		//for (unsigned int i = 0; i < _MAX_OBJ_NUM_; i++) {
		for (unsigned int i = 0; i < objList->getNbOfObjects(); i++) {
			if (i >= _MAX_OBJ_NUM_) {
				std::cerr << "ERROR: Object list overflow" << std::endl;
				break;
			}
			//currentObjectList.IbeoECUObjs[i].cnt = i;
			currentObjectList.IbeoECUObjs[i].objID = objList->getObjects().at(i).getObjectId();
			//currentObjectList.IbeoECUObjs[i].flag = objList->getObjects().at(i).getFlags();
			currentObjectList.IbeoECUObjs[i].trackedByStationaryModel = objList->getObjects().at(i).trackedByStationaryModel();
			currentObjectList.IbeoECUObjs[i].mobile = objList->getObjects().at(i).mobile();
			currentObjectList.IbeoECUObjs[i].motionModelValidated = objList->getObjects().at(i).motionModelValidated();
			//currentObjectList.IbeoECUObjs[i].objAge = objList->getObjects().at(i).getObjectAge();
			//currentObjectList.IbeoECUObjs[i].timestamp = objList->getObjects().at(i).getTimestamp().getMilliseconds();
			//currentObjectList.IbeoECUObjs[i].objPredAge = objList->getObjects().at(i).getObjectPredAge();
			//currentObjectList.IbeoECUObjs[i].classification = objList->getObjects().at(i).getClassification();
			//currentObjectList.IbeoECUObjs[i].classCertainty = objList->getObjects().at(i).getClassCertainty();
			//currentObjectList.IbeoECUObjs[i].classAge = objList->getObjects().at(i).getClassAge();
			currentObjectList.IbeoECUObjs[i].centerX = objList->getObjects().at(i).getObjBoxCenter().getX();
			currentObjectList.IbeoECUObjs[i].centerY = objList->getObjects().at(i).getObjBoxCenter().getY();
			currentObjectList.IbeoECUObjs[i].length = objList->getObjects().at(i).getObjBoxSize().getX();
			currentObjectList.IbeoECUObjs[i].width = objList->getObjects().at(i).getObjBoxSize().getY();
			currentObjectList.IbeoECUObjs[i].orientation = objList->getObjects().at(i).getObjBoxOrientation();
			//currentObjectList.IbeoECUObjs[i].orientationSigma = objList->getObjects().at(i).getObjBoxOrientationSigma();
			//currentObjectList.IbeoECUObjs[i].relVelX = objList->getObjects().at(i).getRelVelocity().getX();
			//currentObjectList.IbeoECUObjs[i].relVelY = objList->getObjects().at(i).getRelVelocity().getY();
			//currentObjectList.IbeoECUObjs[i].relVelSigmaX = objList->getObjects().at(i).getRelVelocitySigma().getX();
			//currentObjectList.IbeoECUObjs[i].relVelSigmaY = objList->getObjects().at(i).getRelVelocitySigma().getY();
			currentObjectList.IbeoECUObjs[i].absVelX = objList->getObjects().at(i).getAbsVelocity().getX();
			currentObjectList.IbeoECUObjs[i].absVelY = objList->getObjects().at(i).getAbsVelocity().getY();
			//currentObjectList.IbeoECUObjs[i].absVelSigmaX = objList->getObjects().at(i).getAbsVelocitySigma().getX();
			//currentObjectList.IbeoECUObjs[i].absVelSigmaY = objList->getObjects().at(i).getAbsVelocitySigma().getY();
		}
		return currentObjectList;
	}

	virtual void onData(const ObjectListEcuEt* const objectList)
	{
		logInfo << "ET Objects received: # " << objectList->getNbOfObjects() << std::endl;

		//push objList to queue
		objListQ.push(parseObjList(objectList));
		//std::cout << "Push Q; current Q size = " << objListQ.size() << std::endl;
	}

	//========================================
	virtual void onData(const Image* const image)
	{
		logInfo << std::setw(5) << image->getSerializedSize() << " Bytes  " << "Image received: time: " << tc.toString(image->getTimestamp().toPtime()) << std::endl;
	}

	//========================================
	void onData(const PositionWgs84_2604* const wgs84)
	{
		logInfo << std::setw(5) << wgs84->getSerializedSize() << " Bytes  "
			<< "PositionWGS84 received: time: " << tc.toString(wgs84->getPosition().getTimestamp().toPtime())
			<< std::endl;
	}

	//========================================
	virtual void onData(const VehicleStateBasicEcu2806* const vsb)
	{
		logInfo << "VSB (0x2806) " << tc.toString(vsb->getTimestamp().toPtime(), 3) << std::endl;
	}

	//========================================
	virtual void onData(const VehicleStateBasicEcu* const vsb)
	{
		logInfo << "VSB " << tc.toString(vsb->getTimestamp().toPtime(), 3) << std::endl;
	}

	//========================================
	void onData(const MeasurementList2821* const ml)
	{
		logInfo << std::setw(5) << ml->getSerializedSize() << " Bytes  "
			<< "MeasurementList received: time: " << tc.toString(ml->getTimestamp().toPtime())
			<< " LN: '" << ml->getListName() << "' GN: '" << ml->getGroupName() << "'"
			<< std::endl;
	}

	//========================================
	virtual void onData(const DeviceStatus* const devStat)
	{
		logInfo << std::setw(5) << devStat->getSerializedSize() << " Bytes  " << "DevStat received" << std::endl;
	}

	//========================================
	virtual void onData(const DeviceStatus6303* const devStat)
	{
		logInfo << std::setw(5) << devStat->getSerializedSize() << " Bytes  " << "DevStat 0x6303 received" << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageError* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Error) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageWarning* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Warning) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageNote* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Note) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageDebug* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << " Bytes  "
			<< "LogMessage (Debug) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	void onData(const Odometry9002* const odo)
	{
		logInfo << std::setw(5) << odo->getSerializedSize() << " Bytes  "
			<< "Steering angle: " << odo->getSteeringAngle()
			<< std::endl;
	}

	//========================================
	//ACTIVE
	void onData(const SystemMonitoringCanStatus6700* const canStatus)
	{
		logInfo << std::setw(5) << canStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringCANStatus6700 received: "
			<< canStatus->toString() << "  "
			<< std::endl;
	}
	//========================================
	//ACTIVE
	void onData(const SystemMonitoringDeviceStatus6701* const deviceStatus)
	{
		logInfo << std::setw(5) << deviceStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringDeviceStatus6701 received: "
			<< deviceStatus->toString() << "  "
			<< std::endl;
	}
	//========================================
	//ACTIVE
	void onData(const SystemMonitoringSystemStatus6705* const systemStatus)
	{
		logInfo << std::setw(5) << systemStatus->getSerializedSize() << " Bytes  "
			<< "SystemMonitoringSystemStatus6705 received: "
			<< systemStatus->toString() << "  "
			<< std::endl;
	}
	//========================================
}; // AllEcuListener

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
		std::cerr << argv[0] << " " << " IP [LOGFILE]" << std::endl;
		std::cerr << "\tIP is the ip address of the Ibeo Ecu, e.g. 192.168.0.1." << std::endl;
		std::cerr << "\tLOGFILE name of the log file. If ommitted, the log output will be performed to stderr." << std::endl;
		return 1;
	}

	hasLogFile = (argc == maxNbOfNeededArguments);
	return 0;
}

//======================================================================

int main(const int argc, const char** argv)
{
	//  HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawFrame, parseObjList(objectList), 0, NULL);

	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	bool hasLogFile;
	const int checkResult = checkArguments(argc, argv, hasLogFile);
	if (checkResult != 0)
		exit(checkResult);
	int currArg = 1;

	std::string ip = argv[currArg++];

	const off_t maxLogFileSize = 1000000;

	LogFileManager logFileManager;
	ibeosdk::LogFile::setTargetFileSize(maxLogFileSize);

	if (hasLogFile) {
		ibeosdk::LogFile::setLogFileBaseName(argv[currArg++]);
	}
	const ibeosdk::LogLevel ll = ibeosdk::logLevelFromString("Error");
	ibeosdk::LogFile::setLogLevel(ll);

	logFileManager.start();
	
	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
			<< "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	live_read(logFileManager, ip);

	exit(0);
}

//======================================================================

void live_read(LogFileManager& logFileManager, std::string ip)
{
	//start new thread
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)doSubThread, NULL, 0, 0);
	std::cerr << "Subthread created" << std::endl;

	AllEcuListener allEcuListener;

	const uint16_t port = getPort(ip, 12002);
	IbeoEcu ecu(ip, port);
	ecu.setLogFileManager(&logFileManager);

	ecu.registerListener(&allEcuListener);
	ecu.getConnected();
	std::cerr << "ECU Connected" << std::endl;

	//CommandManagerAppBaseStatus cmabs;
	//ReplyEcuAppBaseStatus cmabsr;
	//logInfo << "     ==================== Status ======================" << std::endl;
	//ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	//logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '" << cmabsr.getData() << "'" << std::endl;

	//logInfo << "==================== Start Recording =======================" << std::endl;
	//CommandEcuAppBaseCtrl cmabcStart(CommandEcuAppBaseCtrl::AppBaseCtrlId_StartRecording);
	//ReplyEcuAppBaseCtrl cmabcr;
	//ecu.sendCommand(cmabcStart, cmabcr, boost::posix_time::milliseconds(1500));
	//logError << "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'" << std::endl;

	//logInfo << "     ==================== Status ======================" << std::endl;
	//ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	//logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '" << cmabsr.getData() << "'" << std::endl;

# ifdef _WIN32
	::Sleep(1);
# else // _WIN32
	sleep(1);
# endif // _WIN32
	//logInfo << "==================== Stop Recording =======================" << std::endl;
	//CommandEcuAppBaseCtrl cmabcStop(CommandEcuAppBaseCtrl::AppBaseCtrlId_StopRecording);
	//ecu.sendCommand(cmabcStop, cmabcr, boost::posix_time::milliseconds(1500));
	//logError << "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'" << std::endl;

	//logInfo << "     ==================== Status ======================" << std::endl;
	//ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	//logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '" << cmabsr.getData() << "'" << std::endl;

	// Just to keep the program alive
	while (true) {
		if (!ecu.isConnected())
			return;
#	  ifdef _WIN32
		::Sleep(1);
#	  else // _WIN32
		sleep(1);
#	  endif // _WIN32
	} // while
}

//======================================================================
