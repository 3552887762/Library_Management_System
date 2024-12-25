#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include "book.h"
#pragma comment(lib,"winmm.lib")
void Start(Library* lib){
		IMAGE img1,img2;
		loadimage(&img1, "D:\\c++实验\\C++图书管理系统\\登录页面.jpg", 640, 480, true);
		loadimage(&img2, "D:\\c++实验\\C++图书管理系统\\界面.png", 640, 480, true);
	putimage(0, 0, &img1);
	MOUSEMSG msg;
	//播放音乐
	//while (1) {
	//	msg = GetMouseMsg();
	//	//播放音乐
	//	if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 90 && msg.x < 134 && msg.y>186 && msg.y < 318) {
	//		mciSendString("open C:\\Users\\Desktop\\1.mp3 alias m", 0, 0, 0);
	//		mciSendString("play m repeat", 0, 0, 0);//开始播放音乐，repeat重复播
	//		break;
	//	}
	//}

	while(1){
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 500 && msg.y > 300 && msg.y < 400) {
			char c[20] = { 0 };
			InputBox(c,10, "用户名id:", "登录");
			char d[20] = { 0 };
			InputBox(d,10, "密码passwd", "登录");
			if(!strcmp(c,"123")&&!strcmp(d,"123")) {
				MessageBox(NULL,"登录成功!!!","登录",MB_OKCANCEL);
				//进入到下一个界面
						putimage(0, 0, &img2);
						break;
					}
			else {
				MessageBox(NULL, "密码账号输入错误\n登录失败", "登录结果", MB_OKCANCEL);
			}
		}
	}
			//printf("%d %d",msg.x,msg.y);
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 15 && msg.x < 150 && msg.y>83 && msg.y < 135) {

			InsertTail(lib);//	//点击上架图书
		}
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 0 && msg.x < 100 && msg.y>0 && msg.y < 100) {
			Show(lib);//显示全部图书
		}
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 15 && msg.x < 150 && msg.y>210 && msg.y < 260) {
			//printf("%d %d",msg.x,msg.y);
			Delete(lib);//下架图书
		}
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 500 && msg.x < 640 && msg.y>110 && msg.y < 166) {
			Search(lib);//查找
		}
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 500 && msg.x < 640 && msg.y>210 && msg.y < 260) {
			Change(lib);//更改
		}
		else if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 270 && msg.x < 400 && msg.y>150 && msg.y < 200) {
			MessageBox(NULL, "退出", "图书管理", MB_OK);
			break;
		}
	}
}
int main(){
	Library library;
	Book book;
	InitLibrary(&library);
	initgraph(640,480,SHOWCONSOLE);
	//=========
	Start(&library);
	//===================
	system("pause");
	closegraph();
}
#endif