//libraries
#include "math.h"

//application

//controller
#include "layer_controller/mini_md.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
#define pi 3.14159265358979





int main(void)
{
	float L1=0;
	float L2=0;
	float L3=0;
	float L=115.0;
	float x1=0;
	float y1=0;
	float x2=0;
	float y2=0;
	float x3=0;
	float y3=0;
	float lx=0;
	float ly=0;
	float r1=0;
	float r2=0;
	float r3=0;
	float lr;
	float R=0;
	float lR=0;
	float X=0;
	float tx=0;
	float ty=0;
	float dis;
	float ang;
	float o1;
	float o2;
	float o3;
	float sdf;
	float x;
	float y;
	float w1=0;
	float w2=0;
	float w3=0;
	float xp=0;
	float yp=0;
	float jp=0;
	float fp=0;
	float xy=0;
	float d=0;
	float dr=0;
	float wr=0;
	float po=0;

	CW0 cw0;
	CCW0 ccw0;
	Pwm0 pwm0;
	CW1 cw1;
	CCW1 ccw1;
	Pwm1 pwm1;
	CW2 cw2;
	CCW2 ccw2;
	Pwm2 pwm2;
	Enc0 enc0;
	Enc1 enc1;
	Enc2 enc2;
	enc1.setup();
	enc1.count();
	enc2.setup();
	enc2.count();
	enc0.setup();
	enc0.count();
	Serial0 siri;
	siri.setup(115200);
	MiniMD motor0(cw0,ccw0,pwm0);
	motor0.setup();

	MiniMD motor1(cw1,ccw1,pwm1);
	motor1.setup();

	MiniMD motor2(cw2,ccw2,pwm2);
	motor2.setup();

	x=500*cosf(M_PI/6);
	y=500*sinf(M_PI/6);
	po=atanf(y/x);
	if(x==0){
			po=M_PI/2;
		}
	if(x<0){
		po=po+M_PI;
	}


	xy=hypotf(x,y);

    while(1){

    		yp=y-ty;
    		xp=x-tx;

	        jp=xy-X;//Œ»Ý‚Ì‹——£‚Ì•Î·


	        //siri.printf("Ang%f",d);

	        o1=(yp*1050)+((jp-fp)*100);
	        o2=(((sinf(-2*M_PI/3)*yp)+(cosf(-2*M_PI/3)*xp))*980)+((jp-fp)*100);
	        o3=(((sinf(11*M_PI/6)*yp)+(cosf(11*M_PI/6)*xp))*1070)+((jp-fp)*100);

	        sdf=fabsf(o1);
	        if(sdf<fabsf(o2)){
	            sdf=fabsf(o2);
	        }
	        if(sdf<fabsf(o3)){
	            sdf=fabsf(o3);
	        }
	        if(sdf!=0){
	        w1=o1/sdf;
	        w2=o2/sdf;
	        w3=o3/sdf;
	        }
	        else {
				w1=0;
				w2=0;
				w3=0;
			}
	        /*w1=0;
	        w2=-1;
	        w3=1;*/


	        //siri.printf("rt%f,%f,%f\n\r",w1,w2,w3);
	        motor0.duty(w1);
			motor0.cycle();
			motor1.duty(w3);
			motor1.cycle();
			motor2.duty(w2);
			motor2.cycle();




	        L=90;
	        L1=enc2.count()/200*40*M_PI;
	        L2=enc1.count()/200*40*M_PI;
	        L3=enc0.count()/200*40*M_PI;
	        siri.printf("0%f  1%f  2%f\n\r",L1,L2,L3);


	        lr=(L1+L2+L3)/3/L;
	        //printf("new%.2f\n",lr*180/M_PI);
	        wr=dr-lr;
	        dr=lr;

		    x1=-tanf(pi/6)*(L3+L2/sinf(pi/6));
		    y1=L3;
		    //printf("x1 %f      y1 %f \n",x1,y1);
		    x2=tanf(pi/6)*(L3+L1/sinf(pi/6));
		    y2=L3;
		    //printf("x2 %f      y2 %f \n",x2,y2);
		    x3=tanf(pi/6)*(L1-L2)/(2*sinf(pi/6));
		    y3=(-L1-L2)/(2*sinf(pi/6));
		    //printf("x3 %f      y3 %f \n",x3,y3);

	        lx=-(x1+x2+x3)/3;
	        ly=-(y1+y2+y3)/3;

	        X=hypotf(lx,ly);
	         siri.printf("JKIT dis %f\n\r",X);
	         siri.printf("x%f,y%f\n\r",lx,ly);

	        tx=X*cosf(po);
	        ty=X*sinf(po);
	        //siri.printf("x%f,y%f \n",tx,ty);
	        fp=jp;//‰ß‹Ž‚Ì•Î·
	        //siri.printf("%d,%d,%d\n",enc1.count(),enc2.count(),enc3.count());
	        wait(50.0);


	    }








	return 0;
}
