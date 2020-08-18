#include "MenuState.hpp"

#include "GameEngine.hpp"

Texture MenuState::title_img;

MenuState::MenuState()
	: GameState(StateId::Menu)
	, menu_texts()
	, option(0)
{
	title_img = LoadTexture("img.png");
	menu_texts.push_back("Play");
	menu_texts.push_back("About");
	menu_texts.push_back("Exit");

	option = menu_texts.size() * 1000;
}

void MenuState::handle_input()
{
	if (IsKeyPressed(KEY_DOWN)) ++option;
	else if (IsKeyPressed(KEY_UP)) --option;
	else if (IsKeyPressed(KEY_ENTER)) {
		switch (this->get_selected()) {
		case 0:
			this->set_next_state(StateId::Playing);
			break;

		case 1:
			this->set_next_state(StateId::About);
			break;

		case 2:
			GameEngine::get_instance()->quit();
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
	DrawTextureEx(title_img, { 800, 0 }, 0.0f, 0.33f, WHITE);
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
	option = 0;
}
