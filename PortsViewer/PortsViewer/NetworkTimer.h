#pragma once

#include "Singleton.h"

class NetworkTimer : public Singleton<NetworkTimer>
{
public:
	NetworkTimer(void);
	~NetworkTimer(void);
public:
	void run();
private:
	UINT_PTR timer_;
};

