#include <iostream>
#include <string>
#include <set>
#include <map>
#include <deque>

using namespace std;

class HotelManager {

struct TimedData
{
  int64_t time;
  map<string, int64_t> room_counts;
  map<string, set<int64_t>> client_ids;
};

public:
  void Book(int64_t time, const string& hotel_name, const int64_t client_id, int64_t room_count) {
    size_t size = all_hotel_data.size();

    if (size != 0 && all_hotel_data[size - 1].time == time)
    {
      TimedData& data = all_hotel_data[size - 1];
      data.client_ids[hotel_name].insert(client_id);
      data.room_counts[hotel_name] += room_count;
      return;
    }
    
    TimedData data;
    data.time = time;
    data.room_counts[hotel_name] = room_count;
    data.client_ids[hotel_name].insert(client_id);

    all_hotel_data.push_back(data);

    int64_t threshold = all_hotel_data[all_hotel_data.size() - 1].time - 86400;
    while (all_hotel_data.front().time <= threshold) all_hotel_data.pop_front();
  }

  int64_t GetLastRoomCount(const string& hotel_name) {
    int64_t total_room_count = 0;
    for (const TimedData& data : all_hotel_data)
    {
      if (data.room_counts.count(hotel_name) != 0)
      {
        total_room_count += data.room_counts.at(hotel_name);
      }
    }
    return total_room_count;
  }

  int64_t GetLastDistinctClientCount(const string& hotel_name) {
    set<int64_t> distinct_clients;
    for (const TimedData& data : all_hotel_data)
    {
      if (data.client_ids.count(hotel_name) != 0)
      {
        distinct_clients.insert(data.client_ids.at(hotel_name).begin(), data.client_ids.at(hotel_name).end());
      }
    }
    return distinct_clients.size();
  }

private:
  deque<TimedData> all_hotel_data;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  HotelManager hotelManager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    if (query_type == "BOOK") {
      int64_t time;
      string hotel_name;
      int64_t client_id;
      int64_t room_count;
      cin >> time >> hotel_name >> client_id >> room_count;
      hotelManager.Book(time, hotel_name, client_id, room_count);
    } else if (query_type == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;
      cout << hotelManager.GetLastDistinctClientCount(hotel_name) << "\n";
    } else if (query_type == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;
      cout << hotelManager.GetLastRoomCount(hotel_name) << "\n";
    }
  }

  return 0;
}