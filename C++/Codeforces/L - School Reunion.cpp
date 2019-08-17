#include <bits/stdc++.h>
 
using namespace std;
 
#define OPEN 0
#define CLOSE 1
#define MAX_TIME 1000000000 // 10^9
 
class EventLineSweep {
public:
	int time, type;
	EventLineSweep() {}
	EventLineSweep(int time, int type) : time(time), type(type) {}
	bool operator < (const EventLineSweep& other) const {
		if (time != other.time) {
			return time < other.time;
		}
		return type < other.type;
	}
};
 
bool CanExtendR(int time_l, int time_r, int time_reunion) {
	return time_r - time_l <= time_reunion;
}
 
bool CanMeet(const vector<EventLineSweep>& events, int min_meet, int time_reunion) {
	int active = 1;
	int r = 0;
	int size_events = int{events.size()};
	for (int l = 0; l < size_events; l++) {
		while (r + 1 < size_events && CanExtendR(events[l].time, events[r + 1].time, time_reunion)) {
			r++;
			if (events[r].type == OPEN) {
				active++;
			}
		}
		if (active >= min_meet) {
			return true;
		}
		if (events[l].type == CLOSE) {
			active--;
		}
	}
	return false;
}
 
int MinimumTime(const vector<EventLineSweep>& events, int min_meet) {
	int lo = 0, hi = MAX_TIME, mid = 0, min_time = MAX_TIME;
	while (lo <= hi) {
		mid = (lo + hi) / 2;
		if (CanMeet(events, min_meet, mid)) {
			hi = mid - 1;
			min_time = mid;
		} else {
			lo = mid + 1;
		}
	}
	return min_time;
}
 
int main() {
	int num_test_cases;
	vector<EventLineSweep> events;
	scanf("%d", &num_test_cases);
	for (int test_case = 1; test_case <= num_test_cases; test_case++) {
		int num_people, min_meet;
		scanf("%d %d", &num_people, &min_meet);
		events.clear();
		for (int i = 0; i < num_people; i++){
			int entry_time, exit_time;
			scanf("%d %d", &entry_time, &exit_time);
			events.push_back({entry_time, OPEN});
			events.push_back({exit_time, CLOSE});
		}
		sort(events.begin(), events.end());
		printf("Case %d: %d\n", test_case, MinimumTime(events, min_meet));
	}
	
	return 0;
}
