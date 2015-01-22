#ifndef CGAME_H
#define CGAME_H

#include "Globals.h"

// This header stores classes that are interdependent and core to the game
// Game, GameState


class GameState;

class Game
{
private:

	static Game *inst;

	Game();
	~Game();

	bool m_Running;

	bool m_FullScreen;

	char* caption;

	SDL_Window*  window;
	SDL_Surface* screenSurface;

	SDL_Event event;

	SDL_Color defaultColor;

	SDL_GLContext context;

	int screenWidth;
	int screenHeight;

	int maxFPS;

	SDL_DisplayMode currentDisplayMode;

public:

	static Game *GetInstance();

	bool Initialize();

	bool LoadContent();

	void UnloadContent();

	void Update();

	void Draw();

	void EventHandler();

	void ChangeState(GameState *state);

	void PushState(GameState *state);

	void PopState();

	void DestroyInstance();

	void ToggleFullScreen();

	void UpdateScreenDimensions();

	void RevertScreenDimensions();

	SDL_Event GetEvent()
	{
		return event;
	}

	bool isRunning()
	{
		return m_Running;
	}

	void StopRunning()
	{
		m_Running = false;
	}

	SDL_Window* GetWindow()
	{
		return window;
	}

	SDL_Surface* GetSurface()
	{
		return screenSurface;
	}

	SDL_Color GetDefaultColor()
	{
		return defaultColor;
	}

	int GetScreenWidth()
	{
		return screenWidth;
	}

	int GetScreenHeight()
	{
		return screenHeight;
	}

	int GetMaxFPS()
	{
		return maxFPS;
	}

	void SetMaxFPS(int newFPS)
	{
		maxFPS = newFPS;
	}

	void CycleColors(SDL_Color &color, int increment);


	vector<GameState *> GameStates; //GameState stack

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameState
{
public:
	virtual void Init(Game *game) = 0;
	virtual void Finalize() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Game *game) = 0;
	virtual void Draw(Game *game) = 0;
	virtual void Update(Game *game) = 0;

	void ChangeState(Game *game, GameState *state)
	{
		game->ChangeState(state);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif