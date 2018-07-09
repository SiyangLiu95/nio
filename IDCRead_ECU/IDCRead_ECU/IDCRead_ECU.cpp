// Siyang Liu (6796)
// Nio Automotives
// 2018-07-05
// IDCRead_ECU.cpp: parse idc file from ECU into structs for Genesis 

#include <ibeosdk/ecu.hpp>

#include <ibeosdk/devices/IdcFile.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseCtrl.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>


//======================================================================

using namespace ibeosdk;
using namespace cv;

//======================================================================

const ibeosdk::Version::MajorVersion majorVersion(5);
const ibeosdk::Version::MinorVersion minorVersion(2);
const ibeosdk::Version::Revision revision(2);
const ibeosdk::Version::PatchLevel patchLevel;
const ibeosdk::Version::Build build;
const std::string info = "Parse .IDC from ECU";

ibeosdk::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);

IbeoSDK ibeoSDK;

//======================================================================

void file_demo(const std::string& filename);

//======================================================================

TimeConversion tc;

//======================================================================
//========================Siyang Liu====================================
//======================================================================

struct objectList
{
	uint32_t scanStartTimestamp; // avaiable: Frac, Milli, Micro seconds
	int nbOfObj;
	std::vector<uint16_t> objID;
	std::vector<uint16_t> flag; /*	Flags_TrackedByStationaryModel  = 0x0040, ///< is object tracked using stationary model
									Flags_Mobile                    = 0x0080, ///< Has been detected/validated as mobile. (the current tracking model is irrelevant; this flag just means it has been moving at some time)
									Flags_Validated                 = 0x0100  ///< Object (stationary or dynamic) has been validated, i.e. valid enough to send out to the interface */
	std::vector<bool> trackedByStationaryModel;
	std::vector<bool> mobile;
	std::vector<bool> motionModelValidated;
	std::vector<uint32_t> objAge;
	std::vector<uint32_t> timestamp; // avaiable: Frac, Milli, Micro seconds
	std::vector<uint16_t> objPredAge;
	std::vector<int> classification;
	std::vector<uint8_t> classCertainty;
	std::vector<uint32_t> classAge;
	std::vector<float> objBoxCenterX;
	std::vector<float> objBoxCenterY; //Sigma not available yet
	std::vector<float> objBoxLength; //Box.X
	std::vector<float> objBoxWidth; //Box.Y
	std::vector<float> objBoxOrientation; //rad
	std::vector<float> objBoxOrientationSigma;
	std::vector<float> RelVelX;
	std::vector<float> RelVelY;
	std::vector<float> RelVelSigmaX;
	std::vector<float> RelVelSigmaY;
	std::vector<float> AbsVelX;
	std::vector<float> AbsVelY;
	std::vector<float> AbsVelSigmaX;
	std::vector<float> AbsVelSigmaY;
	/*Other avaiable fields:
	nbOfContourPoints;IdxOfclosestPoint;RefPointLocation;RefPointCoords+Sigma;
	RefPointPosCorrCoeffs;ObjPriority;ObjExtMeasurement;List of Contour Points;
	*/
	void addObj(
		uint16_t objID,
		uint16_t flag,
		bool trackedByStationaryModel,
		bool mobile,
		bool motionModelValidated,
		uint32_t objAge,
		uint32_t timestamp, // avaiable: Frac, Milli, Micro seconds
		uint16_t objPredAge,
		int classification,
		uint8_t classCertainty,
		uint32_t classAge,
		float objBoxCenterX,
		float objBoxCenterY,
		float objBoxLength, //Box.X
		float objBoxWidth, //Box.Y
		float objBoxOrientation, //rad
		float objBoxOrientationSigma,
		float RelVelX,
		float RelVelY,
		float RelVelSigmaX,
		float RelVelSigmaY,
		float AbsVelX,
		float AbsVelY,
		float AbsVelSigmaX,
		float AbsVelSigmaY
	) {
		this->objID.push_back(objID);
		this->flag.push_back(flag);
		this->trackedByStationaryModel.push_back(trackedByStationaryModel);
		this->mobile.push_back(mobile);
		this->motionModelValidated.push_back(motionModelValidated);
		this->objAge.push_back(objAge);
		this->timestamp.push_back(timestamp);
		this->objPredAge.push_back(objPredAge);
		this->classification.push_back(classification);
		this->classCertainty.push_back(classCertainty);
		this->classAge.push_back(classAge);
		this->objBoxCenterX.push_back(objBoxCenterX);
		this->objBoxCenterY.push_back(objBoxCenterY);
		this->objBoxLength.push_back(objBoxLength);
		this->objBoxWidth.push_back(objBoxWidth);
		this->objBoxOrientation.push_back(objBoxOrientation);
		this->objBoxOrientationSigma.push_back(objBoxOrientationSigma);
		this->RelVelX.push_back(RelVelX);
		this->RelVelY.push_back(RelVelY);
		this->RelVelSigmaX.push_back(RelVelSigmaX);
		this->RelVelSigmaY.push_back(RelVelSigmaY);
		this->AbsVelX.push_back(AbsVelX);
		this->AbsVelY.push_back(AbsVelY);
		this->AbsVelSigmaX.push_back(AbsVelSigmaX);
		this->AbsVelSigmaY.push_back(AbsVelSigmaY);
	}
};

