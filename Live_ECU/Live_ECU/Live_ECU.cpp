// Siyang Liu (6796)
// Nio Automotives
// 2018-07-09
// Live_ECU.cpp: Read ECU live + input to Genesis + Visualization


#include <ibeosdk/ecu.hpp>
#include <ibeosdk/IpHelper.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/ReplyEcuAppBaseStatus.hpp>
#include <ibeosdk/datablocks/commands/CommandEcuAppBaseCtrl.hpp>
#include <ibeosdk/datablocks/commands/EmptyCommandReply.hpp>


#include <ibeosdk/listener/DataListener.hpp>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>
#include <math.h>

//======================================================================

using namespace ibeosdk;
using namespace cv;

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

void live_demo(LogFileManager& logFileManager, std::string ip);

//======================================================================

TimeConversion tc;


//======================================================================
//========================Siyang Liu Start==============================
//======================================================================

#define w 900 //define window size
#define unit 50 //define each step irl

//prepare global containers for frame
Mat fov = Mat::zeros(w + 20, w, CV_8UC3); // leave space at bottom
char fovTitle[] = "ECU IDC File Replay";
Mat frame;

struct myObjectList
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

struct myObj {
	int classification;
	float centerX;
	float centerY;
	float length;
	float width;
	float orientation;
	float relVelX;
	float relVelY;
	myObj() { //dummy car obj
		classification = 5;
		centerX = (float)76.1921;
		centerY = (float)4.28925;
		length = (float)4.17203;
		width = (float)1.73374;
		orientation = (float)0.0730224;
		relVelX = (float)4.44;
		relVelY = (float)0.33;
	}
	myObj(
		int cl,
		float cX,
		float cY,
		float lth,
		float wth,
		float otn,
		float rVX,
		float rVY
	) {
		this->classification = cl;
		this->centerX = cX;
		this->centerY = cY;
		this->length = lth;
		this->width = wth;
		this->orientation = otn;
		this->relVelX = rVX;
		this->relVelY = rVY;
	}
};

void myRotate(float& x, float& y, float angle) { //rotate 2D coordinate by angle
	float tmpX = cos(angle) * x + sin(angle) * y;
	float tmpY = -sin(angle) * x + cos(angle) * y;
	x = tmpX;
	y = tmpY;
}

Scalar myColor(int& c)
{
	if ((c == 5)
		|| (c == 6)) { //car & truck
		return Scalar(0, 255, 0); //green
	}
	else if (c == 3) { //ped
		return Scalar(0, 255, 255); // green + red = yellow
	}
	else if (c == 4) {
		return Scalar(0, 0, 255); // red
	}
	else if (c == 15) { //MBike
		return Scalar(255, 0, 255); // violet 
	}
	return Scalar(0, 122, 255); // orange
}

void addObj2Frame(Mat& img, myObj o) {
	// find the coordinates of obj box in ibeo coordinate
	myRotate(o.centerX, o.centerY, -o.orientation);
	float pt1x = o.centerX - o.length / (float)2.00000;
	float pt2x = o.centerX + o.length / (float)2.00000;
	float pt1y = o.centerY - o.width / (float)2.00000;
	float pt2y = o.centerY + o.width / (float)2.00000;
	float arrowx = o.centerX + +o.length / (float)2.00000 + sqrtf(o.relVelX * o.relVelX + o.relVelY * o.relVelY);
	float arrowy = o.centerY;
	myRotate(pt1x, pt1y, o.orientation);
	myRotate(pt2x, pt2y, o.orientation);
	myRotate(arrowx, arrowy, o.orientation);
	myRotate(o.centerX, o.centerY, o.orientation);
	//std::cerr << "coordinate in ibeo system:" << std::endl;
	//std::cerr << o.orientation << std::endl;
	//std::cerr << pt1x << std::endl;
	//std::cerr << pt1y << std::endl;
	//std::cerr << pt2x << std::endl;
	//std::cerr << pt2y << std::endl;
	//std::cerr << arrowx << std::endl;
	//std::cerr << arrowy << std::endl;
	//std::cerr << std::endl;

	//convert ibeo coordinate to opencv mat val
	pt1x *= w / unit / 3;
	pt1y *= w / unit / 3;
	pt2x *= w / unit / 3;
	pt2y *= w / unit / 3; //900 pixels represents 150m irl.
	arrowx *= w / unit / 3;
	arrowy *= w / unit / 3;
	//std::cerr << "mat values:" << std::endl;
	//std::cerr << pt1x << std::endl;
	//std::cerr << pt1y << std::endl;
	//std::cerr << pt2x << std::endl;
	//std::cerr << pt2y << std::endl;
	//std::cerr << arrowx << std::endl;
	//std::cerr << arrowy << std::endl;
	//std::cerr << std::endl;

	//std::cerr << "mat locations:" << std::endl;
	//std::cerr << "x1 = " << (float)w / 2.00000 - pt1y << std::endl;
	//std::cerr << "y1 = " << (float)w - pt1x << std::endl;
	//std::cerr << "x2 = " << (float)w / 2.00000 - pt2y << std::endl;
	//std::cerr << "y2 = " << (float)w - pt2x << std::endl;
	//std::cerr << std::endl;

	rectangle(img,
		Point(w / 2 - (int)pt1y, w - (int)pt1x),
		Point(w / 2 - (int)pt2y, w - (int)pt2x),
		myColor(o.classification), 2, LINE_8, 0
	);
	arrowedLine(img,
		Point(w / 2 - (int)o.centerY * (w / unit / 3), w - (int)o.centerX * (w / unit / 3)), //box center location
		Point(w / 2 - (int)arrowy, w - (int)arrowx),
		myColor(o.classification), 1, LINE_8, 0,
		0.1//tip length
	);
}

