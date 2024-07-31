#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SNAKEBEGINSIZE 4
#define SNAKEPARTSSIZE 25
#define FIELDWIDTH 10
#define FIELDHEIGTH 20
#define STARTSPEED 300
#define SPEEDADDITION 20
#define START 1
#define PAUSE 0
enum NcursesKeys {
  NLeft = 0404,
  NUp = 0403,
  NDown = 0402,
  NRight = 0405,
  NStartKey = 53,
  NPauseKey = 50,
  NTerminateKey = 27,
};
enum QtKeys {
  QtLeft = 16777234,
  QtUp = 16777235,
  QtDown = 16777237,
  QtRight = 16777236,
  QtStartKey = 83,
  QtPauseKey = 80,
  QtTerminateKey = 16777216,
  QtSpeedUp = 65,
};
#endif  // CONSTANTS_H
