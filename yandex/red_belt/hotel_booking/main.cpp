#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>

using namespace std;

class HotelManager {

struct SecondData
{
  int64_t time;
  map<string, int64_t> room_counts;
  map<string, map<int64_t, int64_t>> client_counts;
};

public:

  void Book(int64_t time, const string& hotel_name, const int64_t client_id, int64_t room_count) {
    if (all_hotel_data.size() != 0 && all_hotel_data.back().time == time)
    {
      SecondData& data = all_hotel_data.back();
      data.client_counts[hotel_name][client_id]++;
      data.room_counts[hotel_name] += room_count;
      all_room_counts[hotel_name] += room_count;
      all_client_counts[hotel_name][client_id]++;
      return;
    }
    
    SecondData data;
    data.time = time;
    data.room_counts[hotel_name] = room_count;
    data.client_counts[hotel_name][client_id] = 1;

    all_hotel_data.push_back(data);
    all_room_counts[hotel_name] += room_count;
    all_client_counts[hotel_name][client_id]++;

    int64_t threshold = all_hotel_data.back().time - 86400;
    while (all_hotel_data.front().time <= threshold) {
      for (const auto& [hotel_key, map_value] : all_hotel_data.front().client_counts) {
        for (const auto& [client_key, client_value] : map_value) {
          all_client_counts[hotel_key][client_key] -= client_value;
          if (all_client_counts[hotel_key][client_key] <= 0) {
            all_client_counts[hotel_key].erase(client_key);
          }
        }
      }

      for (const auto& [hotel_key, room_value] : all_hotel_data.front().room_counts) {
        all_room_counts[hotel_key] -= room_value;
      }

      all_hotel_data.pop_front();
    }
  }

  int64_t GetLastRoomCount(const string& hotel_name) {
    return all_room_counts[hotel_name];
  }

  size_t GetLastDistinctClientCount(const string& hotel_name) {
    return all_client_counts[hotel_name].size();
  }

private:
  deque<SecondData> all_hotel_data;
  map<string, int64_t> all_room_counts;
  map<string, map<int64_t, int64_t>> all_client_counts;
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