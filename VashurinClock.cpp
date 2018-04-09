//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VashurinClock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClock *FormClock;

//Инициализируем классы для расчета размеров стрелок минут, часов, секунд
PointHou cl = PointHou();
PointMin  pm = PointMin();
PointSec  ps = PointSec();

void line(int x0, int y0,int x1, int y1, TColor color)
{
   FormClock->ImageClock->Canvas->Pen->Color = color;
   FormClock->ImageClock->Canvas->Pen->Style = psSolid;
   FormClock->ImageClock->Canvas->MoveTo(x0,y0);
   FormClock->ImageClock->Canvas->LineTo(x1,y1);
   FormClock->ImageClock->Canvas->MoveTo(x0+1,y0+1);
   FormClock->ImageClock->Canvas->LineTo(x1+1,y1+1);
   FormClock->ImageClock->Canvas->MoveTo(x0-1,y0-1);
   FormClock->ImageClock->Canvas->LineTo(x1-1,y1-1);
}

//---------------------------------------------------------------------------
__fastcall TFormClock::TFormClock(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormClock::FormCreate(TObject *Sender)
{
   ImageClock->Width=ClockSize;
   ImageClock->Height=ClockSize;
   Image1->Width=ClockSize;
   Image1->Height=ClockSize;
   ImageClock->Stretch=True ;
   Image1->Stretch=True;
   ImageClock->Proportional=false;
   Image1->Proportional=false;
   FormClock->ClientWidth=ClockSize;
   FormClock->ClientHeight=ClockSize;
   FormClock->TransparentColor=clWhite;
   FormClock->AlphaBlend=true;
   FormClock->AlphaBlendValue=200;
   Timer1->Enabled;
   Timer1->Interval = 1000;
}

//---------------------------------------------------------------------------

void __fastcall TFormClock::OnTimerEvent(TObject *Sender)
{
	  FormClock->ImageClock->Refresh();
	  //Вытираем прозрачную область рисования стрелок
	  FormClock->ImageClock->Canvas->FillRect(Rect(0,0,337,337));

	  //считываем системное время
	  cl.get_time();

	  //Рисуем стрелки:
	  line (ClockSize/2, ClockSize/2, cl.get_X(), cl.get_Y(), clBlue );
	  pm.get_time();
	  line (ClockSize/2, ClockSize/2, pm.get_X(), pm.get_Y(), clRed );
	  ps.get_time();
	  line (ClockSize/2, ClockSize/2, ps.get_X(), ps.get_Y(), clGreen );

}
//---------------------------------------------------------------------------


