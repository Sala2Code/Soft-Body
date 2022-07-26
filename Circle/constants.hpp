const int width = 900;
const int height = 900;
const int rayon = 1; // Radius of points
const int taille = 50; // The radius of the "ball"

sf::RenderWindow window;
sf::ContextSettings options;
const int fps = 60;
bool isEnter = false;

int n_point = 0;
int n_hook = 0;
const int nb_point = 20; // ! Here you can add or substrat points
const int nb_hook = 2; // per point

const float strength_drag = 3; // 1 is maybe not enough to handle a ball with a "pressure" and a "taille" high. Still, be aware to bugs with an excessive strength_drag 
const float absorb_floor = 0.8;
