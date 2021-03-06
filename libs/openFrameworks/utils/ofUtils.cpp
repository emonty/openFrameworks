#include "ofUtils.h"
#include "ofImage.h"
#include "ofTypes.h"
#include "Poco/String.h"
#include "ofAppRunner.h"

#if defined(TARGET_OF_IPHONE) || defined(TARGET_OSX ) || defined(TARGET_LINUX)
	#include "sys/time.h"
#endif

#ifdef TARGET_OSX 	
	#ifndef TARGET_OF_IPHONE
		#include <mach-o/dyld.h>
		#include <sys/param.h> // for MAXPATHLEN	 	
	#endif
#endif 

#ifdef TARGET_WIN32
    #include <mmsystem.h>
	#ifdef _MSC_VER
		#include <direct.h>
	#endif

#endif

static bool enableDataPath = true;
static unsigned long startTime = ofGetSystemTime();   //  better at the first frame ?? (currently, there is some delay from static init, to running.

//--------------------------------------
int ofGetElapsedTimeMillis(){
	return (int)(ofGetSystemTime() - startTime);
}

//--------------------------------------
float ofGetElapsedTimef(){
	return ((float) ((int)(ofGetSystemTime() - startTime)) / 1000.0f);
}

//--------------------------------------
void ofResetElapsedTimeCounter(){
	startTime = ofGetSystemTime();
}

//=======================================
// this is from freeglut, and used internally:
/* Platform-dependent time in milliseconds, as an unsigned 32-bit integer.
 * This value wraps every 49.7 days, but integer overflows cancel
 * when subtracting an initial start time, unless the total time exceeds
 * 32-bit, where the GLUT API return value is also overflowed.
 */
unsigned long ofGetSystemTime( ) {
	#ifndef TARGET_WIN32
		struct timeval now;
		gettimeofday( &now, NULL );
		return now.tv_usec/1000 + now.tv_sec*1000;
	#else
		#if defined(_WIN32_WCE)
			return GetTickCount();
		#else
			return timeGetTime();
		#endif
	#endif
}

//--------------------------------------------------
int ofGetSeconds(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_sec;
}

//--------------------------------------------------
int ofGetMinutes(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_min;
}

//--------------------------------------------------
int ofGetHours(){
	time_t 	curr;
	tm 		local;
	time(&curr);
	local	=*(localtime(&curr));
	return local.tm_hour;
}

//--------------------------------------------------
int ofGetYear(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  int year = local.tm_year + 1900;
  return year;
}

//--------------------------------------------------
int ofGetMonth(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  int month = local.tm_mon + 1;
  return month;
}

//--------------------------------------------------
int ofGetDay(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  return local.tm_mday;
}

//--------------------------------------------------
int ofGetWeekday(){
  time_t    curr;
  tm       local;
  time(&curr);
  local   =*(localtime(&curr));
  return local.tm_wday;
}

//--------------------------------------------------
void ofEnableDataPath(){
	enableDataPath = true;
}

//--------------------------------------------------
void ofDisableDataPath(){
	enableDataPath = false;
}

//--------------------------------------------------
//use ofSetDataPathRoot() to override this
#if defined TARGET_OSX
	static string dataPathRoot = "../../../data/";
#else
	static string dataPathRoot = "data/";
#endif

//--------------------------------------------------
void ofSetDataPathRoot(string newRoot){
	string newPath = "";
	
	#ifdef TARGET_OSX
		#ifndef TARGET_OF_IPHONE 
			char path[MAXPATHLEN];
			uint32_t size = sizeof(path);				

			if (_NSGetExecutablePath(path, &size) == 0){
				//printf("executable path is %s\n", path);
				string pathStr = string(path);

				//theo: check this with having '/' as a character in a folder name - OSX treats the '/' as a ':'
				//checked with spaces too!

				vector < string> pathBrokenUp = ofSplitString( pathStr, "/");

				newPath = "/";

				for(int i = 0; i < pathBrokenUp.size()-1; i++){				
					newPath += pathBrokenUp[i];
					newPath += "/";
				}

				//cout << newPath << endl;   // some sanity checks here				
				//system( "pwd" );

				chdir ( newPath.c_str() );				
				//system("pwd");        
			}else{				
				ofLog(OF_LOG_FATAL_ERROR, "buffer too small; need size %u\n", size);
			}
		#endif 
	#endif
		
	dataPathRoot = newPath+newRoot;
}

//--------------------------------------------------
string ofToDataPath(string path, bool makeAbsolute){
	if( enableDataPath ){

		//check if absolute path has been passed or if data path has already been applied
		//do we want to check for C: D: etc ?? like  substr(1, 2) == ':' ??
		if( path.length()==0 || (path.substr(0,1) != "/" &&  path.substr(1,1) != ":" &&  path.substr(0,dataPathRoot.length()) != dataPathRoot)){
			path = dataPathRoot+path;
		}

		if(makeAbsolute && (path.length()==0 || path.substr(0,1) != "/")){
			#ifndef TARGET_OF_IPHONE

			#ifndef _MSC_VER
				char currDir[1024];
				path = "/"+path;
				path = getcwd(currDir, 1024)+path;
			#else

				char currDir[1024];
				path = "\\"+path;
				path = _getcwd(currDir, 1024)+path;
				std::replace( path.begin(), path.end(), '/', '\\' ); // fix any unixy paths...


			#endif


			#else
				//do we need iphone specific code here?
			#endif
		}

	}
	return path;
}

