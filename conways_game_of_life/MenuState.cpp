#include "MenuState.hpp"

#include "GameEngine.hpp"

Texture MenuState::waifu = {};

MenuState::MenuState()
	: GameState(StateId::Menu)
	, menu_texts()
	, state(0)
{
	waifu = LoadTexture("img.png");
	menu_texts.push_back("Play");
	menu_texts.push_back("About");
	menu_texts.push_back("Exit");
}

void MenuState::handle_input()
{
	if (IsKeyPressed(KEY_DOWN)) ++state;
	else if (IsKeyPressed(KEY_UP)) --state;
	else if (IsKeyPressed(KEY_ENTER)) {
		switch (this->get_selected()) {
		case 0:
			this->set_next_state(StateId::Playing);
			break;

		case 1:
			this->set_next_state(StateId::About);
			break;

		case 2:
			GameEngine::should_quit = true;
			break;

		default:
			break;
		}
	}
}

void MenuState::tick()
{
}

void MenuState::render() const
{
	DrawText("Conway's Game of Life \nby Haider Rauf", 100, 50, 60, VIOLET);
	DrawTextureEx(waifu, { 800, 0 }, 0.0f, 0.33f, WHITE);
	for (size_t i = 0; i < menu_texts.size(); ++i) {
		if (i == this->get_selected()) {
			DrawText(menu_texts[i].c_str(), 100, i * 100 + 300, 40, RED);
		}
		else {
			DrawText(menu_texts[i].c_str(), 100, i * 100 + 300, 40, BLUE);
		}
	}
}

void MenuState::on_enter()
{
	state = 0;
}