void addCircle(Mat img, Point center)
{
	circle(img,
		center,
		w / 32,
		Scalar(0, 0, 255),
		FILLED,
		LINE_8);
}

void addLine(Mat img, Point start, float angle, int length, Scalar color, int thickness)//angle in rad, left +, right -, center forward 0
{
	int dx = (int)(-sin(angle) * (float)length);
	int dy = (int)(-cos(angle) * (float)length);
	//std::cerr << dx << std::endl;
	//std::cerr << dy << std::endl;
	line(img, start,
		Point(start.x + dx, start.y + dy),
		color, thickness, LINE_8);
}

void setBackground(Mat& img) {
	//parse fov into 3*3 grid, each block represents 50m*50m irl.
	line(img, Point(0, w / 3), Point(w, w / 3), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(0, w * 2 / 3), Point(w, w * 2 / 3), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(w / 3, 0), Point(w / 3, w + 20), Scalar(128, 138, 125), 1, LINE_8);
	line(img, Point(w * 2 / 3, 0), Point(w * 2 / 3, w + 20), Scalar(128, 138, 125), 1, LINE_8);
	//origin
	line(img, Point(w / 2, w), Point(w / 2, w * 5 / 6), Scalar(0, 0, 255), 2, LINE_8);
	line(img, Point(w / 2, w), Point(w / 3, w), Scalar(0, 255, 0), 2, LINE_8);
	//FOV limits
	float fullFOV = (float)145.000 / (float)180.000 * (float)3.14159;
	//std::cerr << "fullFOV = " << fullFOV << std::endl;
	addLine(img, Point(w / 2, w), fullFOV / 2, 800, Scalar(128, 138, 125), 1);
	addLine(img, Point(w / 2, w), -fullFOV / 2, 800, Scalar(128, 138, 125), 1);
}


