//
// Created by 西山大輝 on 2018/12/12.
//

#ifndef PROGRAM_MAIN_H
#define PROGRAM_MAIN_H

#define DestinationX 213    //RJTTのx座標
#define DestinationY 110    //RJTTのy座標

//1km=1.4
//1mile=2.3
//1浬=2.6

#define N 2 //飛行機の数
#define SetNum 10   //集合の数

#define xMax 452    //座標上のx最大値
#define yMax 283    //座標上のy最大値

#define LandingAngle 114    //単位円(度)
#define VelocityAcceMax -2.3    //-100km毎分^2 = -2.3dot/s^2
#define DropAcceMax -6.66    //400m毎分=8.33m/s
#define territorySide 20.8  //[m]
#define territoryFrotBehind 600 //[s]
#define territoryHeight 304.8     //[m]
#define maxDirection() (M_PI/180)

#endif //PROGRAM_MAIN_H
