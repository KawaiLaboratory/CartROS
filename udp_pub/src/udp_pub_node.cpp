//for LRF
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
//for UDP
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
//for CSV
#include "fstream"

// double l = 0.0;     //得られた最近点までの距離[m]
// double theta = 0.0; //得られた最近点の角度[rad]
int cnt = 0;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  // int count = scan->scan_time / scan->time_increment;
  // l = 0.0;
  // theta = 0.0;
  // for(int i = 0; i < count; i++) {
  //   float rad = fmodf(scan->angle_min + PHASE_DIFF + scan->angle_increment * i, 2*M_PI);
  //   float degree = RAD2DEG(rad);
  //   if(90.0 < degree  && degree < 270.0){
  //     if(i == 0 || l > scan->ranges[i]){
  //       l = scan->ranges[i];
  //       theta = rad;
  //     }
  //   }
  // }
  double l = 0.0;     //得られた最近点までの距離[m]
  double theta = 0.0; //得られた最近点の角度[rad]
  ros::Time now = ros::Time::now();
  std::ofstream fs(std::to_string(now.toSec())+".csv");  // CSVファイル生成
  fs << "l, theta" << std::endl;

  int count = scan->scan_time / scan->time_increment;
  for(int i = 0; i < count; i++) {
    l = scan->ranges[i];
    theta = scan->angle_min + scan->angle_increment * i;

    if(theta > scan->angle_max){
      break;
    }else{
      fs << l << "," << theta << std::endl;
    }
  }
  fs.close();
  cnt += 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "udp_pub");
  ros::NodeHandle n;
  ros::Subscriber sub;
  ros::Rate loop_rate(1);
  ros::Rate sleep_rate(0.1);
  // int sock;
  // struct sockaddr_in addr;

  // sock = socket(AF_INET, SOCK_DGRAM, 0);

  // addr.sin_family = AF_INET;
  // addr.sin_port = htons(12345);
  // addr.sin_addr.s_addr = inet_addr("169.254.188.8"); //to white raspi

  // char l_char[1023];
  // char theta_char[1023];
  // char buf[2048];

  sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);

  sleep_rate.sleep();

  while(cnt < 60){

    loop_rate.sleep();
    ros::spinOnce();

    // snprintf(l_char, 1023, "%f", l);
    // snprintf(theta_char, 1023, "%f", theta);
    // snprintf(buf, 2048, "%s,%s", l_char, theta_char);

    // sendto(sock, buf, 2048, 0, (struct sockaddr *)&addr, sizeof(addr));
    // close(sock);
  }

 return 0;
}
