// %Tag(FULL)%
// %Tag(INCLUDE)%
#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Joy.h>
// %EndTag(INCLUDE)%
// %Tag(CLASSDEF)%
class MotorDriver123
{
public:
  MotorDriver123();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int motor1, motor2, motor3;
  double scale_motor1, scale_motor2, scale_motor3;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
}; // %EndTag(CLASSDEF)%

// %Tag(PARAMS)%
MotorDriver123::MotorDriver123():
  motor1(1),
  motor2(2),
  motor3(3)
{

	nh_.param("axis_motor1", motor1, motor1);
	nh_.param("axis_motor2", motor2, motor2);
	nh_.param("axis_motor3", motor3, motor3);

	nh_.param("scale_motor1", scale_motor1, scale_motor1);
	nh_.param("scale_motor2", scale_motor2, scale_motor2);
	nh_.param("scale_motor3", scale_motor3, scale_motor3);
// %EndTag(PARAMS)%

// %Tag(PUB)%
  vel_pub_ = nh_.advertise<std_msgs::Float32MultiArray>("mcWheelVelocityMps", 1000);
// %EndTag(PUB)%
// %Tag(SUB)%
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &MotorDriver123::joyCallback, this);
// %EndTag(SUB)%
}
// %Tag(CALLBACK)%
void MotorDriver123::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

	double vel_motor1, vel_motor2, vel_motor3;
	std_msgs::Float32MultiArray msg;

	vel_motor1 = scale_motor1*joy->axes[motor1];
	vel_motor2 = scale_motor2*joy->axes[motor2];
	vel_motor3 = scale_motor3*joy->axes[motor3];

	msg.data.clear();
	msg.data.push_back(0);
	msg.data.push_back(0);
	msg.data.push_back(0);
	msg.data.push_back(0);
	msg.data.push_back(vel_motor1);
	msg.data.push_back(0);
	msg.data.push_back(vel_motor2);
	msg.data.push_back(vel_motor3);
	msg.data.push_back(0);
	msg.data.push_back(0);

	vel_pub_.publish(msg);

}

// %EndTag(CALLBACK)%
// %Tag(MAIN)%
int main(int argc, char** argv)
	{
  		ros::init(argc, argv, "motor_driver");

  		MotorDriver123 motor_driver;

  		ros::spin();
	}
// %EndTag(MAIN)%
// %EndTag(FULL)%

