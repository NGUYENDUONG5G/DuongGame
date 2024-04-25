#pragma once
#pragma once
//refer from : https://phattrienphanmem123az.com/
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
class ImpTimer
{
public:
	ImpTimer();
	~ImpTimer();

	void start();
	int get_ticks();
	

private:
	int start_tick_;
	bool is_started_;
};



#endif // !IMP_TIMER_H_