//======================================================================
//========================Siyang Liu End================================
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
	virtual void onData(const ObjectListEcuEt* const objectList)
	{
		//right place for this??
		frame = fov.clone(); //initialize frame

		logInfo << "ET Objects received: # " << objectList->getNbOfObjects() << std::endl;

		std::cerr << "Object List DataBlock received" << std::endl;
		myObjectList currentObjectList = {
			objectList->getTimestamp().getMilliseconds(),
			objectList->getNbOfObjects()
		};
		for (unsigned int i = 0; i < currentObjectList.nbOfObj; i++) {
			currentObjectList.addObj(
				objectList->getObjects().at(i).getObjectId(),
				objectList->getObjects().at(i).getFlags(),
				objectList->getObjects().at(i).trackedByStationaryModel(),
				objectList->getObjects().at(i).mobile(),
				objectList->getObjects().at(i).motionModelValidated(),
				objectList->getObjects().at(i).getObjectAge(),
				objectList->getObjects().at(i).getTimestamp().getMilliseconds(),
				objectList->getObjects().at(i).getObjectPredAge(),
				objectList->getObjects().at(i).getClassification(),
				objectList->getObjects().at(i).getClassCertainty(),
				objectList->getObjects().at(i).getClassAge(),
				objectList->getObjects().at(i).getObjBoxCenter().getX(),
				objectList->getObjects().at(i).getObjBoxCenter().getY(),
				objectList->getObjects().at(i).getObjBoxSize().getX(),
				objectList->getObjects().at(i).getObjBoxSize().getY(),
				objectList->getObjects().at(i).getObjBoxOrientation(),
				objectList->getObjects().at(i).getObjBoxOrientationSigma(),
				objectList->getObjects().at(i).getRelVelocity().getX(),
				objectList->getObjects().at(i).getRelVelocity().getY(),
				objectList->getObjects().at(i).getRelVelocitySigma().getX(),
				objectList->getObjects().at(i).getRelVelocitySigma().getY(),
				objectList->getObjects().at(i).getAbsVelocity().getX(),
				objectList->getObjects().at(i).getAbsVelocity().getY(),
				objectList->getObjects().at(i).getAbsVelocitySigma().getX(),
				objectList->getObjects().at(i).getAbsVelocitySigma().getY()
			);

			if ((currentObjectList.classification.at(i) == 3) //ped
				|| (currentObjectList.classification.at(i) == 4) //bicycle
				|| (currentObjectList.classification.at(i) == 5) //car
				|| (currentObjectList.classification.at(i) == 6) //truck
				|| (currentObjectList.classification.at(i) == 15)) //bike
			{
				//logInfo << currentObjectList.classification.at(i) << std::endl;
				//logInfo << currentObjectList.objBoxCenterX.at(i) << std::endl;
				//logInfo << currentObjectList.objBoxCenterY.at(i) << std::endl;
				//logInfo << currentObjectList.objBoxLength.at(i) << std::endl;
				//logInfo << currentObjectList.objBoxWidth.at(i) << std::endl;
				//logInfo << currentObjectList.objBoxOrientation.at(i) << std::endl;
				//logInfo << currentObjectList.RelVelX.at(i) << std::endl;
				//logInfo << currentObjectList.RelVelY.at(i) << std::endl;
				//logInfo << std::endl;
				myObj currentObj = myObj(
					currentObjectList.classification.at(i),
					currentObjectList.objBoxCenterX.at(i),
					currentObjectList.objBoxCenterY.at(i),
					currentObjectList.objBoxLength.at(i),
					currentObjectList.objBoxWidth.at(i),
					currentObjectList.objBoxOrientation.at(i),
					currentObjectList.RelVelX.at(i),
					currentObjectList.RelVelY.at(i)
				);
				addObj2Frame(frame, currentObj);

			}
		}

		imshow(fovTitle, frame); //update frame
		waitKey(1);

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
	const ibeosdk::LogLevel ll = ibeosdk::logLevelFromString("Debug2");
	ibeosdk::LogFile::setLogLevel(ll);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
			<< "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	live_demo(logFileManager, ip);

	exit(0);
}

//======================================================================

void live_demo(LogFileManager& logFileManager, std::string ip)
{
	//fov, frame declared globally
	setBackground(fov);// draw coordinates and background
	imshow(fovTitle, fov);
	frame = fov.clone();
	std::cerr << "frame ready" << std::endl;

	AllEcuListener allEcuListener;

	const uint16_t port = getPort(ip, 12002);
	IbeoEcu ecu(ip, port);
	ecu.setLogFileManager(&logFileManager);

	ecu.registerListener(&allEcuListener);
	ecu.getConnected();

	// 	CommandManagerAppBaseStatus cmabs;
	// 	ReplyEcuAppBaseStatus cmabsr;
	// 	logInfo << "     ==================== Status ======================" << std::endl;
	// 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	// 	logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'" << std::endl;
	//
	// 	logInfo << "==================== Start Recording =======================" << std::endl;
	// 	CommandEcuAppBaseCtrl cmabcStart(CommandEcuAppBaseCtrl::AppBaseCtrlId_StartRecording);
	// 	ReplyEcuAppBaseCtrl cmabcr;
	// 	ecu.sendCommand(cmabcStart, cmabcr, boost::posix_time::milliseconds(1500));
	// 	logError << "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'" << std::endl;
	//
	// 	logInfo << "     ==================== Status ======================" << std::endl;
	// 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	// 	logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'" << std::endl;

# ifdef _WIN32
	::Sleep(1);
# else // _WIN32
	sleep(1);
# endif // _WIN32
	// 	logInfo << "==================== Stop Recording =======================" << std::endl;
	// 	CommandEcuAppBaseCtrl cmabcStop(CommandEcuAppBaseCtrl::AppBaseCtrlId_StopRecording);
	// 	ecu.sendCommand(cmabcStop, cmabcr, boost::posix_time::milliseconds(1500));
	// 	logError << "CommandManagerAppBaseCtrlReply: " << toHex(cmabcr.getCommandId()) << "'" << std::endl;
	//
	// 	logInfo << "     ==================== Status ======================" << std::endl;
	// 	ecu.sendCommand(cmabs, cmabsr, boost::posix_time::milliseconds(500));
	// 	logError << "CommandManagerAppBaseStatusReply: " << cmabsr.getData().size() << "  '"<< cmabsr.getData() << "'" << std::endl;

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
