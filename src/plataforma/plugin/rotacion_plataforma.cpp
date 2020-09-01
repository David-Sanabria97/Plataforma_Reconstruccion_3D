#ifndef PLATAFORMA
#define PLATAFORMA

#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include "rotacion_plataforma.h"
#include "listener.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "comandos.h"

namespace gazebo
{
    class RotacionPlataforma: public ModelPlugin{

      private: physics::JointPtr joint;
      private: common::PID pid;
      physics::ModelPtr modelo;
      std::stringstream  ms;

      /// A node use for ROS transport
      private: std::unique_ptr<ros::NodeHandle> rosNode;
      /// ROS subscriber
      private: ros::Subscriber rosSub;
      private: ros::Publisher  rosPub;
      ///  A ROS callbackqueue that helps process messages
      private: ros::CallbackQueue rosQueue;
      private: ros::CallbackQueue rosQueue2;
      /// A thread the keeps running the rosQueue
      private: std::thread rosQueueThread;

      public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf){
        if (_model->GetJointCount() == 0)  {
          std::cerr << "Invalid joint count, Velodyne plugin not loaded\n";
          return;
        }

        this->modelo=_model;
        this->joint=modelo->GetJoints()[1];
        this->pid = common::PID(1,1,1.5);
        gzdbg<<"Bienvenidos a la Plataforma de Recontruccion \r\n";
        gzdbg <<  this->joint->GetName() + "   \r\n";

        this->modelo->GetJointController()->SetPositionPID(this->joint->GetScopedName(), this->pid);
        double position = 0;
        this->SetPosition(position);
        this->ms<<position;
        this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
        // Create a named topic, and subscribe to it.
        ros::SubscribeOptions so =ros::SubscribeOptions::create<std_msgs::Float32>(
              "/RotacionPlataforma",
              1,
              boost::bind(&RotacionPlataforma::OnRosMsg, this, _1),
              ros::VoidPtr(),
              &this->rosQueue
              );
        this->rosSub = this->rosNode->subscribe(so);

        ros::AdvertiseOptions ad=ros::AdvertiseOptions::create<std_msgs::String>(
              "/RotacionPlataforma_PUB",
              1,
              &this-> conexion,
              &this-> desconexion,
              ros::VoidPtr(),
              &this->rosQueue2
              );
        this->rosPub=this->rosNode->advertise(ad);
        // Spin up the queue helper thread.
        this->rosQueueThread =std::thread(std::bind(&RotacionPlataforma::QueueThread, this));
    }

    static void desconexion(const ros::SingleSubscriberPublisher&){
      ROS_INFO("Me desconecto");

    }
    public: void SetPosition(const double &_position){
      this->modelo->GetJointController()->SetPositionTarget(this->joint->GetScopedName(), _position);
      this->ms<<_position;
      this->ms<<0;

    }
    static void conexion(const ros::SingleSubscriberPublisher&){
      ROS_INFO("Me conecto");

    }
    public: void OnRosMsg(const std_msgs::Float32ConstPtr &_msg){
      this->SetPosition(_msg->data);
    }
    /// \brief ROS helper function that processes messages
    private: void QueueThread(){
      static const double timeout = 0.01;
      while (this->rosNode->ok())
      {
        this->rosQueue.callAvailable(ros::WallDuration(timeout));
        std_msgs::String m;
        std::stringstream  ms;
        ;
        m.data=this->ms.str();
        this->rosPub.publish(m);
      }
    }

};
  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(RotacionPlataforma);
}
#endif
