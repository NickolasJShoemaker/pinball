/***************************************************************************
                          Profiler.h  -  description
                             -------------------
    begin                : Tue Jul 30 2001
    copyright            : (C) 2002 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/


#ifndef PROFILER_H
#define PROFILER_H

constexpr int COUNT = 1;
constexpr int ALIGN = 2;
constexpr int BEH = 3;
constexpr int GLIGHT = 4;
constexpr int COLLISION = 5;
constexpr int PLIGHT = 6;
constexpr int PNORMAL = 7;
constexpr int RENDER = 8;
constexpr int SOUND = 9;
constexpr int SIG = 10;
constexpr int TRANS = 11;
constexpr int DRAW = 13;
constexpr int SWAP = 14;
constexpr int KEY = 15;
constexpr int RENDER_OUT = 16;
constexpr int TICK_OUT = 17;
constexpr int SWAP_OUT = 18;
constexpr int WAIT = 19;

/** Singleton class for quick and dirty profiling */
class Profiler{
	unsigned int m_aProfile[256];
	unsigned int m_iStart;
	unsigned int m_iCurrentProfile;
	unsigned int m_iCurrentTime;
	static Profiler* p_Profiler;
 protected:
	Profiler();
 public:
	~Profiler();
	static Profiler* getInstance();
	void startProfile(int i);
	void stopProfile();
	void printProfile();
};

#endif
