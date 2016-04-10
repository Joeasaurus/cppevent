#pragma once
#include <functional>
#include <chrono>
#include "Event.hpp"

using namespace std;
using namespace std::chrono;

namespace cppevent {
	class TimedEvent {
		public:
			TimedEvent(milliseconds intv, function<void(milliseconds)> func) : interval(intv), callback(func) {
				lastTime = system_clock::now();
			};

			void call() {
				auto timenow = system_clock::now();
				auto newDelta = duration_cast<milliseconds>(timenow - lastTime);

				lastTime += newDelta;
				delta += newDelta;
				if (delta >= interval) {
					callback(delta);
					delta = milliseconds(0);
				}
			};
		private:
			milliseconds delta;
			milliseconds interval;
			system_clock::time_point lastTime;
			function<void(milliseconds)> callback;
	};
}