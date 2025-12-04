# date-recognition-notes

Robust date extraction and parsing from messy text input.

这是一个围绕 **“日期识别与读取（宽松解析）”** 的小练习仓库。

目标是：即使输入格式非常乱，例如：

- `2009//03//02`
- `今天是 2025 年 3 月 1 日`
- `[2024]{12}月31日`
- `2025 ///// 03 // 01`

程序也能从中 **识别出我们想要的年月日 / 时间**，并完成后续计算或排序。

---

## 1. 文件说明

放三个 `.cpp` 文件在仓库根目录：

```text
.
├─ README.md                         # 本说明文件
├─ mother_loose_date_parse.cpp       # 母题：宽松解析日期，打印年月日
├─ extend_day_of_year.cpp            # 拓展 1：宽松日期 + 计算当年的第几天
└─ extend_event_timeline.cpp         # 拓展 2：宽松日志 + 时间线排序
