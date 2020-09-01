#ifndef PLATAFORMA
#define PLATAFORMA
#include "listener.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
namespace gazebo{
  class Listener;
  class RotacionPlataforma: public ModelPlugin{


      private: physics::JointPtr joint;
      private: common::PID pid;
      physics::ModelPtr modelo;
      sdf::ElementPtr sdf;
      Listener *listener;
      std::string estado;
      void buscar(physics::BasePtr contenedor, const physics::Entity::EntityType &);
      public:
        void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
      const std::string& getEstado() const{
        return estado;
      }
      void pintar(std::string);

      };
}
#endif
