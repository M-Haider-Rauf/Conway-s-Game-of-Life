#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "GameState.hpp"
#include <vector>
#include <string>

class MenuState : public GameState {
public:
	MenuState();
	~MenuState() { UnloadTexture(waifu); }

	void handle_input() override;
	void tick() override;
	void render() const override;

	void on_enter() override;
	void on_exit() {};

	size_t get_selected() const {
		return state % menu_texts.size();
	}

private:
	std::vector<std::string> menu_texts;
	size_t state;

	static Texture waifu;
};

#endif // !MENU_STATE_HPP
