/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_game.h>
#include <vix_sdlwindow.h>
#include <vix_debugutil.h>

#ifdef VIX_DIRECTX_BUILD
#include <vix_dxrenderer.h>
#endif

#ifdef VIX_OPENGL_BUILD
#include <vix_glrenderer.h>
#endif

namespace Vixen {

	IGame::IGame()
	{
	    m_config = new GameConfig;
		m_window = new SDLGameWindow(m_config->WindowArgs());
#ifdef VIX_DIRECTX_BUILD
        m_renderer = new DXRenderer;
#elif defined(VIX_OPENGL_BUILD)
        m_renderer = new GLRenderer;
#endif
		m_keyboard = new SDLKeyboardState;
		m_mouse = new SDLMouseState;
		m_window->VSetParent(this);
		m_window->VSetRenderer(m_renderer);
	}

	int IGame::Run()
	{
		/*if application window exists*/
		if (m_window) {
			if(!m_window->VRun()) {
			  DebugPrintF(VTEXT("Application loop encountered error"));
				return -1;
			}
		}

        m_renderer->VDeInitialize();

		return 0;
	}

	IGameWindow* const IGame::GetWindow() const
	{
		return m_window;
	}

	IRenderer* const IGame::GetRenderer() const
	{
		return m_renderer;
	}

	GameConfig* const IGame::GetConfig() const
	{
	    return m_config;
	}

	SDLKeyboardState* const IGame::GetKeyboard() const
	{
		return m_keyboard;
	}

	SDLMouseState* const IGame::GetMouse() const
	{
		return m_mouse;
	}
}
