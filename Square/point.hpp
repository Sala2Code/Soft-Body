struct Point{
    sf::CircleShape point;
    sf::RectangleShape v_line;

    int i_point;
    sf::Vector2f v {0,0}; // Speed
    sf::Vector2f f {0,0}; // Force
    sf::Vector2f pos{0,0};

    bool drag = false;
    std::vector<int> list_neighbor{};


    // Graphiques
    void setPos(sf::Vector2f pos_i);
    void updatePos();
    void updateVar();

    // Calculs
    sf::Vector2f F_collision(sf::Vector2f v_col, sf::Vector2f n);

    Point(){};
    Point(sf::Vector2f pos_i, int index){
        point.setRadius(rayon);
        point.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

        v_line.setSize({0,1});
        v_line.setFillColor(sf::Color::White);


        pos = {pos_i.x,pos_i.y};
        point.setPosition(pos.x,pos.y);
        i_point = index;
    }
};

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

const float absorb_floor = 0.8;
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