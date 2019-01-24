#ifndef _H_MAIN
#define _H_MAIN

const double PI   = 3.1515;

const int radius = 200;

const int GAME_BORDER = 5;

const int GAME_WIDTH  = (radius + GAME_BORDER) * 2;
const int GAME_HEIGHT = (radius + GAME_BORDER) * 2;

const int CIRCLE_WIDTH = 5;

const int xOffset = radius + GAME_BORDER;
const int yOffset = radius + GAME_BORDER;

const DWORD WINDOW_STYLE = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

#endif