#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

/*
 * 母题：宽松日期解析（Loose Date Parsing）
 * ----------------------------------------
 * 功能目标：
 *   - 输入一行可能非常混乱的字符串，例如：
 *        "2009/03/02"
 *        "今天是2025年3月1日"
 *        "[2024]{12}31"
 *        "2025 //// 03 / 01"
 *
 *   - 不严格要求格式，也不验证分隔符，只从中“抓取整数序列”
 *
 *   - 提取出的整数序列形如：
 *        {2025, 3, 1}
 *
 *   - 使用前三个数分别当作 year / month / day
 *
 *   - 若整数数量不足 3 → 输出 "format problem"
 *   - 若日期非法 → 输出 "invalid date"
 *   - 否则格式化输出 YYYY-MM-DD
 */

vector<int> extractInts(const string& s) {
    vector<int> nums;
    int n = (int)s.size();
    int i = 0;

    while (i < n) {
        if (isdigit(static_cast<unsigned char>(s[i]))) {
            int val = 0;
            while (i < n && isdigit(static_cast<unsigned char>(s[i]))) {
                val = val * 10 + (s[i] - '0');
                ++i;
            }
            nums.push_back(val);
        } else ++i;
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
    if (m < 1 || m > 12) return false;
    int dim = daysInMonth(y, m);
    return d >= 1 && d <= dim;
}

int main() {
    string line;
    getline(cin, line);

    vector<int> nums = extractInts(line);
    if (nums.size() < 3) {
        cout << "format problem\n";
        return 0;
    }

    int y = nums[0], m = nums[1], d = nums[2];
    if (!validDate(y, m, d)) {
        cout << "invalid date\n";
        return 0;
    }

    cout << setfill('0')
         << setw(4) << y << "-"
         << setw(2) << m << "-"
         << setw(2) << d << "\n";

    return 0;
}
