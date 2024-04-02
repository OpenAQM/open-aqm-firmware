#pragma once

enum Button {
    // Every button must have an id in the range of 0 to BTN_NUMBER-1
    BUTTON_SELECT = 0,
    // Historical reasons (will be removed in the future!) ↓
    BUTTON_1 = 0,
};

extern const char* ButtonNames[];