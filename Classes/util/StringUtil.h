#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class StringUtil
{
public:
	static vector<string> splitToStr(const string& src, string delimit)
	{
		vector<string> ret;
		size_t last = 0;   
		size_t index=src.find_first_of(delimit,last); 
		while (index!=std::string::npos)  {   
			ret.push_back(src.substr(last,index-last));   
			last=index+1;    
			index=src.find_first_of(delimit,last);  
		}  if (index-last>0)  {     
			ret.push_back(src.substr(last,index-last)); 
		}
		return ret;  
	}

	static vector<int> splitToInt(const string& src, string delimit)
	{
		vector<int> ret;
		size_t last = 0;   
		size_t index=src.find_first_of(delimit,last); 
		while (index!=std::string::npos)  {   
			ret.push_back(atoi(src.substr(last,index-last).c_str()));   
			last=index+1;    
			index=src.find_first_of(delimit,last);  
		}  if (index-last>0)  {     
			ret.push_back(atoi(src.substr(last,index-last).c_str())); 
		}
		return ret;  
	}
	//类型转化string
	template <class T> static string m_toStr(T tmp)
	{
		stringstream ss;
		ss << tmp;
		return ss.str();
	}
	//int加到sring尾部
	static string StringAddInt(string s,int i ){
		std::ostringstream oss;
		oss << s << i;
		return oss.str();
	}

};


#endif