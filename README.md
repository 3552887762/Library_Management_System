# Library_Management_System
图书管理系统课设是一项经典的C语言实践项目，通过该项目可以熟悉结构体、指针、文件操作等C语言核心功能，同时结合easyX库实现简单的图形用户界面（GUI），增强用户交互体验。

我们需要将，此处的文件路径改为我们自己电脑的文件路径：

**加载图片**
```C++
loadimage(&img1, "D:\\c++实验\\C++图书管理系统\\登录页面.jpg", 640, 480, true);
loadimage(&img2, "D:\\c++实验\\C++图书管理系统\\界面.png", 640, 480, true);
```

当然我们可以自己增加音乐，只需要在对应路径传入mp3即可
```C++
//播放音乐
while (1) {
	msg = GetMouseMsg();
	//播放音乐
	if (msg.uMsg == WM_LBUTTONDOWN && msg.x > 90 && msg.x < 134 && msg.y>186 && msg.y < 318) {
		mciSendString("open C:\\Users\\Desktop\\1.mp3 alias m", 0, 0, 0);
		mciSendString("play m repeat", 0, 0, 0);//开始播放音乐，repeat重复播
		break;
	}
}
```

我们也可以根据自己的图片来进行修改

我们界面的操作，需要根据图片上按钮的像素点坐标来修改，需要我们自己在本地终端进行修改优化

**如何对页面的按钮进行优化**
```C++
 (msg.uMsg == WM_LBUTTONDOWN && msg.x > 400 && msg.x < 500 && msg.y > 300 && msg.y < 400) 
```