bool DoLOG = false;

//======================================================================
//========================Siyang Liu====================================
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
	// Active ECU Scan point output
	void onData(const ScanEcu* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "ScanEcu received: # " << scan->getScanNumber()
			<< "  #Pts: " << scan->getNumberOfScanPoints()
			<< "  ScanStart: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	//Scala Scan points
	void onData(const Scan2208* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << " Bytes  "
			<< "Scan2208 received: # " << scan->getScanNumber()
			<< "  #Pts: " << scan->getSubScans().at(0).getNbOfPoints()
			<< "  ScanStart: " << tc.toString(scan->getSubScans().at(0).getStartScanTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	void onData(const ObjectListEcu* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListEcu received: # " << objList->getNumberOfObjects() << std::endl;
	}

	//========================================
	// Active ECU object list ouput
	void onData(const ObjectListEcuEt* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << " Bytes  " << "ObjectListEcuEts received: # " << objList->getNbOfObjects() << std::endl;

		objectList currentObjectList = {
			objList->getTimestamp().getMilliseconds(),
			objList->getNbOfObjects()
		};
		for (unsigned int i = 0; i < currentObjectList.nbOfObj; i++) {
			currentObjectList.addObj(
				objList->getObjects().at(i).getObjectId(),
				objList->getObjects().at(i).getFlags(),
				objList->getObjects().at(i).trackedByStationaryModel(),
				objList->getObjects().at(i).mobile(),
				objList->getObjects().at(i).motionModelValidated(),
				objList->getObjects().at(i).getObjectAge(),
				objList->getObjects().at(i).getTimestamp().getMilliseconds(),
				objList->getObjects().at(i).getObjectPredAge(),
				objList->getObjects().at(i).getClassification(),
				objList->getObjects().at(i).getClassCertainty(),
				objList->getObjects().at(i).getClassAge(),
				objList->getObjects().at(i).getObjBoxCenter().getX(),
				objList->getObjects().at(i).getObjBoxCenter().getY(),
				objList->getObjects().at(i).getObjBoxSize().getX(),
				objList->getObjects().at(i).getObjBoxSize().getY(),
				objList->getObjects().at(i).getObjBoxOrientation(),
				objList->getObjects().at(i).getObjBoxOrientationSigma(),
				objList->getObjects().at(i).getRelVelocity().getX(),
				objList->getObjects().at(i).getRelVelocity().getY(),
				objList->getObjects().at(i).getRelVelocitySigma().getX(),
				objList->getObjects().at(i).getRelVelocitySigma().getY(),
				objList->getObjects().at(i).getAbsVelocity().getX(),
				objList->getObjects().at(i).getAbsVelocity().getY(),
				objList->getObjects().at(i).getAbsVelocitySigma().getX(),
				objList->getObjects().at(i).getAbsVelocitySigma().getY()
			);

			if (currentObjectList.objID.at(i) == 147) {
				logInfo << currentObjectList.classification.at(i) << std::endl;
				logInfo << currentObjectList.objBoxCenterX.at(i) << std::endl;
				logInfo << currentObjectList.objBoxCenterY.at(i) << std::endl;
				logInfo << currentObjectList.objBoxLength.at(i) << std::endl;
				logInfo << currentObjectList.objBoxWidth.at(i) << std::endl;
				logInfo << currentObjectList.objBoxOrientation.at(i) << std::endl;
				logInfo << currentObjectList.RelVelX.at(i) << std::endl;
				logInfo << currentObjectList.RelVelY.at(i) << std::endl;
				logInfo << std::endl;
			}
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
