//============================================================================
// Name        : ECTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Master.h>
#include <Domain.h>
#include <EL1004.h>
#include <EL3161.h>
#include <chrono>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <thread>

//#define RT

extern "C"
{
#include <signal.h>
#include <unistd.h>

#ifdef RT
#include <sched.h>
#include <string.h>
#include <sys/mman.h>
#endif
}

#define OFFSET 0
#define GAIN 1

using namespace std;

//Globals
volatile bool g_run = true;

//Signal callback
void abrt( int )
{
	g_run = false;
}

string getDateStr()
{
	time_t rawtime;
	char buffer[80];

	time( &rawtime );
	auto timeinfo = localtime( &rawtime );

	strftime( buffer, 80, "%Y-%m-%d_%H:%M:%S", timeinfo );

	return buffer;
}

int main( int argc, char **argv )
{
#ifdef RT 	//Real time stuff
	//Prio
	struct sched_param param;
	param.sched_priority = 49;
	if( sched_setscheduler( 0, SCHED_FIFO, &param ) == -1 )
	{
		cerr << "setscheduler failed...\n";
		return 1;
	}

	//Lock memory
	if( mlockall( MCL_CURRENT | MCL_FUTURE ) == -1 )
	{
		cerr << "mlockall failed..\n";
		return 1;
	}

	//Prefault stack
	{
		uint8_t dummy[1024*8];
		memset( dummy, 0, 1024*8 );
	}
#endif

	try
	{
		//Setup ethercat bus
		luna::Master master;
		luna::Domain domain( master );
		luna::EL3161 ain1( &master, 0, 5 );
		domain.add( &ain1 );

		master.activate();
		domain.fetchPD();

		//Cycle time
		const chrono::milliseconds cycle_time{ 10 };

		//Call abrt function on Ctrl+C
		signal( SIGINT, abrt );
		signal( SIGTERM, abrt );

		//Open file
		string filename{ "/tmp/data_" + getDateStr() + ".csv" };
		cout << "Opening file: " << filename << endl;
		ofstream outp_file( filename );
		if( !outp_file.is_open() )
		{
			cerr << "Failed to open file." << endl;
			return 1;
		}


		//Header for csv
		outp_file << "Data" << endl;

		while( g_run )
		{
			chrono::system_clock::time_point cycle_start_time = chrono::system_clock::now();

			//Calculate value
			double value = (double)(ain1.getValue() - OFFSET) * (double)GAIN;

			outp_file << value << endl;
			cout << value << endl;
			master.updateDomain( &domain );

			std::this_thread::sleep_until( cycle_start_time + cycle_time );
		}

		outp_file.close();

		master.deactivate();

		cout << endl << endl;
	}
	catch( const luna::Master::errors &e )
	{
		switch( e )
		{
			case luna::Master::errors::Request:
				cerr << "Master request failed...\n";
				break;
			case luna::Master::errors::Activate:
				cerr << "Master Activate failed...\n";
				break;
			default:
				cerr << "Undefined master error...\n";
				break;
		}
	}
	catch( const luna::Domain::errors &e )
	{
		switch( e )
		{
			case luna::Domain::errors::Create:
				cerr << "Domain create error...\n";
				break;
			default:
				cerr << "Undefined domain error...\n";
				break;
		}
	}
	catch( ... )
	{
		cerr << "Undefined error.\n";
	}

	return 0;
}
