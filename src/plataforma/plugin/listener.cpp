#include "listener.h"

#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include <gazebo/gazebo.hh>
#include "comandos.h"

namespace gazebo{
  void Listener::init(RotacionPlataforma * plataforma){

      this->plataforma = plataforma;

    if(!ros::isInitialized()){
      int argc=0;
      char **argv=NULL;
      ros::init(argc,argv,"gazebo_client", ros::init_options::NoSigintHandler);
    }
    /* crear Nodo*/
    this->nodo.reset(new ros::NodeHandle("gazebo_clinet"));
    /* Crear subscriptor*/
    ros::SubscribeOptions so=ros::SubscribeOptions::create<std_msgs::String>(
        "/RotacionPlataforma",
        1,
        boost::bind(&Listener::listener,this,_1),
        ros::VoidPtr(),
        &this->cola
        );
    this->subscriber=this->nodo->subscribe(so);

    ros::AdvertiseOptions ad=ros::AdvertiseOptions::create<std_msgs::String>(
          "/RotacionPlataforma_msj",
          1,
          &this-> conexion,
          &this-> desconexion,
          ros::VoidPtr(),
          &this->cola2
          );
    this->publisher=this->nodo->advertise(ad);

    this->threadColas=std::thread(std::bind(&Listener::thread, this));
  }
  void Listener::listener(const std_msgs::String::ConstPtr& msg){
    std::string m=msg->data.c_str();
	//	Comandos::ruta="";
		Comandos::procesar(m, this->plataforma);
  }
  void Listener::conexion(const ros::SingleSubscriberPublisher&){
    ROS_INFO("Me conecto");

  }
  void Listener::desconexion(const ros::SingleSubscriberPublisher&){
    ROS_INFO("Me desconecto");

  }
  void Listener::thread(){
    static const double timeout=0.01;
    while(this->nodo->ok()){
      this->cola.callAvailable(ros::WallDuration(timeout));
      std_msgs::String m;
      std::stringstream  ms;

      ms<<this->plataforma->getEstado();
      m.data=ms.str();

      this->publisher.publish(m);


    }
  }

}
