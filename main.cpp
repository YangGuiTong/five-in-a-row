#include <iostream>
#include <Windows.h>
#include <graphics.h>	// 图形库
#include <vector>		// 动态数组，该地方用于悔棋
#include <mmsystem.h>	// 背景音乐

// 加载 winmm.lid库文件
#pragma comment(lib,"winmm.lib")


using namespace std;

#define GRAPHICS_X 880
#define GRAPHICS_Y 780

// 游戏棋板
#define PLATE_X	 30				//////
#define PLATE_Y  50				/////	棋盘的矩形的坐标值
#define PLATE_XX 50*14+PLATE_X	////
#define PLATE_YY 50*15			///
// 偏移量
#define	OFFSET   50	// 每个棋盘空格相隔50像素


typedef struct VECTOR {
	vector<int> x;
	vector<int> y;
};
// 悔棋标志
VECTOR pullBack;	// 记录棋盘上一下好的棋子的坐标，好用于悔棋



// 游戏初始化界面
void initgraphGame(void) {
	// 初始化图像界面
	initgraph(1080, 720);

	// 将图片应用于界面中
	loadimage(0, _T("begin-1.jpg"));

	// 设置字体颜色
	settextcolor(RGB(255, 255, 255));

	// 设置字体
	settextstyle(35, 0, _T("微软雅黑"));

	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	// 写字
	outtextxy(415, 60, _T("正在加载游戏...")); 

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 5);

	// 画一个空心矩形
	rectangle(220, 195, 820, 305);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(120, 0, _T("微软雅黑"));

	// 写字
	outtextxy(244, 190, _T("编程使我快乐")); 

	// 设置字体颜色
	settextcolor(RGB(255, 200, 88));

	// 写字
	outtextxy(110, 410, _T("欢迎进入五子棋游戏")); 

	Sleep(3000);
	closegraph();
}


// 游戏背景音乐
void music(void) {
	mciSendString("play Sunburst.mp3 repeat", 0, 0, 0);
}

// 背景音乐标识
bool gameMusicFlag = true;

// 游戏背景音乐开关
void musicFlag(void) {
	if (gameMusicFlag) {
		gameMusicFlag = false;
		mciSendString("pause Sunburst.mp3",NULL,0,NULL);	// 暂停
		//mciSendString("close Sunburst.mp3",NULL,0,NULL);	// 停止
	} else {
		gameMusicFlag = true;
		music();
	}
}



// 棋盘绘制
void plate(void) {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	for (int i=0; i<13; i++) {
		//	固定值加上一个偏移量
		line(PLATE_X, PLATE_Y+(OFFSET*(i+1)), PLATE_XX, PLATE_Y+(OFFSET*(i+1)));	// 行
		line(PLATE_X+(OFFSET*(i+1)), PLATE_Y, PLATE_X+(OFFSET*(i+1)), PLATE_YY);	// 纵
	}
}

// 游戏 开始 和 结束 和 悔棋 和 音乐开关 和 五子棋 绘制
void gameButton(void) {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 175, 850, 225);
	
	// 写字
	outtextxy(767, 185, _T("音乐开关")); 


	// 字体外的方框
	rectangle(760, 250, 850, 300);
	
	// 写字
	outtextxy(767, PLATE_Y*5+10, _T("开始游戏")); 

	// 字体外的方框
	rectangle(760, 450, 850, 500);

	// 写字
	outtextxy(767, 460, _T("结束游戏")); 

	// 字体外的方框
	rectangle(760, 650, 850, 700);

	// 写字
	outtextxy(785, 662, _T("悔棋")); 


	// 设置字体
	settextstyle(30, 0, _T("微软雅黑"));

	// 五子棋
	outtextxy(700/2, 10, _T("五子棋"));
}

// 开始游戏提示
void gameHints(void) {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(28, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 50, 850, 150);
	
	// 写字
	outtextxy(775, 65, _T("请点击")); 
	outtextxy(763, 100, _T("开始游戏")); 
}

// 清楚提示
void deleteHints(void) {
	IMAGE image;
	loadimage(&image, _T("cheng.jpg"));
	putimage(758, 48, &image);
}

