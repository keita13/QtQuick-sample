#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static const std::string OPENCV_WINDOW = "Image window";
using namespace std::chrono_literals;


class Listener : public rclcpp::Node
{
public:
  explicit Listener(const std::string & topic_name)
  : Node("opencv_sub")
  {
    // chatterトピックのコールバック関数
    auto callback =
    [this](const sensor_msgs::msg::Image::UniquePtr msg) -> void
      {

	cv_bridge::CvImagePtr cv_ptr;
	cv_ptr = cv_bridge::toCvCopy(*msg, sensor_msgs::image_encodings::BGR8);

        cv::Mat display_frame = cv_ptr->image;

	cv::cvtColor(display_frame, g_frame,cv::COLOR_BGR2GRAY);
	cv::Canny(g_frame,edge_frame, 50, 110);

	cv::imshow("OpenCV image receiver cv", cv_ptr->image);

        cv::waitKey(1);

      };
    auto publish_message =
      [this]() -> void{
	auto msg = cv_bridge::CvImage(std_msgs::msg::Header(),sensor_msgs::image_encodings::BGR8, edge_frame).toImageMsg();

	pub_->publish(std::move(msg));
      };
      // chatterトピックの受信設定
    rclcpp::QoS qos1(rclcpp::KeepLast(10));
    rclcpp::QoS qos2(rclcpp::KeepLast(10));
    sub_ = create_subscription<sensor_msgs::msg::Image>(
      topic_name, qos1, callback);
    
    pub_ = create_publisher<sensor_msgs::msg::Image>("edge", qos2);
    timer_ = create_wall_timer(10ms, publish_message);
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
  size_t frame_id_ = 0;
  cv::Mat hsv_image;
  cv::Mat display_frame;
  cv::Mat g_frame;
  cv::Mat edge_frame;
};


int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);

  auto node = std::make_shared<Listener>("camera/color/image_raw");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
