#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef ROS
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <sensor_msgs/msg/joy.hpp>
#endif

QObject *rootObject;
QObject *qmlObject;
#ifdef ROS
class Listener : public rclcpp::Node
{
public:
  explicit Listener(const std::string & topic_name)
    : Node("listener")
  {
    // chatterトピックのコールバック関数
    auto callback =
      [this](const std_msgs::msg::String::UniquePtr msg) -> void
    //[this](const sensor_msgs::msg::Joy::UniquePtr msg) -> void
      {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
	qmlObject->setProperty("text", msg->data.c_str());
	//RCLCPP_INFO(this->get_logger(), "%lf", msg->axes[1]);
	//qmlObject->setProperty("text", msg->axes[1]);
	QCoreApplication::processEvents();
      };

    // chatterトピックの受信設定
    rclcpp::QoS qos(rclcpp::KeepLast(10));
    sub_ = create_subscription<std_msgs::msg::String>(topic_name, qos, callback);
    //sub_ = create_subscription<sensor_msgs::msg::Joy>(topic_name, qos, callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  //rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
};
#endif

int main(int argc, char *argv[])
{

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  rootObject = engine.rootObjects().first();
  qmlObject = rootObject->findChild<QObject*>("textObject");

  
#ifdef ROS
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;
  auto node = std::make_shared<Listener>("chatter");
  // auto node = std::make_shared<Listener>("joy");
  exec.add_node(node);
  exec.spin();
  rclcpp::shutdown();
#else
  return app.exec();
#endif

  return 0;
    
}
