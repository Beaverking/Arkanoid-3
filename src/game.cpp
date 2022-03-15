
#include "game.h"

Player player;
Ball ball = Ball();
MainMenu mainMenu;
LevelEditor levelEditor;
bool atStart;

enum class Menu;

std::vector<Block> blocks;
std::vector<int> collidedBlocksIndex;
TTF_Font* titleFont;
TTF_Font* font;

std::vector<Level> levels;

void ConstructLevel(std::string level) {

    std::string levelname = "levels/" + level + ".txt";

    std::ifstream t(levelname);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    
    std::cout << str << std::endl;
    std::cout << str.length() << std::endl;    

    for (size_t i = 0; i < 256; i++)
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
}

void LoadLevels() {

    const std::filesystem::path levelsPath{ "levels/" };
    //std::cout << "directory_iterator:\n";
    SDL_Color White = { 255, 255, 255 };
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

        level.text_rect = { 30, 30 + (i * 30), 10 * wordLenght, 20 };
        level.message = TTF_RenderText_Solid(font, s.c_str(), White);
        level.text = SDL_CreateTextureFromSurface(render, level.message);
        level.levelName = s;

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
    //font = TTF_OpenFont("audio/2TECH2.ttf", 48);
    //font = TTF_OpenFont("audio/Fuji_Quake_Zone.ttf", 48);
    //font = TTF_OpenFont("audio/NeoTech.ttf", 48);
    titleFont = TTF_OpenFont("assets/NeoTechItalic.ttf", 72);
    if (font == NULL || titleFont == NULL) {
        std::cout << "font not loaded" << std::endl;
    }
}


