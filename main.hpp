
#ifndef PROGRAM_MAIN_H
#define PROGRAM_MAIN_H

//1km=1.4
//1mile=2.3
//1浬=2.6
//3.6dot=1km

#define N 25 //飛行機の数

#define VelocityAcceMax -1.3
#define DropAcceMax -10.66    //400m毎分=8.33m/s
#define territorySide 2.9438  //[dot]
#define territoryFrotBehind 100000 //[s]
#define territoryHeight 304.8     //[m]
#define maxDirection() (M_PI/180)

void JudgeState();

#endif //PROGRAM_MAIN_H