//----------------------------------------
template <>
string ofToHex(const string& value) {
	ostringstream out;
	// how many bytes are in the string
	int numBytes = value.size();
	for(int i = 0; i < numBytes; i++) {
		// print each byte as a 2-character wide hex value
		out << setfill('0') << setw(2) << hex << (unsigned int) value[i];
	}
	return out.str();
}

//----------------------------------------
string ofToHex(const char* value) {
	// this function is necessary if you want to print a string
	// using a syntax like ofToHex("test")
	return ofToHex((string) value);
}

//----------------------------------------
int ofToInt(const string& intString) {
	int x = 0;
	istringstream cur(intString);
	cur >> x;
	return x;
}

//----------------------------------------
int ofHexToInt(const string& intHexString) {
	int x = 0;
	istringstream cur(intHexString);
	cur >> hex >> x;
	return x;
}

//----------------------------------------
char ofHexToChar(const string& charHexString) {
	int x = 0;
	istringstream cur(charHexString);
	cur >> hex >> x;
	return (char) x;
}

//----------------------------------------
float ofHexToFloat(const string& floatHexString) {
	int x = 0;
	istringstream cur(floatHexString);
	cur >> hex >> x;
	return *((float*) &x);
}

//----------------------------------------
string ofHexToString(const string& stringHexString) {
	stringstream out;
	stringstream stream(stringHexString);
	// a hex string has two characters per byte
	int numBytes = stringHexString.size() / 2;
	for(int i = 0; i < numBytes; i++) {
		string curByte;
		// grab two characters from the hex string
		stream >> setw(2) >> curByte;
		// prepare to parse the two characters
		stringstream curByteStream(curByte);
		int cur = 0;
		// parse the two characters as a hex-encoded int
		curByteStream >> hex >> cur;
		// add the int as a char to our output stream
		out << (char) cur;
	}
	return out.str();
}

//----------------------------------------
float ofToFloat(const string& floatString) {
	float x = 0;
	istringstream cur(floatString);
	cur >> x;
	return x;
}

//----------------------------------------
bool ofToBool(const string& boolString) {
	static const string trueString = "true";
	static const string falseString = "false";
	string lower = Poco::toLower(boolString);
	if(lower == trueString) {
		return true;
	}
	if(lower == falseString) {
		return false;
	}
	bool x = false;
	istringstream cur(lower);
	cur >> x;
	return x;
}

//----------------------------------------
char ofToChar(const string& charString) {
	char x = '\0';
	istringstream cur(charString);
	cur >> x;
	return x;
}

//----------------------------------------
template <> string ofToBinary(const string& value) {
	stringstream out;
	int numBytes = value.size();
	for(int i = 0; i < numBytes; i++) {
		bitset<8> bitBuffer(value[i]);
		out << bitBuffer;
	}
	return out.str();
}

//----------------------------------------
string ofToBinary(const char* value) {
	// this function is necessary if you want to print a string
	// using a syntax like ofToBinary("test")
	return ofToBinary((string) value);
}

//----------------------------------------
int ofBinaryToInt(const string& value) {
	const int intSize = sizeof(int) * 8;
	bitset<intSize> binaryString(value);
	return (int) binaryString.to_ulong();
}

//----------------------------------------
char ofBinaryToChar(const string& value) {
	const int charSize = sizeof(char) * 8;
	bitset<charSize> binaryString(value);
	return (char) binaryString.to_ulong();
}

//----------------------------------------
float ofBinaryToFloat(const string& value) {
	const int floatSize = sizeof(float) * 8;
	bitset<floatSize> binaryString(value);
	unsigned long result = binaryString.to_ulong();
	// this line means:
	// 1 take the address of the unsigned long
	// 2 pretend it is the address of a float
	// 3 then use it as a float
	// this is a bit-for-bit 'typecast'
	return *((float*) &result);
}

//----------------------------------------
string ofBinaryToString(const string& value) {
	ostringstream out;
	stringstream stream(value);
	bitset<8> byteString;
	int numBytes = value.size() / 8;
	for(int i = 0; i < numBytes; i++) {
		stream >> byteString;
		out << (char) byteString.to_ulong();
	}
	return out.str();
}

//--------------------------------------------------
vector <string> ofSplitString(const string& str, const string& delimiter = " "){
    vector<string> elements;
	// Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiter, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiter, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
    	elements.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiter, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiter, lastPos);
    }
    return elements;
}