// 游戏界面
void gameInterface(void) {
	// 初始化图像界面
	initgraph(GRAPHICS_X, GRAPHICS_Y);

	// 设置图像的背景颜色
	setbkcolor(RGB(255,200,88));
	// 应用到图像中
	cleardevice();

	// 设置画笔颜色
	setlinecolor(RGB(0,0,0));

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 3);

	// 画一个空心矩形
	rectangle(PLATE_X, PLATE_Y, PLATE_XX, PLATE_YY);

	// 画棋板
	plate();

	// 游戏按钮
	gameButton();

	// 开始游戏提示
	gameHints();
}

// 游戏选手
typedef struct PLAYER {
	int white;
	int black;
};
PLAYER player;	// 用于左上角提示选手下棋

// frame of reference 坐标
typedef struct FOR {
	int x;
	int y;
};
FOR fofr;	// 用于更新数组

// 鼠标坐标
typedef struct MOUSES {
	int x;
	int y;
};
MOUSES mouses;	// 用于下棋

int Map[15][15] = {		// int Map[15][15] = {0};
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


IMAGE imageBlack;	// 黑棋图片存储变量
IMAGE imageWhite;	// 白棋图片存储变量
// 游戏选手显示
void gamePlayerShow(void) {
	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体
	settextstyle(30, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(750, 40, 860, 160);
	
	// 清除提示
	deleteHints();

	if (player.white) {
		// 设置字体颜色
		settextcolor(RGB(255, 255, 255));

		// 写字
		outtextxy(780, 52, _T("白方")); 
		outtextxy(780, 80, _T("下棋"));

		// 预先加载图片
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);
		// 显示棋子
		putimage(790, 110, &imageWhite);

	} else if (player.black) {
		// 设置字体颜色
		settextcolor(RGB(0, 0, 0));

		// 写字
		outtextxy(780, 52, _T("黑方")); 
		outtextxy(780, 80, _T("下棋")); 

		// 预先加载图片
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);
		// 显示棋子
		putimage(790, 110, &imageBlack);

	} else {
		outtextxy(780, 52, _T("第三方")); 
		outtextxy(780, 80, _T("下棋")); 
	}
}



// 鼠标事件：点击开始游戏与退出游戏
bool beginGame(void) {
	MOUSEMSG mouse;	// 鼠标变量

	while (1) {
		mouse = GetMouseMsg();	// 调用系统的函数

		// 如果有鼠标左键点击操作
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
				return true;
			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
				return false;
			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
				musicFlag();	// 音乐控制
				continue;
			}
		}

		Sleep(10);
	}
}



// 重新开始游戏
void newGame(void) {
	// 重新开始游戏
	gameInterface();	// 初始化地图
	for (int i=0; i<15; i++) {	// 地图全部置为零
		for (int j=0; j<15; j++) {
			Map[i][j] = 0;
		}
	}

	// 重新开始游戏，将悔棋标志清空
	pullBack.x.clear();
	pullBack.y.capacity();

	// 重新开始游戏之后，恢复白棋先出
	player.black = 0;
	player.white = 1;
}



