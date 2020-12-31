#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"
#include "set.h"

class Application
{
public:
	Application() : m_result(0)
	{
	}

	~Application()
	{
	}

	void executeListTestCase();
	void executeArrayTestCase();
	void executeSetCase();
	int exec();
	void printHelp();
private:
	int m_result;
};
#endif
