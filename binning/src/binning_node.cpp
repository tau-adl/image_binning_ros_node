#include <ros/ros.h>
#include <opencv2/core/core.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/imgproc.hpp>
using namespace std;

class image_resizer
{
public:  
  image_resizer()
  {
    image_transport::ImageTransport it(nh);
    pub = it.advertise("/camera/image_raw", 1);
    sub = it.subscribe("/camera_decompressed/image_raw", 1, &image_resizer::grab_image, this);

    cout << "Image Binner Constructed" << endl;
  }

  void grab_image(const sensor_msgs::ImageConstPtr& msg)
  {
      // Copy the ros image message to cv::Mat.
      cv_bridge::CvImageConstPtr cv_ptr;
      cv::Mat resized_image;
      try
      {
        cv_ptr = cv_bridge::toCvShare(msg);
        cv::resize(cv_ptr->image, resized_image, resized_image.size(), 0.5, 0.5, cv::INTER_AREA);
          
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", resized_image).toImageMsg();
        
        msg->header.stamp = cv_ptr->header.stamp;
        pub.publish(msg);
      }
      catch (cv_bridge::Exception& e)
      {
          ROS_ERROR("cv_bridge exception: %s", e.what());
          return;
      }

  }
private:
  ros::NodeHandle nh; 
  image_transport::Publisher pub;
  image_transport::Subscriber sub;
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "binning");
    image_resizer image_resizer_inst;   
   	ros::spin();
    // Stop all threads
    ros::shutdown();
    return 0;
}
