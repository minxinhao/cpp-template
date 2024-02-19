
//
// task:
//
// read in a csv containing meeting schedules:
//   <room> <from (hhmm)> <duration (minutes)> <meeting name>
//   bricks, 900, 15, introduction
//   bricks, 915, 60, standard library
//   bricks, 945, 15, break
//   bricks, 1000, 60, standard library hands-on
//   cafetaria, 1200, 45, lunch
//   bricks, 1300, 15, break
//
// then, read commands from standard input:
//   sorted <column number>: print the list, sorted by column
//   overlaps: print overlapping meetings
//   holes: print space between meetings
//   room <room>: prints only meetings in <room>
//   quit
//
#include "dbg.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>

using time_point = std::tuple<uint8_t, uint8_t>;
using duration = std::tuple<time_point, time_point>;

struct meeting
{

    time_point start_time;
    uint64_t duration;
    std::string room;
    std::string meeting_name;

    meeting(uint8_t _start_hour, uint8_t _start_min, uint64_t _duration, std::string &&_room,
            std::string &&_meeting_name)
        : start_time(_start_hour, _start_min), duration(_duration), room(_room), meeting_name(_meeting_name)
    {
    }

    meeting(const meeting &) = default;
    meeting(meeting &&) = default;

    meeting &operator=(const meeting &m1) = default;
    meeting &operator=(meeting &&m1) = default;
    bool operator==(const meeting &m1) const = default;

    time_point get_end_point() const
    {
        uint8_t num_min = duration % 60;
        num_min = std::get<1>(start_time) + num_min;
        uint8_t num_hour = duration / 60 + num_min / 60;
        num_min %= 60;
        return std::tuple(std::get<0>(start_time) + num_hour, num_min);
    };

    bool is_over_lap(const meeting &m2) const
    {
        auto end_1 = this->get_end_point();
        auto end_2 = m2.get_end_point();
        if (this->start_time < m2.start_time && end_1 > m2.start_time)
            return true;
        else if (this->start_time > m2.start_time && end_2 > this->start_time)
            return true;
        return false;
    }
};

duration operator-(const time_point &a, const time_point &b)
{
    return std::tuple(a, b);
}

bool operator<(const time_point &a, const time_point &b)
{
    if (std::get<0>(a) < std::get<0>(b))
        return true;
    if (std::get<0>(a) == std::get<0>(b) && std::get<1>(a) < std::get<1>(b))
        return true;
    return false;
}

bool operator>(const time_point &a, const time_point &b)
{
    if (a != b && !(a < b))
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const meeting &m)
{
    os << "Start Time: " << static_cast<int>(std::get<0>(m.start_time)) << ":"
       << static_cast<int>(std::get<1>(m.start_time)) << std::endl;
    os << "Duration: " << m.duration << std::endl;
    os << "Room: " << m.room << std::endl;
    os << "Meeting Name: " << m.meeting_name << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const duration &d)
{
    auto &&start = std::get<0>(d);
    auto &&end = std::get<1>(d);
    os << "Start TIme" << static_cast<int>(std::get<0>(start)) << ":" << static_cast<int>(std::get<1>(start))
       << std::endl;
    os << "End TIme" << static_cast<int>(std::get<0>(end)) << ":" << static_cast<int>(std::get<1>(end)) << std::endl;
    return os;
}

std::vector<meeting> read_file()
{
    std::string filename = "../test_template/meeting.csv";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return std::vector<meeting>();
    }

    std::string line;
    std::vector<meeting> schedule;
    while (std::getline(file, line))
    {
        auto split = line | std::views::split(',');
        auto it = split.begin();
        auto room = *(it++);
        uint64_t start_time = std::stoi(std::string((*it).begin(), (*it).end()));
        it++;
        uint8_t start_hour = start_time / 100;
        uint8_t start_min = start_time % 100;
        uint64_t duration = std::stoi(std::string((*it).begin(), (*it).end()));
        it++;
        auto meeting_name = *it;

        schedule.emplace_back(start_hour, start_min, duration, std::string(room.begin(), room.end()),
                              std::string(meeting_name.begin(), meeting_name.end()));
    }
    // dbg(schedule);

    file.close();
    return schedule;
}

void sort_by_column(std::vector<meeting> &schedule, std::string &column_id)
{
    if (column_id == "room")
        std::sort(schedule.begin(), schedule.end(),
                  [](const meeting &m1, const meeting &m2) { return m1.room < m2.room; });
    if (column_id == "time")
        std::sort(schedule.begin(), schedule.end(),
                  [](const meeting &m1, const meeting &m2) { return m1.start_time < m2.start_time; });
    if (column_id == "duration")
        std::sort(schedule.begin(), schedule.end(),
                  [](const meeting &m1, const meeting &m2) { return m1.duration < m2.duration; });
    if (column_id == "name")
        std::sort(schedule.begin(), schedule.end(),
                  [](const meeting &m1, const meeting &m2) { return m1.meeting_name < m2.meeting_name; });
}

void overlaps(std::vector<meeting> &schedule)
{
    // 1. 按照教室排序
    std::sort(schedule.begin(), schedule.end(), [](const meeting &m1, const meeting &m2) { return m1.room < m2.room; });

    // 2. adjacecnt difference
    auto check_room = [&](const meeting &m) -> void {
        static int cnt = 0;
        auto end_time = m.get_end_point();
        auto it = std::find(schedule.begin(), schedule.end(), m);
        auto it_2 = (it == schedule.end()) ? schedule.end() : it + 1;
        while (it_2 != schedule.end() && it_2->room == m.room)
        {
            if (m.is_over_lap(*it_2))
            {
                std::cout << "---overlap meeting " << cnt++ << "---\n";
                dbg(*it);
                dbg(*it_2);
            }
            it_2++;
        }
    };

    std::for_each(schedule.begin(), schedule.end(), check_room);
}

void holes(std::vector<meeting> &schedule)
{
    // 1. 去除overlap的所有meeting
    std::vector<const meeting *> non_overlap;
    std::for_each(schedule.begin(), schedule.end(), [&](const meeting &m) {
        auto end_time = m.get_end_point();
        auto it = std::find(schedule.begin(), schedule.end(), m);
        auto it_2 = (it == schedule.end()) ? schedule.end() : it + 1;
        while (it_2 != schedule.end() && it_2->room == m.room)
        {
            if (m.is_over_lap(*it_2))
                return;
            it_2++;
        }
        non_overlap.push_back(&m);
    });

    // 2. 对于剩下的meeting sort by start time
    std::sort(non_overlap.begin(), non_overlap.end(),
              [](const meeting *m1, const meeting *m2) { return m1->start_time < m2->start_time; });
    std::for_each(non_overlap.begin(), non_overlap.end(), [](const meeting *m) { dbg(*m); });
}

void print(std::vector<meeting> &schedule, std::string &room)
{
    std::for_each(schedule.begin(), schedule.end(), [&](const meeting &m) {
        if (m.room == room)
            dbg(m);
    });
}

void read_command(std::vector<meeting> &schedule)
{
    std::string command;
    while (true)
    {
        std::cin >> command;
        if (command == "quit")
            return;
        else if (command == "sorted")
        {
            std::string colunm_id;
            std::cin >> colunm_id;
            sort_by_column(schedule, colunm_id);
        }
        else if (command == "overlap")
        {
            overlaps(schedule);
        }
        else if (command == "holes")
        {
            holes(schedule);
        }
        else if (command == "room")
        {
            std::string room_id;
            std::cin >> room_id;
            print(schedule, room_id);
        }
    }
}

int main()
{
    auto schedule = read_file();

    read_command(schedule);
    return 0;
}