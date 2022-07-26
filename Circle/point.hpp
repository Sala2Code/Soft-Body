struct Point{
    sf::CircleShape point;
    sf::RectangleShape v_line;

    int i_point;
    sf::Vector2f v {0,0}; // Speed
    sf::Vector2f f {0,0}; // Force
    sf::Vector2f pos{0,0};

    bool drag = false;
    std::vector<int> list_neighbor{};
    sf::Vector2f l0; // named l0 because the initial position can give us the length of the spring at the start.

    // Graphiques
    void setPos(sf::Vector2f pos_i);
    void updatePos();
    void updateVar();

    // Calculs
    sf::Vector2f F_collision(sf::Vector2f v_col, sf::Vector2f n);
    bool isCollision(Point p1, Point p2, sf::Vector2f v);

    Point(){};
    Point(sf::Vector2f pos_i, int index){
        point.setRadius(rayon);
        point.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

        v_line.setSize({0,1});
        v_line.setFillColor(sf::Color::White);


        pos = {pos_i.x,pos_i.y};
        l0 = pos;
        point.setPosition(pos.x,pos.y);
        i_point = index;
    }
};

#include "connect.hpp"
std::array<Point,nb_point> list_point{};
std::array<D_line,nb_point*nb_hook> list_connect{};

// ! Graphiques
void Point::setPos(sf::Vector2f pos_i){
    point.setPosition(pos_i.x,pos_i.y);
    pos = {pos_i.x,pos_i.y};
    // a_pos = pos;
}

void Point::updateVar(){
    v+=f;
    // ! Bordure

    if(pos.y+v.y>height-2*rayon){
        v = F_collision(v,{0,-1});
    }
    else if(pos.y+v.y<0){
        v = F_collision(v,{0,1});
    }
    else if(pos.x+v.x>width-2*rayon){
        v = F_collision(v,{-1,0});
    }
    else if(pos.x+v.x<0){
        v = F_collision(v,{1,0});
    }
    else{ // Collision with others points and edges
        bool noCollision = true;
        for(int i=0;i<n_hook;i++){
            if(list_connect[i].i_p1 != i_point && list_connect[i].i_p2!=i_point){ // It's not colliding with itself
                Point p1 = list_point[list_connect[i].i_p1] ;
                Point p2 = list_point[list_connect[i].i_p2] ;
                if( isCollision(p1,p2,v) ){
                    sf::Vector2f n = { (p1.pos.y - p2.pos.y)/(p1.pos.x - p2.pos.x),-1}; //Définir normal vector
                    float norme = sqrt(pow(n.x,2)+pow(n.y,2));
                    n = {n.x / norme, n.y / norme}; // Normalize normal vector
                    v = F_collision(v,n);
                    noCollision = false;
                    break;
                }
            }
        }
        if(noCollision){
            for(int i=0;i<n_point;i++){
                if(i!=i_point){
                    Point p1 = list_point[i];
                    if(sqrt( pow(p1.pos.x-(pos.x+v.x),2)+pow(p1.pos.y-(pos.y+v.y),2) ) < rayon*2){
                        v=-v*absorb_floor;
                    }
                }
            }
        }
    }
    // To avoid an "explosion", you can delete this lines but you can encountered some errors.
    // const int v_tolerance = 7;
    // float v_norme = sqrt(pow(v.x,2)+pow(v.y,2)); 
    // if( v_norme > v_tolerance){
    //     v.x = v.x/v_norme*v_tolerance;
    //     v.y = v.y/v_norme*v_tolerance;
    // }

    pos+=v;
    point.setPosition(pos.x, pos.y);

    // ! v_line
    float mod = sqrt(pow(v.x,2)+pow(v.y,2));
    v_line.setSize({mod*10,2}); // "*10" is to better show.
    v_line.setPosition(pos.x+rayon,pos.y+rayon);
    float angle = (v.y>0) ? acos(v.x / mod) : - acos(v.x / mod);  
    v_line.setRotation(angle*180/PI);
}

// ! Calculs


sf::Vector2f Point::F_collision(sf::Vector2f v_col, sf::Vector2f n){
    return {
        static_cast<float>( 
            (v_col.x-2*n.x*( v_col.x * n.x + v_col.y*n.y ))*absorb_floor
        ),
        static_cast<float>(
            (v_col.y-2*n.y*( v_col.x * n.x + v_col.y*n.y ))*absorb_floor
        )
    };
}


const float dist_col = rayon;
bool Point::isCollision(Point p1, Point p2, sf::Vector2f v){
    // Equation droite => ax + b = y
    // Distance d'un point à cette droite => | ax + y + b | / sqrt(a²+1)
    if( ( p1.pos.x > pos.x+v.x && pos.x+v.x > p2.pos.x ) || ( pos.x+v.x > p1.pos.x && p2.pos.x > pos.x+v.x) ){

        float a = (p1.pos.y - p2.pos.y)/(p1.pos.x - p2.pos.x);
        float b = p1.pos.y - a*p1.pos.x;

        // Additional verification (because the speed is too much high and the distance can doesn't pass beneath of dist_col)
        if( ( pos.y+v.y > a*(pos.x+v.x)+b && pos.y < a*pos.x+b ) || ( a*(pos.x+v.x)+b > pos.y+v.y  && a*pos.x+b < pos.y )){
            return true;
        }

        if( abs(a*(pos.x+v.x) - (pos.y+v.y) + b) / sqrt(pow(a,2) + 1) < dist_col){
            return true;
        }
    }
    return false;
}
