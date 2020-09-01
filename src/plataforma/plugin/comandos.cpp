#include "comandos.h"
#include <stdio.h>
#include "std_msgs/String.h"
#include <vector>
#include "rotacion_plataforma.h"


namespace gazebo{

      bool Comandos::procesar(std::string &comando, RotacionPlataforma * plataforma){
        std::vector<std::string> partes=split(comando, ' ');

        if(partes.size()==0){

        }else{
              switch (partes[0][0]) {
                case 'd':
                      if(partes.size()>1){
                          plataforma->pintar(partes[1]);
                      }
                      break;
              }

        }
      }

}
std::vector<std::string> split(const std::string &c, char d){
    std::vector<std::string> resultado;

    std::stringstream cs(c);
    std::string parte;
    while(std::getline(cs,parte,d)){
      resultado.push_back(parte);
    }
    return resultado;
}
