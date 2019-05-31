#include <fstream>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

//parameter values for Gingrich and Byrne model in the journal of neurophysiology

// 1)  Fig.2 Simulations of the maintenance of short-term facilitation (STF) of nondepressed synapses
//             Control     ::  total_t=592, ISI =20, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=false, PKA_ON=false, PKC_ON=false  PKC_OnSetTime=430, PKA_OnSetTime=430
//             5-HT        ::  total_t=592, ISI =20, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=false, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=430, PKA_OnSetTime=430
//             5-HT+Met    ::  total_t=592, ISI =20, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=false, PKA_ON=false, PKC_ON=true,  PKC_OnSetTime=430, PKA_OnSetTime=430
//             5-HT+Che    ::  total_t=592, ISI =20, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=false, PKA_ON=true,  PKC_ON=false, PKC_OnSetTime=430, PKA_OnSetTime=430

//2)   Fig. 3. Empirical analysis and simulation of the effects of PKC on STF of depressed synapses
//             5-HT+Met     ::  total_t=452, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=false, PKC_ON=true,  PKC_OnSetTime=290, PKA_OnSetTime=290

//3)   Fig. 4. Dynamics of PKC- and PKA- dependent processes in the maintenance of STF of nondepressed synapse
//             Control     ::  total_t=292, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=false, PKC_ON=false  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT        ::  total_t=292, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT+Met    ::  total_t=292, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=false, PKC_ON=true,  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT+Che    ::  total_t=292, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=true,  PKC_ON=false, PKC_OnSetTime=130, PKA_OnSetTime=130

//4)   Fig. 5. PKC-dependent process enhanced the recovery of the RRP (sucrose modeling:: first time of application of sucrose happen at 150s , second time of applicatoin of sucrose happened at 450s. Note Calcium influx (Ica) was set to 0)
//             Control     ::  total_t=450, ISI =300, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=true, PKA_ON=false, PKC_ON=false  PKC_OnSetTime=390, PKA_OnSetTime=390
//             5-HT        ::  total_t=450, ISI =300, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=true, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=390, PKA_OnSetTime=390
//             5-HT+Che    ::  total_t=292, ISI =300, Time_FirstSpike=150, Time_SencondSpike=450, sucrose=true, PKA_ON=true,  PKC_ON=false, PKC_OnSetTime=390, PKA_OnSetTime=390

//5)   Fig. 6. Contribution of PKC-dependent processes to the maintenance of STF was dependent on stimulus frequency. ( Fig. 6   recalibration of model : Kr=4.266 )
//             Control     ::  total_t=172, ISI =50, Time_FirstSpike=150, Time_SencondSpike=(151 (ISIs=1s at the paper); 155(ISIs=5s ISIs=5s at the paper); 10s(ISIs=10s); 20s(ISIs=20s)), sucrose=false, PKA_ON=false, PKC_ON=false  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT        ::  total_t=172, ISI =50, Time_FirstSpike=150, Time_SencondSpike=(151 (ISIs=1s at the paper); 155(ISIs=5s ISIs=5s at the paper); 10s(ISIs=10s); 20s(ISIs=20s)), sucrose=false, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT+Met    ::  total_t=172, ISI =50, Time_FirstSpike=150, Time_SencondSpike=(151 (ISIs=1s at the paper); 155(ISIs=5s ISIs=5s at the paper); 10s(ISIs=10s); 20s(ISIs=20s)), sucrose=false, PKA_ON=false, PKC_ON=true,  PKC_OnSetTime=130, PKA_OnSetTime=130
//             5-HT+Che    ::  total_t=172, ISI =50, Time_FirstSpike=150, Time_SencondSpike=(151 (ISIs=1s at the paper); 155(ISIs=5s ISIs=5s at the paper); 10s(ISIs=10s); 20s(ISIs=20s)), sucrose=false, PKA_ON=true,  PKC_ON=false, PKC_OnSetTime=130, PKA_OnSetTime=130

//6)   Fig. 7.  5-HT-induced STF of depressed synapses was dependent on the stimulus frequency  
//             5-HT (ISI=1s)   ::  total_t=199.5, ISI =1, Time_FirstSpike=150, Time_SencondSpike=151, sucrose=false, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=169, PKA_OnSetTime=169
//             5-HT (ISI=20s)  ::  total_t=1132, ISI =20, Time_FirstSpike=150, Time_SencondSpike=170, sucrose=false, PKA_ON=true,  PKC_ON=true,  PKC_OnSetTime=530, PKA_OnSetTime=530
//orignal G-B model (1985)

