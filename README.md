# Plataforma_Reconstruccion_3D

El codigo es la simulacion de una pltaforma de recontruccion 3D apartir de un sensor LiDAR HOKUYP el cual emite un laser 2D, la simulacion es realizada en GAZEBO
Cuenta con un Launcher, el mundo de GAZEBO con el modelo de la plataforma de recontruccion, dos codigos en python para la recontruccion simulada y real.

CLONAR REPOSITORIO 



CORRER CODIGO

1 ) para que el codigo funcione correctamente debe ingresar a la carpeta  src/plataforma/world/plataforma.world
cambiar los valores de en los links del modelo por la ruta correspondiente a su ordenador 

ejemplo linea 133  <uri>file:///home/david/Plataforma_Reconstruccion_3D/meshes/Chassis.STL</uri> cambiar /david por su correcpondiente /user

2) realizado el punto numero 1 debe seguir con:

$ cd /Plataforma_Reconstruccion_3D 

$ source devel/setup.sh

$ roslaunch plataforma plataforma.launcher

esto iniciara el simulador GAZEBO el cual iniciara en PAUSE

3) en otra ventana de terminal ejecutar 

Click Run en GAZEBO

$ cd /Plataforma_Recontruccion_3D/src 

$ python Scaner3D_simulado.py Nombre_archivo Angulo_max Angulo_Step

Scaner3D_simulador.py creara un archivo llamado Nombre_archivo.txt

Angulo_max  corresponde el algulo al que llegara la plataforma 

Angulo_Step corresponde al angulo en el que se movera para cada toma de datos


