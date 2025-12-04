#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

/*
 * 拓展 1：宽松日期 + 计算当年的第几天
 * ----------------------------------
 * 功能描述：
 *   - 支持“多行输入”，直到 Ctrl+D (EOF)
 *   - 每一行都是杂乱的日期字符串，同母题
 *   - 抽取整数 → 前三个构成 year/month/day
 *   - 若格式错 → "format problem"
 *   - 若日期非法 → "invalid date"
 *   - 否则输出：
 *
 *        YYYY-MM-DD is day X of year
 *
 * 技术要点：
 *   - 闰年判断
 *   - 每月天数累加
 *   - 多行输入 while (getline)
 */

vector<int> extractInts(const string& s) {
    vector<int> nums;
    for (int i = 0; i < (int)s.size();) {
        if (isdigit(static_cast<unsigned char>(s[i]))) {
            int val = 0;
            while (i < (int)s.size() && isdigit((unsigned char)s[i])) {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            nums.push_back(val);
        } else i++;
    }
    return nums;
}

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    static int base[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m < 1 || m > 12) return 0;
    if (m == 2) return isLeap(y) ? 29 : 28;
    return base[m];
}

bool validDate(int y, int m, int d) {
    int dim = daysInMonth(y, m);
    return m >= 1 && m <= 12 && d >= 1 && d <= dim;
}

int dayOfYear(int y, int m, int d) {
    int sum = d;
    for (int i = 1; i < m; ++i) sum += daysInMonth(y, i);
    return sum;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;

        auto nums = extractInts(line);
        if (nums.size() < 3) {
            cout << "format problem\n";
            continue;
        }

        int y = nums[0], m = nums[1], d = nums[2];
        if (!validDate(y, m, d)) {
            cout << "invalid date\n";
            continue;
        }

        int k = dayOfYear(y, m, d);

        cout << setfill('0')
             << setw(4) << y << "-"
             << setw(2) << m << "-"
             << setw(2) << d
             << " is day " << k << " of year\n";
    }
    return 0;
}