/*double total_t=1250.5; // total time (seconds)

double ISI=100; // ITI=interspike interval (seconds)

double Time_FirstSpike=150; // Timing of first spike (EPSP0)
double Time_SecondSpike=250; // Timing of Second spike (EPSP1)
*/

/*double total_t=592; // total time (seconds)

double ISI=20; // ITI=interspike interval (seconds)

double Time_FirstSpike=150; // Timing of first spike (EPSP0)
double Time_SecondSpike=450; // Timing of Second spike (EPSP1)
*/

/*double total_t=530.5; // total time (seconds)

double ISI=20; // ITI=interspike interval (seconds)

double Time_FirstSpike=150; // Timing of first spike (EPSP0)
double Time_SecondSpike=170; // Timing of Second spike (EPSP1)
*/

 /*double Time_FirstSpike = 150;
 double Time_SecondSpike = 151;
 double ISI = 1;
 double total_t = 169.5;
 */

double total_t=292; // total time (seconds)

double ISI=20; // ITI=interspike interval (seconds)

double Time_FirstSpike=150; // Timing of first spike (EPSP0)
double Time_SecondSpike=170; // Timing of Second spike (EPSP1)


bool Sucrose=false;   //timing of first applicatoin of sucrose 150:  Time_FirstSpike=150;    timing of 2nd applicatoin of sucrose 450: ISI=300;  PKC_OnSetTime=390;PKA_OnSetTime=390;

bool PKC_ON=false;
bool PKA_ON=true;
//double PKC_OnSetTime=290;

double PKC_OnSetTime=130;
double PKA_OnSetTime=130;

double spikeWidth=0.0;    // spikeWidth= 0
double spikeWidth1=0.003;  //spikeWidth before 5HT induced activation of PKA
//double spikeWidth2=0.009;   //spikeWidth after 5HT induced activation of PKA
double spikeWidth2=0.0044;   //spikeWidth after 5HT induced activation of PKA 5 parameters
//double spikeWidth2=0.0073;   //spikeWidth after 5HT induced activation of PKA



double ti[100]={0};
double Release[100]={0}, Replenishment[100]={0};



double Mins=0.002, Mins1=150,Mins2=0.0;

//paramenter of Ca regulation in the G-B model
static double Kc=103.0;
static double Ta=0.001;
static double Ti=0.44;
static double Tr=15.6;

static double Ku=2907.0; //(orignal value from G-B model)
//static double Ku=407.0;  //new value 

//static double Ku=599.9713;  //new value 11 parameters 

static double Mu=28.107;  // Mu^2=709 (format different)
static double Kd=0.338;

static double Vc=2.15; //(orignal value from G-B model)
//static double Vc=0.22; //new value

//static double Vc=0.2142; //new value 11 parameters

//parameters for vesicle storage and release in the G-B model
//static double Vr=1.0; //(orignal value from G-B model)

static double Vr=1.0134;  // new value from PSO 5 parameters

//static double Kr=3.16; (orignal value from G-B model)
static double Kr=2.266; //new value from PSO 5 paramerters
//static double Kr=3.6235; //new value from PSO 11 parameters

static double Kvd=0.001; //(orignal value from G-B model)
//static double Kvd=0.003; //new value
//static double Kvd=0.0077; //new value 11 parameters

//static double Kf=21.0;  //(orignal value from G-B model)
//static double Kf=148.0;  //new value
static double Kf=34.7732; //new value from PSO 5 paramters
//static double Kf=198.7943; //new value from PSO

static double Mf=0.0008;  //(orignal value from G-B model)
//static double Mf=0.008;  //new value
//static double Mf=0.0008;  //new value 11 paramters

//static double Nf=2.83; //(orignal value from G-B model)
static double Nf=3.7970;  //new value from PSO 5 parameters
//static double Nf=24.1374;  //new value from PSO 11 paramters

static double Ks=35.0;
static double Ms=0.2276; // format issue
static double Ns=1.75;

