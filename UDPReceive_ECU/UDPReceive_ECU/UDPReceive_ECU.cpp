// Siyang Liu (6796) implementing template by Siwei Peng
// NIO Automotives 
// 2018-07-10
// UDPReceive_ECU.cpp: simualtes receiving via UDP

#include <iostream>
#include "stdafx.h"

#include "IbeoECUObjTypeDef.h"
#include "IbeoUDPReceive.h"


int main()
{
	IbeoUDPReceive receiveList;
	receiveList.InitSocket("192.168.0.15", "1001");
	cout << "Receive socket initialized " << endl;

	IbeoECUObjList ol;
	
	while (true)
	{
		/*map info receiver*/
		if (receiveList.ReceiveStructData(&ol))
		{
			cout << "received objlist: " << (int)ol.nbOfObjects << endl;
		}
		else
		{
			cout << "receive failed" << endl;
			continue;
		}
	}
	return 0;
}

