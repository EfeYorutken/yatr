/*
	 implement the engine.cpp
 */

#include <chrono>
#include <concepts>
#include <ftxui/component/app.hpp>
#include <ftxui/dom/deprecated.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <print>
#include <ranges>
#include <string>
#include <vector>
#include <format>
#include <thread>

#include "game_engine.cpp"

#include <ftxui/component/event.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/dom/elements.hpp"

const int w = 20;
const int h = 35;

std::string Code(ftxui::Event event) {
  std::string codes;
  for (auto& it : event.input()) {
    codes += " " + std::to_string('a' + (unsigned int)it);
  }
  return codes;
}


int main(){

	/*
	Engine<w, h, 10> engine;

	engine.display();
	*/

	auto screen = ftxui::ScreenInteractive::Fullscreen();
	std::vector<ftxui::Event> events;

	std::pair<int, int> top_left_corner = {0,0};

	auto component = ftxui::Renderer([&] {

			ftxui::Elements children = {
			ftxui::text(std::format("{}", "stuff")),
			ftxui::separator(),
			ftxui::canvas(w, h, [&](ftxui::Canvas& canvas){
					canvas.DrawBlock(top_left_corner.first, top_left_corner.second, true, ftxui::Color::Red);
					return;
					})
			};

			return ftxui::vbox(children);
			});

	std::atomic<bool> running = true;
	std::thread ticker_thread([&running, &screen](){
			while(running){ 
			std::this_thread::sleep_for(std::chrono::seconds(1));
			screen.PostEvent(ftxui::Event::Custom);
			}
			});

	component |= ftxui::CatchEvent([&events, &top_left_corner](ftxui::Event e){ 

			if( e == ftxui::Event::Custom ){
			++top_left_corner.first;
			return true;
			}

			events.push_back(e);
			return true; 
			});

	screen.Loop(component);

	running = false;

	if(ticker_thread.joinable()){
		ticker_thread.join();
	}


	return 0;
}
