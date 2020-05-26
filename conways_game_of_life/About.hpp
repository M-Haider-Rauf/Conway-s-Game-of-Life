#ifndef ABOUT_STATE_HPP
#define ABOUT_STATE_HPP

#include "GameState.hpp"

class AboutState : public GameState {
public:
	AboutState();

	void handle_input() override;
	void tick() override {};
	void render() const override;

	void on_enter() override {};
	void on_exit() override {};

private:

};

#endif // !ABOUT_STATE_HPP
