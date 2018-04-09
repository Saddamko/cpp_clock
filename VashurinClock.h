#ifndef VashurinClockH
#define VashurinClockH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>

#include <ctime>
#include <time.h>
#include <cmath>
#include <exception>

#endif

int ClockSize = 300;
//---------------------------------------------------------------------------
class TFormClock : public TForm
{
__published:	// IDE-managed Components
	TImage *ImageClock;
	TTimer *Timer1;
	TImage *Image1;
	void __fastcall FormCreate(TObject *Sender);
void __fastcall OnTimerEvent(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormClock(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormClock *FormClock;
//---------------------------------------------------------------------------

class Clock {
public:
	int min, hou, sec;
public:
	void Init(int hou1, int min1, int sec1 ){
		if (hou1 < 0 || hou1>23 || min1 < 0 || min1>60 || sec1 < 0 || sec1>60)
		{
			//throw gcnew Exception();
		}
		min = min1;
		sec = sec1;
		hou = hou1;
	}

	void InitUser(int hou1, int min1, int sec1)
	{
		sec++;
		if (sec==60)
		{
			min++;
			sec = 0;
		}
		if (min == 60)
		{
			if (hou == 24 && min == 60 && sec == 60)
			{
				min = 0;
				hou = 1;
			}
			hou++;
			min = 0;
		}
	}


	void get_time() {

		time_t seconds; //кол-во секунд, прошщедщего с 1-го января 1970
		time(&seconds);
		struct tm lt;
		localtime_s(&seconds, &lt ); //часы, мин, сек
		min = lt.tm_min;
		sec = lt.tm_sec;
		hou = lt.tm_hour;
	}

	virtual double get_X() {
		return 0;
	}

	virtual double get_Y() {
		return 0;
	}

};

class PointHou : public Clock {
public:
	double get_X() {
		return ClockSize/2 + 75 * sin(2 * 3.14F*(hou * 60 + min) / 12 / 60);
	}
	double get_Y() {
		return ClockSize/2 - 75 * cos(2 * 3.14F*(hou * 60 + min) / 12 / 60);
	}
};

class PointMin : public Clock {
public:

	double get_X() {
		return  ClockSize/2 + 100 * sin(2 * 3.14F* min / 60);
	}
	double get_Y() {
		return  ClockSize/2 - 100 * cos(2 * 3.14F* min / 60);
	}
};

class PointSec : public Clock {
public:

	double get_X() {
		return ClockSize/2 + 125 * sin(2 * 3.14F* sec / 60);
	}
	double get_Y() {
		return ClockSize/2 - 125 * cos(2 * 3.14F* sec / 60);
	}
};



