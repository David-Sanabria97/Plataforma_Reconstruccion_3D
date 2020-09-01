#include "rotacion_plataforma.h"
#include "listener.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "comandos.h"

namespace gazebo
{
        
        void RotacionPlataforma::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf){

              this->modelo=_model;
              this->joint=modelo->GetJoints()[1];
              this->pid = common::PID(1,1,2);
              gzdbg<<"Bienvenidos a la Plataforma de Recontruccion \r\n";
              listener= new Listener();
              listener->init(this);
              this->estado="iniciado";

              gzdbg <<  this->joint->GetName() + "   \r\n";





    }

    void RotacionPlataforma::pintar(std::string tipo){

            gzdbg <<  std::to_string(this->joint->GetAngle(0).Radian()) + "   \r\n";
            this->modelo->GetJointController()->SetPositionPID(this->joint->GetScopedName(), this->pid);
            this->modelo->GetJointController()->SetPositionTarget(this->joint->GetScopedName(), 3);



    }




  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(RotacionPlataforma);
}
