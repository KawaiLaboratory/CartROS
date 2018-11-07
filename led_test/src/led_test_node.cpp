#include "ros/ros.h"
#include "pigpiod_if2.h"
#include "math.h"

#define SHUTDOWN_PIN 29
#define CLUTCH_PIN   31
#define START_PIN    32 
#define SETUP_LED    38
#define DRIVING_LED  40

int pi;
extern int pi;

int main(int argc, char **argv){
  ros::init(argc, argv, "led_test");
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Rate loop_rate(20);

  pi = pigpio_start("localhost", "8888");
  set_mode(pi, SHUTDOWN_PIN, PI_INPUT);
  set_mode(pi, CLUTCH_PIN, PI_INPUT);
  set_mode(pi, START_PIN, PI_INPUT);
  set_mode(pi, SETUP_LED, PI_OUTPUT);
  set_mode(pi, DRIVING_LED, PI_OUTPUT);

  gpioSetPullUpDown(SHUTDOWN_PIN, PI_PUD_UP);
  gpioSetPullUpDown(CLUTCH_PIN, PI_PUD_UP);
  gpioSetPullUpDown(START_PIN, PI_PUD_UP);
  gpioSetPullUpDown(SETUP_LED, PI_PUD_DOWN);
  gpioSetPullUpDown(DRIVING_LED, PI_PUD_DOWN);

  printf("GPIO%d is level %d", SHUTDOWN_PIN, gpioRead(SHUTDOWN_PIN));
  printf("GPIO%d is level %d", CLUTCH_PIN, gpioRead(CLUTCH_PIN));
  printf("GPIO%d is level %d", START_PIN, gpioRead(START_PIN));
}
