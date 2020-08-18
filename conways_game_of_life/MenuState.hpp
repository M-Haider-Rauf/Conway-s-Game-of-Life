#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "GameState.hpp"
#include <vector>
#include <string>

class MenuState : public GameState {
public:
	MenuState();
	~MenuState() { UnloadTexture(title_img); }

	void handle_input() override;
	void tick() override;
	void render() const override;

	void on_enter() override;
	void on_exit() {};

	int get_selected() const {
		return option % menu_texts.size();
	}

private:
	std::vector<std::string> menu_texts;
	int option;

	static Texture title_img;
};

#endif // !MENU_STATE_HPP
