#pragma once

class baseState
{
public:
	void run();
protected:
	int x=10;

};

class Home :baseState
{
	int x = 10;
};