// 鼠标点击操作
int ifbool(void) {
	MOUSEMSG mouse;	// 鼠标变量

	while (1) {
		mouse = GetMouseMsg();	// 调用系统的函数

		// 如果有鼠标左键点击操作
		if (mouse.uMsg == WM_LBUTTONDOWN) {		// 下棋操作
			for (int i=0; i<15; i++) {
				for (int j=0; j<15; j++) {		// 判断鼠标的坐标是否在该区域
					if ((mouse.x >= i*50+PLATE_X-15 && mouse.x <= i*50+PLATE_X+15) &&
						(mouse.y >= j*50+PLATE_Y-15 && mouse.y <= j*50+PLATE_Y+15)) {

							// 等于零，该区域没有棋子
							if (Map[i][j] == 0) {
								fofr.x = i;		// 用于更新数组
								fofr.y = j;

								mouses.x = i*50+PLATE_X;	// 用于下棋
								mouses.y = j*50+PLATE_Y;

								pullBack.x.push_back(i);	// 用于悔棋
								pullBack.y.push_back(j);
								return 1;

							} else {
								return 2;
							}

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {	// 重新开始游戏
						newGame();	// 重新开始游戏函数
						return 3;

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 650 && mouse.y < 700)) {		// 悔棋操作
						if (pullBack.x.size() > 0 && pullBack.y.size() > 0) {	// 大于零，说明有棋子记录，可以悔棋
							int x = pullBack.x[pullBack.x.size()-1];
							int y = pullBack.y[pullBack.y.size()-1];

							// 删除容器上的一个悔棋记录
								pullBack.x.pop_back();
								pullBack.y.pop_back();

				

								Map[x][y] = 0;
								// 重新加载游戏
								gameInterface();	// 初始化地图

	
								for (int i=0; i<15; i++) {	// 将地图上的棋子摆回来
									for (int j=0; j<15; j++) {
										if (Map[i][j] == 1) {
											loadimage(&imageWhite, _T("white.jpg"), 30, 30);
											putimage(i*50+PLATE_X-15, j*50+PLATE_Y-15, &imageWhite);
				
										} else if (Map[i][j] == 2) {
											loadimage(&imageBlack, _T("black.jpg"), 30, 30);
											putimage(i*50+PLATE_X-15, j*50+PLATE_Y-15, &imageBlack);
											
										}
									}
								}

								if (player.black == 1) {
									player.black = 0;
									player.white = 1;
								} else {
									player.black = 1;
									player.white = 0;
								}
								return 4;
						}
						
					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {		// 推出游戏操作
						// 结束程序
						closegraph();
						exit(1);

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
						musicFlag();	// 音乐控制
						continue;
					} 
				}
			}
		}

		Sleep(10);
	}
}


// 下棋
void playChess(void) {
	
	if (player.black) { // 如果为真
		// 预先加载图片
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);
		// 将棋子下到棋板上面
		putimage(mouses.x-15, mouses.y-15, &imageBlack);
		player.black = 0;	// 下棋顺序标志
		player.white = 1;	// 下棋顺序标志
		Map[fofr.x][fofr.y] = 2;	// 更新数组
	} else {
		// 预先加载图片
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);
		// 将棋子下到棋板上面
		putimage(mouses.x-15, mouses.y-15, &imageWhite);
		player.black = 1;
		player.white = 0;
		Map[fofr.x][fofr.y] = 1;
	}
}

// 提示该处已有棋子
void hint(void) {
	// 清除提示
	deleteHints();

	// 设置画笔粗细
	setlinestyle(PS_SOLID, 2);

	// 设置字体颜色
	settextcolor(RGB(0, 0, 0));

	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));

	// 字体外的方框
	rectangle(760, 50, 850, 150);
	
	// 写字
	outtextxy(788, 52, _T("此处")); 
	outtextxy(768, 80, _T("已有棋子")); 


	// 确认 字体外的方框
	rectangle(765, 110, 845, 145);
	// 设置字体
	settextstyle(25, 0, _T("微软雅黑"));
	// 写字
	outtextxy(790, 115, _T("确认")); 


	MOUSEMSG mouse;	// 鼠标变量

	while (1) {
		mouse = GetMouseMsg();	// 调用系统的函数

		// 如果有鼠标左键点击操作
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 765 && mouse.x < 845) && (mouse.y > 90 && mouse.y < 145)) {
				// 清除提示
				deleteHints();
				break;

			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
						newGame();	// 重新开始游戏函数
						break;

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
						// 结束程序
						closegraph();
						exit(1);

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
						musicFlag();	// 音乐控制
						continue;
					}
		}

		Sleep(10);
	}
}


void playGames(void);
// 执行胜利界面
void Victory(int victory) {
	Sleep(300);
	//closegraph();
	//initgraph(680, 417);

	//IMAGE image;

	//// 加载图片
	//loadimage(&image, _T("timg.jpg"));
	//putimage(0, 0, &image);

	settextstyle(77, 0, _T("微软雅黑"));

	// 设置字体的背景颜色为透明
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("恭喜白棋获胜"));

	} else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("恭喜黑棋获胜"));

	} else {
		outtextxy(200, 150, _T("参数有问题！"));
	}


	// 点击开始游戏
	if (beginGame()) {
		newGame();	// 重新加载游戏

		// 玩游戏
		playGames();
	} else {
		closegraph();
		exit(1);
	}

	/*system("pause");
	closegraph();
	exit(1);*/
}

