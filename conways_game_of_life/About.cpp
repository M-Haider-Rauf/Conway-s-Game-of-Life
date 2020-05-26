#include "About.hpp"

AboutState::AboutState()
	: GameState(StateId::About)
{
}

void AboutState::handle_input()
{
	if (IsKeyPressed(KEY_ENTER)) {
		this->set_next_state(StateId::Menu);
	}
}

void AboutState::render() const
{
	const char* about_text = "Hello! This is my attempt at making Conway's\n"
		"game of  Life. It's  basically a form of cellular automation\n"
		"If you got no idea what it is, look it up, pretty interesting\n"
		"stuff. You can press P to pause and arrow keys to control\n"
		"speed. Anyways, press ENTER to go back! \n\t\tDated: 5/26/2020\n";
	DrawText(about_text, 40, 100, 40, RED);
}
