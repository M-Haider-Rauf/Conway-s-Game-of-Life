#include "GameState.hpp"
#include "Constants.hpp"


GameState::GameState(StateId id)
	: state_id (id)
	, next_state_if(StateId::Null)
{
}

GameState::~GameState()
{
}



