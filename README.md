# date-recognition-notes

Robust date extraction and parsing from messy text input.

This repo is a small side project where I play with **“loose” date parsing** in C++.  
Nothing too serious – just notes, experiments, and some code I’d like to keep around.

The idea is simple:

> Even if the input format is messy, I still want to reliably extract `year / month / day` (and maybe time).

Examples:

- `2009//03//02`
- `Today is 2025-3-1`
- `[2024]{12}月31日`
- `2025 ///// 03 // 01`

---

## Files

```text
.
├─ README.md                         # this file
├─ main_loose_date_parse.cpp         # main problem: loose date parsing
├─ ext1_loose_date_day_of_year.cpp   # extension 1: day-of-year calculation
└─ ext2_loose_date_event_timeline.cpp# extension 2: event log timeline sorting
```

## Notes

Each file focuses on one small idea.
Nothing huge — just tiny building blocks that help me practice messy-input parsing,
date validation, struct design, and a bit of "mini engineering" taste.

Honestly, this repo is more like a personal playground:
a place to try ideas, break things, fix them again, and slowly collect small utilities
that might be useful someday… or maybe never — which is also fine.

I’ll probably keep adding small experiments whenever I feel like it :)
