#pragma once
#include <windowsx.h> 
#include <windows.h> 
#include <time.h>
#include <tchar.h>  

#define DEFTIMER1 123
#define main_W 320
#define main_H 480
#define nW 16
#define nH 24


void paintblock(HDC gdc);
void OnPrint(HDC hdc);
void paint(HDC gdc);
void onTimer(HWND hwnd);
void killTime(HWND hwnd);
void ontime(HWND h);


void init();
void create_block();


bool islow();
bool isfull();
void block_down();
void block_left();
void block_right();
void block_spin();


bool impact();
bool impact_l();
bool impact_r();
bool impact_s();