//--------------------------------------------------
string ofJoinString(vector <string> stringElements, const string & delimiter){
	string resultString = "";
	int numElements = stringElements.size();
	
	for(int k = 0; k < numElements; k++){
		if( k < numElements-1 ){
			resultString += stringElements[k] + delimiter;
		}
	}
	
	return resultString;
}

//--------------------------------------------------
bool ofIsStringInString(string haystack, string needle){
	return ( strstr(haystack.c_str(), needle.c_str() ) != NULL );
}

//--------------------------------------------------
void ofLaunchBrowser(string url){

	// http://support.microsoft.com/kb/224816

	//make sure it is a properly formatted url
	if(url.substr(0,7) != "http://"){
		ofLog(OF_LOG_WARNING, "ofLaunchBrowser: url must begin http://");
		return;
	}

	//----------------------------
	#ifdef TARGET_WIN32
	//----------------------------

		#if (_MSC_VER)
		// microsoft visual studio yaks about strings, wide chars, unicode, etc
		ShellExecuteA(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#else
		ShellExecute(NULL, "open", url.c_str(),
                NULL, NULL, SW_SHOWNORMAL);
		#endif

	//----------------------------
	#endif
	//----------------------------

	//--------------------------------------
	#ifdef TARGET_OSX
	//--------------------------------------
		// ok gotta be a better way then this,
		// this is what I found...
		string commandStr = "open "+url;
		system(commandStr.c_str());
	//----------------------------
	#endif
	//----------------------------

	//--------------------------------------
	#ifdef TARGET_LINUX
	//--------------------------------------
		string commandStr = "xdg-open "+url;
		int ret = system(commandStr.c_str());
		if(ret!=0) ofLog(OF_LOG_ERROR,"ofLaunchBrowser: couldn't open browser");
	//----------------------------
	#endif
	//----------------------------
}

//--------------------------------------------------
string ofGetVersionInfo(){
	string version;
	stringstream sstr;
	sstr << "of version: " << OF_VERSION << endl;
	return sstr.str();
}

//---- new to 006
//from the forums http://www.openframeworks.cc/forum/viewtopic.php?t=1413

//--------------------------------------------------
void ofSaveScreen(string filename) {
   ofImage screen;
   screen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
   screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
   screen.saveImage(filename);
}

//--------------------------------------------------
int saveImageCounter = 0;
void ofSaveFrame(){
   string fileName = ofToString(saveImageCounter) + ".png";
   ofSaveScreen(fileName);
   saveImageCounter++;
}

//levels are currently:
// see ofConstants.h
// OF_LOG_NOTICE
// OF_LOG_WARNING
// OF_LOG_ERROR
// OF_LOG_FATAL_ERROR

int currentLogLevel =  OF_DEFAULT_LOG_LEVEL;
//--------------------------------------------------
void ofSetLogLevel(int logLevel){
	currentLogLevel = logLevel;
}

//--------------------------------------------------
void ofLog(int logLevel, string message){
	if(logLevel >= currentLogLevel){
		if(logLevel == OF_LOG_VERBOSE){
			printf("OF_VERBOSE: ");
		}
		else if(logLevel == OF_LOG_NOTICE){
			printf("OF_NOTICE: ");
		}
		else if(logLevel == OF_LOG_WARNING){
			printf("OF_WARNING: ");
		}
		else if(logLevel == OF_LOG_ERROR){
			printf("OF_ERROR: ");
		}
		else if(logLevel == OF_LOG_FATAL_ERROR){
			printf("OF_FATAL_ERROR: ");
		}
		printf("%s\n",message.c_str());
	}
}

//--------------------------------------------------
void ofLog(int logLevel, const char* format, ...){
	//thanks stefan!
	//http://www.ozzu.com/cpp-tutorials/tutorial-writing-custom-printf-wrapper-function-t89166.html

	if(logLevel >= currentLogLevel){
		va_list args;
		va_start( args, format );
		if(logLevel == OF_LOG_VERBOSE){
			printf("OF_VERBOSE: ");
		}
		else if(logLevel == OF_LOG_NOTICE){
			printf("OF_NOTICE: ");
		}
		else if(logLevel == OF_LOG_WARNING){
			printf("OF_WARNING: ");
		}
		else if(logLevel == OF_LOG_ERROR){
			printf("OF_ERROR: ");
		}
		else if(logLevel == OF_LOG_FATAL_ERROR){
			printf("OF_FATAL_ERROR: ");
		}
		vprintf( format, args );
		printf("\n");
		va_end( args );
	}
}

//for setting console color
//doesn't work in the xcode console - do we need this?
//works fine on the terminal though - not much use

//--------------------------------------------------
void ofSetConsoleColor(int color){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	#else
		printf("\033[%im",  color);
	#endif
}

//--------------------------------------------------
void ofRestoreConsoleColor(){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), OF_CONSOLE_COLOR_RESTORE);
	#else
		printf("\033[%im",  OF_CONSOLE_COLOR_RESTORE);
	#endif
}


