#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace std;

/*
 * 拓展 2：事件时间线排序（Event Timeline）
 * ----------------------------------------
 * 输入格式：
 *     第一行：整数 N（日志条数）
 *     后面 N 行：每行是一条“宽松格式”日志，如：
 *
 *          [2025年03月01日] 09:30:00 login
 *          今天是2025年3月1日 08点00分00秒 wake_up
 *          2024/12/31-23:59:59 new_year_eve
 *
 * 解析规则：
 *   - 提取一行中的所有整数
 *   - 若数量 < 6，则缺日期/时间，丢弃
 *   - 前六个整数 =
 *        year, month, day, hour, minute, second
 *
 *   - 日期非法/时间非法 → 丢弃该条
 *   - 否则作为事件保存
 *
 * 输出：
 *   - 按时间升序排序后，统一格式输出：
 *
 *        YYYY-MM-DD HH:MM:SS  原始整行
 *
 * 这是一道“工程化味道更强”的小题：
 *   - struct 设计（DateTime / Event）
 *   - 自定义排序（operator<）
 *   - 解析逻辑与业务逻辑分离
 */

vector<int> extractInts(const string& s) {
    vector<int> nums;
    int i = 0;
    while (i < (int)s.size()) {
        if (isdigit((unsigned char)s[i])) {
            int v = 0;
            while (i < (int)s.size() && isdigit((unsigned char)s[i])) {
                v = v * 10 + (s[i] - '0');
                i++;
            }
            nums.push_back(v);
        } else i++;
    }
    return nums;
}

/**************** 日期工具 ****************/

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    static int base[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m < 1 || m > 12) return 0;
    if (m == 2) return isLeap(y) ? 29 : 28;
    return base[m];
}

bool validDate(int y, int m, int d) {
    int dim = daysInMonth(y, m);
    return m>=1 && m<=12 && d>=1 && d<=dim;
}

bool validTime(int h, int m, int s) {
    return h>=0 && h<=23 && m>=0 && m<=59 && s>=0 && s<=59;
}

/**************** 结构体 ****************/

struct DateTime {
    int y,m,d,hh,mm,ss;
};

// 时间排序规则
bool operator<(const DateTime& a, const DateTime& b) {
    if (a.y  != b.y)  return a.y  < b.y;
    if (a.m  != b.m)  return a.m  < b.m;
    if (a.d  != b.d)  return a.d  < b.d;
    if (a.hh != b.hh) return a.hh < b.hh;
    if (a.mm != b.mm) return a.mm < b.mm;
    return a.ss < b.ss;
}

struct Event {
    DateTime t;
    string raw; // 原始整行
};

int main() {
    int N;
    cin >> N;
    string dummy;
    getline(cin, dummy); // 吃掉换行

    vector<Event> events;
    events.reserve(N);

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);

        auto nums = extractInts(line);
        if (nums.size() < 6) continue; // 不完整

        DateTime t { nums[0], nums[1], nums[2],
                     nums[3], nums[4], nums[5] };

        if (!validDate(t.y, t.m, t.d)) continue;
        if (!validTime(t.hh, t.mm, t.ss)) continue;

        events.push_back({t, line});
    }

    // 时间排序
    sort(events.begin(), events.end(),
         [](const Event& a, const Event& b){
             return a.t < b.t;
         });

    // 输出统一格式
    for (auto& e : events) {
        auto& t = e.t;
        cout << setfill('0')
             << setw(4) << t.y << "-"
             << setw(2) << t.m << "-"
             << setw(2) << t.d << " "
             << setw(2) << t.hh << ":"
             << setw(2) << t.mm << ":"
             << setw(2) << t.ss
             << "  " << e.raw << "\n";
    }

    return 0;
}