static double Ts=213.0; //(orignal value from G-B model)
//static double Ts=3400.0; //new value
//static double Ts=340.0; //new value 11 parameters

//static double Vf=6.08; (orignal value from G-B model)
//static double Vf=3.04; //new value
static double Vf=2.4397; //new value from PSO 5 parameters
//static double Vf=2.4898; //new value from PSO 11 parameters

static double Kn=0.005;// (orignal value from G-B model)
//static double Kn=0.015; //new value





//initial conditions
double Ai,Ica, Iu, Id, If, Is, Ivd, In, Ir;
static double Ci=1.0;
static double Bi=1.0;

//static double Cf1=100.0;
static double Cf1=100.0;


double Cc=0.0;
double PVM=0.0;
double Cf=100.0;
double Cr=100.0;
double ePsp=0.0;

double y_temp[5]={0.0,0.0,100.0,100.0,0.0};   //y[0]: Ca concentration in the interior department. y[1]:PVM.    y[2]: vesicle concentration in feeding pool. y[3]: vesicle concentration in RRP. y[4]: accumulated vesicle released.
double y[5]={0.0,0.0,100.0,100.0,0.0};

//double spikeWidth=0.003;
//double spikeWidth=0.005;



//paramters for PKC dependent vesicle mobilization


double Ireplenish_temp=0, If_temp=0, Is_temp=0, Cc_temp=0,Cf_temp=0,Cr_temp=0;
double Accumulated_release=0, Accumulated_replenishment=0;

//double Gpkc=6.2;  // maximum contribution of PKC : Gpkc=6.0  
//double Tau1=-4.0, Tau2=-110;

double Gpkc=14.2031;  // maximum contribution of PKC : Gpkc=6.0   from PSO 5 paramters
//double Gpkc=11.784;  // maximum contribution of PKC from PSO 11 parameters


double Tau1=-0.4, Tau2=-67.8612; //5 parameters
//double Tau1=-0.4, Tau2=-78.4570; // 11 parameters

double Scale_Replenish=1;
//double Scale_Replenish=4.2820;

double Ireplenish=0; 
double Replenish=0;


double m_activation=0, h_inactivation=1.0;



int nu=0; // number of spike





double Cai_s(double);  //calcium function





double Diff=0,Diff_euler=0;

long double  t3=0.0001;  // numeric stepsize. t3=0.0001  denote stepsize = 0.1 ms.

double t2=0.1; // output stepsize: t2= 1 denote 1 output data per seconds.



