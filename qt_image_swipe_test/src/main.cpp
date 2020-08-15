#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "video_provider.h"
#include "image_receiver.h"

#ifdef ROS
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <sensor_msgs/msg/image.hpp>
#endif

QObject *rootObject;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
 // Connect to VideoCapture
    VideoProvider* videoProvider = new VideoProvider();
    engine.addImageProvider(QLatin1String("VideoCapture"), videoProvider);

    // Image Receiver
    ImageReceiver imageReceiver;

    // Connect ImageReceiver to VideoProvider
    QObject::connect(&imageReceiver, SIGNAL(OnReceiveImage(QImage)), videoProvider, SLOT(OnReceiveImage(QImage)));
    
    
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

#ifdef ROS
    // Initialize ROS
    // Create subscriber node
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
    rclcpp::executors::SingleThreadedExecutor exec;
    auto node = rclcpp::Node::make_shared("qt_subscriber");
    //auto serial = std::make_shared<Listener>("serial");
    //auto node = std::make_shared<Listener>("/camera/color/image_raw",&imageReceiver);

    // Subscription
    auto cb_group = node->create_callback_group(rclcpp::callback_group::CallbackGroupType::MutuallyExclusive);
    ///camera/color/image_raw
    auto sub = node->create_subscription<sensor_msgs::msg::Image>("/edge",std::bind(&ImageReceiver::imageCallback, &imageReceiver, std::placeholders::_1),rmw_qos_profile_sensor_data,cb_group);
     
    exec.add_node(node);
    //exec.add_node(serial);
    exec.spin();
    rclcpp::shutdown();
#else
    return app.exec();
#endif

}