// 判断是否下完了五个一样的棋子
void ifVictory(void) {
	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {

			// 核心算法，游戏棋子判断
			if ((Map[i][j]==1 && Map[i-1][j-1]==1 && Map[i-2][j-2]==1 && Map[i-3][j-3]==1 && Map[i-4][j-4]==1) ||		// 左上角
				(Map[i][j]==1 && Map[i+1][j-1]==1 && Map[i+2][j-2]==1 && Map[i+3][j-3]==1 && Map[i+4][j-4]==1) ||		// 右上角
				(Map[i][j]==1 && Map[i-1][j+1]==1 && Map[i-2][j+2]==1 && Map[i-3][j+3]==1 && Map[i-4][j+4]==1) ||		// 左下角
				(Map[i][j]==1 && Map[i+1][j+1]==1 && Map[i+2][j+2]==1 && Map[i+3][j+3]==1 && Map[i+4][j+4]==1) ||		// 右下角
				(Map[i][j]==1 && Map[i][j-1]==1 && Map[i][j-2]==1 && Map[i][j-3]==1 && Map[i][j-4]==1) ||				// 上
				(Map[i][j]==1 && Map[i][j+1]==1 && Map[i][j+2]==1 && Map[i][j+3]==1 && Map[i][j+4]==1) ||				// 下
				(Map[i][j]==1 && Map[i-1][j]==1 && Map[i-2][j]==1 && Map[i-3][j]==1 && Map[i-4][j]==1) ||				// 左
				(Map[i][j]==1 && Map[i+1][j]==1 && Map[i+2][j]==1 && Map[i+3][j]==1 && Map[i+4][j]==1)) {				// 右
					Victory(1);	// 执行胜利代码

			} else if ((Map[i][j]==2 && Map[i-1][j-1]==2 && Map[i-2][j-2]==2 && Map[i-3][j-3]==2 && Map[i-4][j-4]==2) ||		// 左上角
					   (Map[i][j]==2 && Map[i+1][j-1]==2 && Map[i+2][j-2]==2 && Map[i+3][j-3]==2 && Map[i+4][j-4]==2) ||		// 右上角
					   (Map[i][j]==2 && Map[i-1][j+1]==2 && Map[i-2][j+2]==2 && Map[i-3][j+3]==2 && Map[i-4][j+4]==2) ||		// 左下角
				   	   (Map[i][j]==2 && Map[i+1][j+1]==2 && Map[i+2][j+2]==2 && Map[i+3][j+3]==2 && Map[i+4][j+4]==2) ||		// 右下角
					   (Map[i][j]==2 && Map[i][j-1]==2 && Map[i][j-2]==2 && Map[i][j-3]==2 && Map[i][j-4]==2) ||				// 上
					   (Map[i][j]==2 && Map[i][j+1]==2 && Map[i][j+2]==2 && Map[i][j+3]==2 && Map[i][j+4]==2) ||				// 下
					   (Map[i][j]==2 && Map[i-1][j]==2 && Map[i-2][j]==2 && Map[i-3][j]==2 && Map[i-4][j]==2) ||				// 左
					   (Map[i][j]==2 && Map[i+1][j]==2 && Map[i+2][j]==2 && Map[i+3][j]==2 && Map[i+4][j]==2)) {				// 右
							Victory(2);	// 执行胜利代码
			}
		}
	}
}

// 玩游戏
void playGames(void) {
	while (1) {
		gamePlayerShow();		// 选手下棋提示	

		int keyword = ifbool();	// 鼠标点击棋盘

		if (keyword == 1) {
			playChess();	// 下棋
			ifVictory();	// 判断是否下完了五个一样的棋子

		} else if (keyword == 2) {
			hint();			// 提示该处已有棋子

		} else if (keyword == 3) {
			// 已执行界面重新加载，清楚开始游戏提示
			deleteHints();
		} else if (keyword == 4) {
			// 已执行界面重新加载，清楚开始游戏提示
			deleteHints();
		}
	}
}



int main(void) {
	// 白色为1，白棋先出
	player.black = 0;
	player.white = 1;


	// 加载游戏
	initgraphGame();

	// 背景音乐
	music();

	// 游戏界面
	gameInterface();

	// 开始游戏
	if (beginGame()) {
		// 玩游戏
		playGames();
	}

	return 0;
}