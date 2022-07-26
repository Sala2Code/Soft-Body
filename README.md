# Soft-Body
SFML Soft Body. You can draw your own structure easily, read the readme.

## Youtube

My YouTube Channel : https://www.youtube.com/channel/UCcEkxe69YprtYS2dDW7w5-Q
Video explain the code : soon...

## DrawYourMeshes.cpp

![Uploading 2022-07-26 16-00-15.gif…]()

With left click you can add points to build what you want.
To connect 2 points already drawn, press S and select them.
Then press Enter to run. 
You can move the structure with your mouse. Only, don't set the point radius value too low (otherwise you won't be able to catch it)


## Circle.cpp

![cercle sans vecteur](https://user-images.githubusercontent.com/109032171/181034549-e27dfc9c-8e1e-4218-a83a-5791eecc2fb3.gif)

![cerlce_vecteur](https://user-images.githubusercontent.com/109032171/181028712-c84e1ea5-84d7-4998-a5b8-5fb8d3e66d51.gif)

This simulation works with a feature added which is the pressure.
You can delete the velocity vector easily (read the Circle.cpp and at the end).
Then, you can add or substrat points (indeed it's not a circle but a n-polygone so you can create a square without diagonal and with pressure).
You can too modify the size of the circle and circle's points.
According to the pressure, number of points... change the "strength_drag" (in constants.hpp) to move the circle most or less quickly.

## Square.cpp

![square](https://user-images.githubusercontent.com/109032171/181028666-eddb5553-d844-4543-8c07-17355ee1b775.gif)

A simple square.
You can modify the size of square.
