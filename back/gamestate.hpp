#include "window.hpp"

class gamestate
{
public:
    gamestate();

private:
    bool m_running;
    std::unique_ptr<window> m_winOBJ;
};