void main()
{
	ofstream ofile("release.txt",ios::out);   //output file :: synaptic release
	ofstream ofile1("If.txt",ios::out);
	ofstream ofile2("supply_rate.txt",ios::out);  //output file::  calcium dynamics and vesicle storage and mobillization
	ofstream ofile3("supply_rate_1.txt",ios::out);
	ofstream ofile4("If_test.txt",ios::out);


	//for ( double i=2000;i<=51000;i=i+ISI)
	//for ( double i=Time_FirstSpike;i<=total_t-1000;i=i+ISI)

	//after PSO fitness
	/*
Ku=452.37;
Vc=0.1879;
Kr=3.4813;
Kvd=0.006;
Kf=274.2275;
Mf=0.0059;
Nf=35.2744;
Ts=3674.93;
Kn=0.0267;
Vf=1.6322;
*/

//	2 fold boundary . fig 1 control and Fig. 7
/*Ku=203.5    	 ;
Vc=0.2968  	;
Kr=3.1164   	;
Kvd=0.006   	;
Kf=177.1591      ;
Mf=0.004  ;
Nf=14.15;
Ts=6800;
Kn=0.0075;
Vf=4.1614 ;
*/

	// 10 fold boundary Fig 1 control and fig. 7
/*Ku=43.6589   	  ;
Vc=0.2870  	;
Kr=3.6251   	;
Kvd=0.0091   	;
Kf=117.7265         ;
Mf=0.0091   ;
Nf=12.6584    ;
Ts=34000   ;
Kn=0.0015   ;
Vf=4.2644 ;
*/

	ti[nu]=Time_FirstSpike;
	cout<<"ti["<<nu<<"]="<<Time_FirstSpike<<endl;
	nu++;

	//for ( double i=Time_SecondSpike;i<=total_t;i=i+ISI)
	for ( double i=Time_SecondSpike;i<=total_t;i=i+ISI) // original G-B model (1985)
	{

		ti[nu]=i;
		cout<<"ti["<<nu<<"]="<<i<<endl;
		nu++;
	}

	//ti[nu]=ti[nu-1]+100;
	//cout<<"ti["<<nu<<"]="<<ti[nu]<<endl;
	//nu++;
	cout<<"nu="<<nu<<endl;

	int ii=0;


	double Cai_spike=0;




	cout<< ti[0]<<endl;
	cout<<nu<<endl;
	ofile<<"Stim.No."<<" "<<"ReleaseNormToEPSP0"<<" "<<"Accumulated_release"<<" "<<"Accumulated_Replenishment"<<" "<<"ReleaseNormToEPSP1"<<endl;
	ofile1<<"t"<<" "<<"Cai"<<" "<<"N"<<" "<<"NF"<<" "<<"Rn"<<" "<<"R"<<" "<<"R+NF+N"<<" "<<"N1"<<" "<<"Rn1"<<" "<<"Pn1"<<endl;
	ofile2<<"t"<<" "<<"Ica"<<" "<<"supply_rate"<<" "<<"If"<<" "<<"Is"<<" "<<"Cc"<<" "<<"Cf"<<" "<<"Cr"<<" "<<"PKC"<<endl;
	ofile3<<"t"<<" "<<"Ica"<<" "<<"supply_rate"<<" "<<"If"<<" "<<"Is"<<" "<<"Cc"<<" "<<"Cf"<<" "<<"Cr"<<" "<<"PKC"<<endl;
	ofile4<<"t"<<" "<<"Ica"<<" "<<"Ireplenish"<<" "<<"If"<<" "<<"Is"<<endl;

	double tt=0;
	for (int i=0;i<100;i++)
	{   
		tt=tt+1;
		//ofile1<<tt<<" "<<0<<" "<<N<<" "<<Rn<<" "<<R<<" "<<Vpre1<<" "<<N1<<" "<<N2<<" "<<N3<<" "<<Rn1<<" "<<Rn2<<endl;
	}

	int Ca_Int=0;

	Mins1=Time_SecondSpike;


	for (long double t=0; t<total_t;t=t+t3)
	{
		if (t>=PKC_OnSetTime && PKC_ON==true)
		{


			m_activation=1.0-exp((t-PKC_OnSetTime)/Tau1);
			h_inactivation=exp((t-PKC_OnSetTime)/Tau2);
			
			Kn=0.015*m_activation*h_inactivation*Gpkc;
		
		}

		if (t>=PKA_OnSetTime && PKA_ON==true)
		{

            
 
			spikeWidth=spikeWidth2;

			Cai_spike=Cai_s(t);

			Ica=Cai_spike;
		}
		else if (t>=PKA_OnSetTime && PKA_ON==false && PKC_ON==true)
		{

			
				spikeWidth=spikeWidth1;
				Cai_spike=Cai_s(t);
				Ica=Cai_spike;
		}
		else
		{
				spikeWidth=spikeWidth1;
							
				Cai_spike=Cai_s(t);
				Ica=Cai_spike;
		}


			
	
	


       if (Sucrose==true )
	   {
		   Ica=0;

		   if ( abs((t-150.0))<t3)
		   {
			   y[3]=0;
			   y_temp[3]=0;
		   }

		  
	   }


		//Ica = Ai * Bi * Kc;
		Iu = Ku / (1.0 + pow(Mu / y_temp[0], 2.0));
		Id = y_temp[0] * Kd;
		If = (y_temp[2] * Kf / Cf1) * (1.0 / (1.0 + Mf / pow(y_temp[0], Nf)));
		Is = y_temp[2] * y_temp[1] / Cf1;
		Ivd = (y_temp[2] - y_temp[3]) * Kvd;

		In = (Cf1 - y_temp[2]) * Kn;
		if (In<=0)
			In=0;


		Ir = (y_temp[3] * Vr) * (Ica * Kr);

		//Is=0;

		//Ireplenish=Scale_Replenish*(If+Is+Ivd)*(1.0-y_temp[3]/100.0)*(1.0+7.9*m_activation*h_inactivation);
		Ireplenish=Scale_Replenish*(If+Is+Ivd)*(1.0-y_temp[3]/100.0)+Gpkc*m_activation*h_inactivation*(1.0-y_temp[3]/100.0);



		// 
		//if (Ireplenish<0)
		//	Ireplenish=0;


		 // sumulating sucrose experiments


		y[0] = y_temp[0]+t3*(Ica - Iu - Id) / Vc;
		y[1] = y_temp[1]+t3*((Ks / (1.0 + pow(Ms / y_temp[0], Ns))) - y_temp[1]) / Ts;
		y[2] = y_temp[2]+t3*(In - Ireplenish) / Vf;
		y[3] = y_temp[3]+t3*(Ireplenish- Ir) / Vr;
		y[4] = y_temp[4]+t3*Ir;

		y_temp[0]=y[0];
		y_temp[1]=y[1];
		y_temp[2]=y[2];
		y_temp[3]=y[3];
		y_temp[4]=y[4];

		Ireplenish_temp=Ireplenish_temp+t3*Ireplenish;
		//Accumulated_replenishment=Accumulated_replenishment+t3*Ireplenish;
		If_temp=If_temp+t3*Scale_Replenish*(If)*(1.0-y_temp[3]/100.0);
		Is_temp=Is_temp+t3*Scale_Replenish*(Is)*(1.0-y_temp[3]/100.0);
		Cc_temp=Cc_temp+t3*y[0];
		Cr_temp=Cr_temp+t3*y[3];
		Cf_temp=Cf_temp+t3*y[2];


		if (t>=149 && t<170)
			Replenish=Replenish+t3*Ireplenish;
      

		if (t>Time_FirstSpike+spikeWidth)
		{
			cout<<endl;
			cout<<"t="<<t<<"                "<<"y[0]="<<y[0]<<endl;
			cout<<"t="<<t<<"                "<<"y[1]="<<y[1]<<endl;
			cout<<"t="<<t<<"                "<<"y[2]="<<y[2]<<endl;
			cout<<"t="<<t<<"                "<<"y[3]="<<y[3]<<endl;
			cout<<"t="<<t<<"                "<<"y[4]="<<y[4]<<endl;
	   // ofile3<<t<<" "<<Ireplenish<<endl;
		//ofile4<<t/1000.0<<" "<<Cai<<" "<<N<<" "<<NF<<" "<<Rn<<" "<<b1<<" "<<Pn1<<" "<<PnF<<" "<<R<<" "<<R+NF+N<<endl;
		Time_FirstSpike=Time_FirstSpike+ISI;
		}

		//if (t>Mins)

		
		if (t>Mins)
		{
			
	    ofile3<<t<<" "<<Ica<<" "<<Ireplenish<<" "<<Scale_Replenish*(If)*(1.0-y_temp[3]/100.0)<<" "<<Scale_Replenish*(Is)*(1.0-y_temp[3]/100.0)<<" "<<y[0]<<" "<<y[2]<<" "<<y[3]<<" "<<Gpkc*m_activation*h_inactivation<<endl;
		//ofile4<<t/1000.0<<" "<<Cai<<" "<<N<<" "<<NF<<" "<<Rn<<" "<<b1<<" "<<Pn1<<" "<<PnF<<" "<<R<<" "<<R+NF+N<<endl;
		Mins=Mins+0.01;
		}
        
		if (t>Mins2 )
		{
			if (t<1.0)
			{
				Mins2=Mins2+t2;
			}
			else
			{
			
				ofile2<<t<<" "<<Ica<<" "<<Ireplenish_temp/t2<<" "<<If_temp/t2<<" "<<Is_temp/t2<<" "<<Cc_temp/t2<<" "<<Cf_temp/t2<<" "<<Cr_temp/t2<<" "<<Gpkc*m_activation*h_inactivation<<endl;
				//ofile4<<t/1000.0<<" "<<Cai<<" "<<N<<" "<<NF<<" "<<Rn<<" "<<b1<<" "<<Pn1<<" "<<PnF<<" "<<R<<" "<<R+NF+N<<endl;
				Mins2=Mins2+t2;
				Ireplenish_temp=0;
				If_temp=0;
				Is_temp=0;
				Cc_temp=0;
				Cf_temp=0;
				Cr_temp=0;
			}
		
		}
        
        
		
		

        if (t>Mins1 && t<Mins1+0.3)
		{
			
	   // ofile4<<t<<" "<<Scale_Replenish*(If)*(1.0-y_temp[3]/100.0)<<" "<<y_temp[2] * Kf / Cf1<<" "<<(1.0 / (1.0 + Mf / pow(y_temp[0], Nf)))<<" "<<(1.0-y_temp[3]/100.0)<<endl;
		ofile4<<t<<" "<<Ica<<" "<<Ireplenish<<" "<<If<<" "<<Is<<endl;
		//Mins1=Mins1+0.01;
		}

			
		for (int i=0;i<nu;i++)
		{
	
			if ((t-ti[i])>=0 && (t-ti[i])<=spikeWidth)
			{
				Release[i]=Release[i]+(y[3] * Vr) * (Ica * Kr)*t3;
			}
			if ((t-ti[i])>=0 && (t-ti[i])<=ISI)
			{
				Replenishment[i]=Replenishment[i]+Ireplenish*t3;
			}
			
		}

		if(Sucrose==true && t-150.0<-0.0001 && t-150.0> -0.0002)
		  cout<<"# of RRP before  1st surcose application"<<"     "<<"t="<<t<<"    "<<"y[3]="<<y[3]<<endl;

		if(Sucrose==true && t-300.0<0.0 && t-300.0> -0.0001 )
		  cout<<"# of RRP after  1st surcose application"<<"     "<<"t="<<t<<"    "<<"y[3]="<<y[3]<<endl;

		if(Sucrose==true && t-450.0<=0.0001 && t-450.0> 0 )
		  cout<<"# of RRP before  2nd surcose application"<<"    "<<"t="<<t<<"    "<<"y[3]="<<y[3]<<endl;



	

	
	}
	
	for (int i=0;i<nu;i++)
	{
	            
		        if (Release[0]!=0)
				{
		        

					for (int j=0; j<=i;j++)
					{
						Accumulated_release=Accumulated_release+Release[j];
						Accumulated_replenishment=Accumulated_replenishment+Replenishment[j];
					}
					cout<<"Release["<<i<<"]="<<Release[i]/Release[0]*100.0<<endl;
					cout<<"Accumulated_release="<<Accumulated_release<<endl;
					cout<<"Replenishment["<<i<<"]="<<Replenishment[i]<<endl;
					cout<<"Accumulated_replenishment="<<Accumulated_replenishment<<endl;
					ofile<<i+1<<" "<<Release[i]/Release[0]<<" "<<Accumulated_release<<" "<<Accumulated_replenishment<<" "<<Release[i]/Release[1]<<endl;
					Accumulated_release=0;
					Accumulated_replenishment=0;
				}
			
	}
	
     

	  cout<<endl;
	  cout<<endl;

	  cout<<"Release["<<"0"<<"]="<<Release[0]<<endl;
	  cout<<"Release[0]/43.0029="<<Release[0]/43.0029<<endl;
	  cout<<"Release[1]/Release[0]="<<Release[1]/Release[0]<<endl;
	  cout<<"Replenished Vesicle between 1st and 2nd stimulus"<<endl;
	  cout<<"Replenished="<<Replenish<<endl;
	  cout<<"Replenished/43.0029="<<Replenish/43.0029<<endl;
	 // string s;
     // cin >> s;
	//  cout<< s;

	  system("pause");



	double temp_If=0;
    for (double x=0;x<100;x=x+0.1)
	{   
        for (double y=0;y<100;y=y+0.1)
		{
			
			//ofile1<<x<<" "<<1.0 / (1.0 + 0.008 / pow(1.2, x))-(1.0 / (1.0 + 0.008 / pow(0.8, x)))<<endl;
		}
		
	}




	//ofile1<<endl;
    



}




double Cai_s(double t)
{

	double temp=0;

	

	for (int i=0;i<nu;i++)
	{	

		double x=t-ti[i];
		if (x>=0 && x<=spikeWidth)
		{
			Ai = 1.0 - exp(-x / Ta);
			Bi = Ci * exp(-x / Ti);
			break;
		}
		else
		{
			Ai = 0.0;
			//Ci = 1.0 - (1.0 - Bi) * exp(-(x - spikeWidth) / Tr);
		}
	}
		
	temp=Ai * Bi * Kc;

	return temp;
	}

