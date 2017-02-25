/**
 * @file   main.c
 * @author Gerasimov A.S.
 * @brief  Example of singleton classes.
 */
#include <stddef.h>
#include <stdio.h>
#include <windows.h>
#include "typedef.h"
#include "helpers/Singleton.hpp"

/* Crete demo singleton class. */
class Demo
{
public:
	Demo() {};
	~Demo() {};

	void hello ( void );

private:
	static const char *name_;
};

void Demo::hello ( void )
{
	printf( "%s ...\n", name_ );
}

const char *Demo::name_(static_cast<const char*>("Demo Singleton"));

/* Create global singleton object. */
SINGLETON( Demo, DemoSingleton );

int main ( void )
{
	DemoSingleton::instance()->hello();

	return 0;
}
