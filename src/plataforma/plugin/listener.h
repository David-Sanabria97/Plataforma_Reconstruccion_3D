#ifndef LISTENER
#define  LISTENER

#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include <thread>
#include "rotacion_plataforma.h"

namespace gazebo{
    class RotacionPlataforma;
    class Listener{
        private:
              /* creacion de nodo, publicador, subscriptor*/
              std::unique_ptr<ros::NodeHandle> nodo;
              ros::Subscriber subscriber;
              ros::Publisher publisher;
              ros::CallbackQueue cola;
              ros::CallbackQueue cola2;
              std::thread threadColas;
              RotacionPlataforma * plataforma;

        public:
            void init(RotacionPlataforma *);
            void listener(const std_msgs::String::ConstPtr& msg);
            /* cuando alguien se suscribe*/
            static void conexion(const ros::SingleSubscriberPublisher&);
            static void desconexion(const ros::SingleSubscriberPublisher&);
            void thread();

    };

}
#endif
