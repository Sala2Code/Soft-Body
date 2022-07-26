const int width = 900;
const int height = 900;
const int rayon = 10;
const int taille = 100;

sf::RenderWindow window;
sf::ContextSettings options;
const int fps = 60;
bool isEnter = false;
bool isStop = false; // To connect 2 points already made

int n_point = 0;
int n_hook = 0;
const int nb_point = 100;
const int nb_hook = 4; // per point
const float absorb_floor = 0.8;
