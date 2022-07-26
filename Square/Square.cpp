////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <array>
#include <vector>

#include <math.h>       
#define PI 3.14159265

#include "console.hpp"
#include "constants.hpp"
#include "point.hpp"
#include "connect.hpp"

std::array<Point,nb_point> list_point{};
std::array<D_line,nb_point*nb_hook> list_connect{};

void connect_mesh(Point p1, Point p2, int i_p1, int i_p2);

int main()
{
    Point last_point; //point selected
    int i_last_point; // index of the selected point

    
    LoadFont();

    sf::RenderWindow window(sf::VideoMode(width, height), "Soft-bodied");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(fps);
    options.antialiasingLevel = 8;

    while (window.isOpen())
    {
        int mouse_x = sf::Mouse::getPosition(window).x;
        int mouse_y = sf::Mouse::getPosition(window).y;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            } 
            if (event.type == sf::Event::MouseButtonPressed){
                // Drag
                if (event.mouseButton.button == sf::Mouse::Left && isEnter){
                    for(int i=0; i<n_point;i++){
                        float dist = sqrt(pow(list_point[i].pos.x-mouse_x+rayon,2)+pow(list_point[i].pos.y - mouse_y+rayon,2));
                        if(dist <= rayon){
                            list_point[i].drag = true;
                        }
                    }
                }
            }
            // Released the drag
            if(event.type == sf::Event::MouseButtonReleased){
                for(int i =0; i<n_point;i++){
                    list_point[i].drag = false;
                }
            }
        }
        window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isEnter){ // To create a Squre
            for(int i=0; i<nb_point; i++){
                //Same formule to create a regular n-polygon
                Point point({static_cast<float>(cos(2*PI*n_point/nb_point)*taille + width/2), static_cast<float>(sin(2*PI*n_point/nb_point)*taille + 400)}, n_point);
                if (n_point > 0){
                    connect_mesh(point,last_point,n_point,i_last_point); 
                }
                list_point[n_point] = point;
                last_point = point;
                i_last_point = n_point;
                n_point++;
            }
            connect_mesh(list_point[0],last_point,0,3); 
            connect_mesh(list_point[1],list_point[3],1,3); 
            connect_mesh(list_point[0],list_point[2],0,2); 
            isEnter = true;
        }
        if(isEnter){
            // ! Drag
            for(int i=0;i<n_point;i++){
                Point &p = list_point[i];
                if(p.drag){
                    float dist = sqrt(pow(p.pos.x-mouse_x,2)+pow(p.pos.y - mouse_y,2));
                    p.f={(mouse_x-p.pos.x)/dist,(mouse_y-p.pos.y)/dist};
                }
            }
            // ! Force
            const float g = 0.1;
            for(int i=0;i<n_point;i++){
                list_point[i].f.y+=g;
            }
            const float k_elastic = 0.1;
            const float k_damp = 0.3;
            const int l0_val = sqrt(2*pow(taille,2));
            for(int i=0;i<n_hook;i++){
                Point &p1 = list_point[list_connect[i].i_p1];
                Point &p2 = list_point[list_connect[i].i_p2];
                float dist_p1_p2 = sqrt(pow(p1.pos.x-p2.pos.x,2)+pow(p1.pos.y-p2.pos.y,2));
                
                if(dist_p1_p2>0.01){
                    sf::Vector2f v_p1_p2 = p1.v - p2.v;
                    float force = (dist_p1_p2-l0_val)*k_elastic + (v_p1_p2.x*(p1.pos.x-p2.pos.x)+v_p1_p2.y*(p1.pos.y-p2.pos.y))*k_damp/dist_p1_p2;
                    sf::Vector2f f = {force*((p1.pos.x-p2.pos.x)/dist_p1_p2) , force*((p1.pos.y-p2.pos.y)/dist_p1_p2)};

                    p1.f -= f;
                    p2.f += f;

                    list_connect[i].normale = {(p1.pos.y - p2.pos.y)/dist_p1_p2, -(p1.pos.x - p2.pos.x)/dist_p1_p2};
                }
            }

            // ! Maj
            for(int i=0;i<n_point;i++){
                list_point[i].updateVar();
                list_point[i].f = {0,0};
            }
            for(int i=0;i<n_hook;i++){
                list_connect[i].updateLine(list_point[list_connect[i].i_p1],list_point[list_connect[i].i_p2]);
            }
        }
        // Indication
        else{
            SetText(indication,"Press S to create a square." );
            indication.setPosition(10,10);
            window.draw(indication);
        }

        for(int i=0;i<n_point;i++){
            window.draw(list_point[i].point);
            window.draw(list_point[i].v_line);
        }
        for(int i=0;i<n_hook;i++){
            window.draw(list_connect[i].line);
        }
        window.display();
    }
    return 0;
}

void connect_mesh(Point p1, Point p2, int i_p1, int i_p2){
    list_connect[n_hook] = D_line{p1,p2,i_p1,i_p2};
    p1.list_neighbor.push_back(i_p2); 
    p2.list_neighbor.push_back(i_p1);
    n_hook++;   
}
