
#include "game.h"

Player player;
MainMenu mainMenu;
LevelEditor levelEditor;
bool atStart;

enum class Menu;
Menu currentMenu;

std::vector<Block> blocks;
TTF_Font* titleFont;
TTF_Font* font;
TTF_Font* creditFont;

std::vector<Level> levels;
std::list<Ball> balls;

int hitsToAddBall;
int ballID = 0;

void ConstructLevel(std::string level) {

    blocks.clear();
    levels.clear();
    levelEditor.editor_blocks.clear();

    std::string levelname = "levels/" + level + ".txt";
    std::ifstream t(levelname);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());    

    for (unsigned int i = 0; i < 256; i++)
    {
        Block block;

        block.x = i % 16 * (block.w + 10);
        block.y = i / 16 * (block.h + 10);

        char a = str.at(i);
        int health = a - '0';

        block.health = health;
        block.updateColor();
        blocks.push_back(block);
    }

    hitsToAddBall = 1;

    atStart = true;
    balls.clear();

    AddBall();
}

void LoadLevels() {

    levels.clear();

    const std::filesystem::path levelsPath{ "levels/" };
    
    int i = 0;

    // Iterate over the `std::filesystem::directory_entry` elements
    for (auto const& dir_entry : std::filesystem::directory_iterator{ levelsPath })
    {
        std::string s;
        std::stringstream ss;
        ss << dir_entry;
        ss >> s;
        
        int first = 0;

        for (size_t i = 0; i < s.length(); i++)
        {
            if (s.at(i) == '/') 
            {
                if (first == 0) {
                    first = i + 1;
                }
            }
            else if (s.at(i) == '.') {
                s = s.substr(first, i - first);
                break;
            }
        }

        Level level;
        int wordLenght = s.length();

        level.levelName = s;
        level.text_rect = { 30, 30 + (i * 30), 10 * wordLenght, 20 };
        levels.push_back(level);
        i++;
    }
}

void LoadAudio() {
    LoadAudioFiles();
}

void LoadFont()
{
    if (TTF_Init() == -1)
        std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
    font = TTF_OpenFont("assets/8BIT.ttf", 72);
    creditFont = TTF_OpenFont("assets/font.ttf", 24);
    //font = TTF_OpenFont("audio/Fuji_Quake_Zone.ttf", 48);
    //font = TTF_OpenFont("audio/NeoTech.ttf", 48);
    titleFont = TTF_OpenFont("assets/NeoTechItalic.ttf", 72);
    if (font == NULL || titleFont == NULL || creditFont == NULL) {
        std::cout << "font not loaded" << std::endl;
    }
}

void AddBall() {
    Ball ball = Ball(); // feedback: you don't have to call a constructor explicitly in this case. Declaring a Ball instance would
                        // trigger default constructor for this class anyways. Currently you create 2 instences and a second instance is
                        // being copied to the first one.
    ball.ballInStart(player.rect);
    ball.id = ballID;
    ballID++;
    balls.push_back(ball);
}

void HitsToNewBall() {
    if (hitsToAddBall == 10) {
        hitsToAddBall = 0;
        AddBall();
    }
}

bool InsideRect(SDL_Rect rect, int mouseX, int mouseY) {
    if ((mouseX > rect.x) && (mouseX < rect.x + rect.w) && (mouseY > rect.y) && (mouseY < rect.y + rect.h))
    {
        return true;
    }
    return false;
}