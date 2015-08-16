/*************************************************************************
	> File Name: hiho59.cpp
	> Author: jluchuang
	> Mail: jlu_chuang@163.com
	> Created Time: 2015年08月15日 星期六 21时11分27秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<stdio.h>
using namespace std;

struct FuncLog {
	string name;
    int startTime;

	FuncLog(){
	}

	FuncLog(string _name, int _startTime){
		name = _name;
		startTime = _startTime;
	}
	FuncLog(const FuncLog &log){
		name = log.name;
		startTime = log.startTime;
	}
};

struct Result { 
	string name; 
	int costTime;
	bool isSet;

	Result(){
	}

	Result(string _name, int _costTime){
		name = _name;
		costTime = _costTime;
		isSet = false;
	}
	Result(const Result &result){
		name = result.name;
		costTime = result.costTime;
		isSet = result.isSet; 
	}
};

bool parseOneLine(const string logLine, stack<FuncLog>& logStack, vector<Result>& resVec, int& lastTime);
bool parseTime(string time, int& timeToInt);
int stringToInt(string str);
string intToTimeStr(int t);
void parseLog(int logLen);
string formatIntToDoubleDigistsStr(int num);

bool parseOneLine(const string logLine, stack<FuncLog>& logStack, vector<Result>& resVec, int& lastTime){
	if(logLine.length() == 0){
		return true;
	}

    int i = 0;
	i = logLine.find_first_of(' ', i);
	if(i == string::npos) {
		return false;              // Get name error
	}
	string name = logLine.substr(0, i);

	int j = 0;
	j = logLine.find_first_of(' ', i+1);
	if(j == string::npos) {
		return false;              // Get time error
	}
	string time = logLine.substr(i+1, j-i-1);
	int timeToInt = 0;
	if(!parseTime(time, timeToInt)){
		return false;              // Time format error
	}

	if(timeToInt < lastTime || timeToInt < 0){
		return false;              // Time ASC order error
	}
	else {
		lastTime = timeToInt;
	}

	string action = logLine.substr(j+1, logLine.length() - j-1);
	if(action == "START" || action == "END") {
		if(action == "START") {
			logStack.push(FuncLog(name, timeToInt));
			resVec.push_back(Result(name, timeToInt));
            return true;
		}
		else {
			if(logStack.empty() || logStack.top().name != name) {
				return false;
			}
			else {
				int costTime = timeToInt - logStack.top().startTime;
				if(costTime < 0) {
					return false;
				}
				int resPos = resVec.size()-1;
				for( ; resPos >= 0; resPos --){
					if(resVec[resPos].isSet == false){
						break;
					}
				}
				resVec[resPos].costTime = costTime;
				resVec[resPos].isSet = true;
				//cout<<logStack.top().name<<" "<<intToTimeStr(costTime)<<endl;
				logStack.pop();
				return true;
			}
		}
	}
	else{
		return false;              //Action format error
	}
}

bool parseTime(string time, int& timeToInt) {
	char separator = ':';
	int i = 0;
	i = time.find_first_of(separator, i);
	if(i == string::npos) {
		return false;             //Get hour error
	}
	int hour = stringToInt(time.substr(0,i));

	int j = 0;
	j = time.find_first_of(separator, i+1);
	if(j == string::npos) {
		return false;             //Get minite error
	}
	int minite = stringToInt(time.substr(i+1, j-i-1));

	int second = stringToInt(time.substr(j+1, time.length() - j - 1));

    timeToInt = (hour*3600 + minite*60 + second);

	return true;
}

int stringToInt(string str) {
	int res = 0;
	int i = 0;
	for( ; i < str.length(); i++) {
		int tmp = str[i] - '0';
		res = res*10 + tmp;
	}
	return res;
}

string intToTimeStr(int t){
	string res;
	int sec = t%60;
	t = t/60;
	int min = t%60;
	t = t/60;
	int hou = t;
	res += formatIntToDoubleDigistsStr(hou);
	res += ":";
	res += formatIntToDoubleDigistsStr(min);
	res += ":";
	res += formatIntToDoubleDigistsStr(sec);
	return res;
}

string formatIntToDoubleDigistsStr(int num){
    char tmp[3];
	if(num < 10){
		sprintf(tmp, "0%d", num);
	} 
	else{
		sprintf(tmp, "%d", num);
	}
	return string(tmp);
}

void parseLog(int logLen) {
	if(logLen & 0x1)
	{
		cout<<"Incorrect performance log"<<endl;
		return;
	}
	int resNo = 0;
	int lastTime = 0;
	vector <Result> resVec;
	stack <FuncLog> logStack;
	for(int i = 0; i < logLen; i++){
		//getchar();
		string logLine;
		getline(cin, logLine);

		if(!parseOneLine(logLine, logStack, resVec, lastTime)) {
	        cout<<"Incorrect performance log"<<endl;
			return;
		}
	}
	if(!logStack.empty()){
		cout<<"Incorrect performance log"<<endl;
		return;
	}
	for(int i = 0; i<resVec.size(); i++){
		cout<<resVec[i].name<<" "<<intToTimeStr(resVec[i].costTime)<<endl;
	}
}

int main() {
	int n = 0;
	cin>>n;
	getchar();
	parseLog(n);
	return 0;
}
