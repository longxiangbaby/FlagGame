#ifndef __ARRAYUTIL_H__
#define __ARRAYUTIL_H__
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


class ArrayUtil
{
public:

	template <class T> static int getIndex(vector<T> _data,T object)
	{
		auto iter = std::find(_data.begin(), _data.end(), object);

		if (iter != _data.end())
			return iter - _data.begin();

		return -1;
	}

	static bool isLike(vector<string> _data,string object)
	{
		int length=_data.size();
		for (int i = length - 1; i >= 0 ; i--)
		{
			bool isTrue=(_data[i]==object);
			if (_data[i]==object)
			{
				return true;
			}
		}
		return false;
	}

	template <class T> static void eraseObject(vector<T> _data,T object, bool removeAll = false)
	{
		if (removeAll)
		{
			for (auto iter = _data.begin(); iter != _data.end();)
			{
				if ((*iter) == object)
				{
					iter = _data.erase(iter);
				}
				else
				{
					++iter;
				}
			}
		}
		else
		{
			auto iter = std::find(_data.begin(), _data.end(), object);
			if (iter != _data.end())
			{
				_data.erase(iter);
			}
		}
	}


};
#endif