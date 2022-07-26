struct D_line{
    sf::RectangleShape line;
    // Indexes
    int i_p1;
    int i_p2;
    sf::Vector2f normale;

    void updateLine(Point point1, Point point2);
    D_line(){};
    D_line(Point p1, Point p2, int i_1, int i_2){
        float x1 = p1.pos.x;
        float y1 = p1.pos.y;
        float x2 = p2.pos.x;
        float y2 = p2.pos.y;

        i_p1 = i_1;
        i_p2 = i_2;

        line.setSize({static_cast<float>(sqrt(pow(x1-x2,2)+pow(y1-y2,2))),1});
        line.setFillColor(sf::Color::White);
        line.setPosition(x1+rayon,y1+rayon);

        float angle = (y2>y1) ? acos((x2 - x1)/(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2)))) : - acos((x2 - x1)/(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2))));  
        line.setRotation(angle*180/PI);
    }
};

void D_line::updateLine(Point p1, Point p2){
        float x1 = p1.pos.x;
        float y1 = p1.pos.y;
        float x2 = p2.pos.x;
        float y2 = p2.pos.y;

        line.setSize({static_cast<float>(sqrt(pow(x1-x2,2)+pow(y1-y2,2))),1});
        line.setPosition(x1+rayon,y1+rayon);
        float angle = (y2>y1) ? acos((x2 - x1)/(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2)))) : - acos((x2 - x1)/(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2))));  
        line.setRotation(angle*180/PI);
}
