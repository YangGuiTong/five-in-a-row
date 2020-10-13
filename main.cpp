#include <iostream>
#include <Windows.h>
#include <graphics.h>	// ͼ�ο�
#include <vector>		// ��̬���飬�õط����ڻ���
#include <mmsystem.h>	// ��������

// ���� winmm.lid���ļ�
#pragma comment(lib,"winmm.lib")


using namespace std;

#define GRAPHICS_X 880
#define GRAPHICS_Y 780

// ��Ϸ���
#define PLATE_X	 30				//////
#define PLATE_Y  50				/////	���̵ľ��ε�����ֵ
#define PLATE_XX 50*14+PLATE_X	////
#define PLATE_YY 50*15			///
// ƫ����
#define	OFFSET   50	// ÿ�����̿ո����50����


typedef struct VECTOR {
	vector<int> x;
	vector<int> y;
};
// �����־
VECTOR pullBack;	// ��¼������һ�ºõ����ӵ����꣬�����ڻ���



// ��Ϸ��ʼ������
void initgraphGame(void) {
	// ��ʼ��ͼ�����
	initgraph(1080, 720);

	// ��ͼƬӦ���ڽ�����
	loadimage(0, _T("begin-1.jpg"));

	// ����������ɫ
	settextcolor(RGB(255, 255, 255));

	// ��������
	settextstyle(35, 0, _T("΢���ź�"));

	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	// д��
	outtextxy(415, 60, _T("���ڼ�����Ϸ...")); 

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 5);

	// ��һ�����ľ���
	rectangle(220, 195, 820, 305);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(120, 0, _T("΢���ź�"));

	// д��
	outtextxy(244, 190, _T("���ʹ�ҿ���")); 

	// ����������ɫ
	settextcolor(RGB(255, 200, 88));

	// д��
	outtextxy(110, 410, _T("��ӭ������������Ϸ")); 

	Sleep(3000);
	closegraph();
}


// ��Ϸ��������
void music(void) {
	mciSendString("play Sunburst.mp3 repeat", 0, 0, 0);
}

// �������ֱ�ʶ
bool gameMusicFlag = true;

// ��Ϸ�������ֿ���
void musicFlag(void) {
	if (gameMusicFlag) {
		gameMusicFlag = false;
		mciSendString("pause Sunburst.mp3",NULL,0,NULL);	// ��ͣ
		//mciSendString("close Sunburst.mp3",NULL,0,NULL);	// ֹͣ
	} else {
		gameMusicFlag = true;
		music();
	}
}



// ���̻���
void plate(void) {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	for (int i=0; i<13; i++) {
		//	�̶�ֵ����һ��ƫ����
		line(PLATE_X, PLATE_Y+(OFFSET*(i+1)), PLATE_XX, PLATE_Y+(OFFSET*(i+1)));	// ��
		line(PLATE_X+(OFFSET*(i+1)), PLATE_Y, PLATE_X+(OFFSET*(i+1)), PLATE_YY);	// ��
	}
}

// ��Ϸ ��ʼ �� ���� �� ���� �� ���ֿ��� �� ������ ����
void gameButton(void) {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 175, 850, 225);
	
	// д��
	outtextxy(767, 185, _T("���ֿ���")); 


	// ������ķ���
	rectangle(760, 250, 850, 300);
	
	// д��
	outtextxy(767, PLATE_Y*5+10, _T("��ʼ��Ϸ")); 

	// ������ķ���
	rectangle(760, 450, 850, 500);

	// д��
	outtextxy(767, 460, _T("������Ϸ")); 

	// ������ķ���
	rectangle(760, 650, 850, 700);

	// д��
	outtextxy(785, 662, _T("����")); 


	// ��������
	settextstyle(30, 0, _T("΢���ź�"));

	// ������
	outtextxy(700/2, 10, _T("������"));
}

// ��ʼ��Ϸ��ʾ
void gameHints(void) {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(28, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 50, 850, 150);
	
	// д��
	outtextxy(775, 65, _T("����")); 
	outtextxy(763, 100, _T("��ʼ��Ϸ")); 
}

// �����ʾ
void deleteHints(void) {
	IMAGE image;
	loadimage(&image, _T("cheng.jpg"));
	putimage(758, 48, &image);
}

// ��Ϸ����
void gameInterface(void) {
	// ��ʼ��ͼ�����
	initgraph(GRAPHICS_X, GRAPHICS_Y);

	// ����ͼ��ı�����ɫ
	setbkcolor(RGB(255,200,88));
	// Ӧ�õ�ͼ����
	cleardevice();

	// ���û�����ɫ
	setlinecolor(RGB(0,0,0));

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 3);

	// ��һ�����ľ���
	rectangle(PLATE_X, PLATE_Y, PLATE_XX, PLATE_YY);

	// �����
	plate();

	// ��Ϸ��ť
	gameButton();

	// ��ʼ��Ϸ��ʾ
	gameHints();
}

// ��Ϸѡ��
typedef struct PLAYER {
	int white;
	int black;
};
PLAYER player;	// �������Ͻ���ʾѡ������

// frame of reference ����
typedef struct FOR {
	int x;
	int y;
};
FOR fofr;	// ���ڸ�������

// �������
typedef struct MOUSES {
	int x;
	int y;
};
MOUSES mouses;	// ��������

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


IMAGE imageBlack;	// ����ͼƬ�洢����
IMAGE imageWhite;	// ����ͼƬ�洢����
// ��Ϸѡ����ʾ
void gamePlayerShow(void) {
	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ��������
	settextstyle(30, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(750, 40, 860, 160);
	
	// �����ʾ
	deleteHints();

	if (player.white) {
		// ����������ɫ
		settextcolor(RGB(255, 255, 255));

		// д��
		outtextxy(780, 52, _T("�׷�")); 
		outtextxy(780, 80, _T("����"));

		// Ԥ�ȼ���ͼƬ
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);
		// ��ʾ����
		putimage(790, 110, &imageWhite);

	} else if (player.black) {
		// ����������ɫ
		settextcolor(RGB(0, 0, 0));

		// д��
		outtextxy(780, 52, _T("�ڷ�")); 
		outtextxy(780, 80, _T("����")); 

		// Ԥ�ȼ���ͼƬ
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);
		// ��ʾ����
		putimage(790, 110, &imageBlack);

	} else {
		outtextxy(780, 52, _T("������")); 
		outtextxy(780, 80, _T("����")); 
	}
}



// ����¼��������ʼ��Ϸ���˳���Ϸ
bool beginGame(void) {
	MOUSEMSG mouse;	// ������

	while (1) {
		mouse = GetMouseMsg();	// ����ϵͳ�ĺ���

		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
				return true;
			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
				return false;
			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
				musicFlag();	// ���ֿ���
				continue;
			}
		}

		Sleep(10);
	}
}



// ���¿�ʼ��Ϸ
void newGame(void) {
	// ���¿�ʼ��Ϸ
	gameInterface();	// ��ʼ����ͼ
	for (int i=0; i<15; i++) {	// ��ͼȫ����Ϊ��
		for (int j=0; j<15; j++) {
			Map[i][j] = 0;
		}
	}

	// ���¿�ʼ��Ϸ���������־���
	pullBack.x.clear();
	pullBack.y.capacity();

	// ���¿�ʼ��Ϸ֮�󣬻ָ������ȳ�
	player.black = 0;
	player.white = 1;
}



// ���������
int ifbool(void) {
	MOUSEMSG mouse;	// ������

	while (1) {
		mouse = GetMouseMsg();	// ����ϵͳ�ĺ���

		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {		// �������
			for (int i=0; i<15; i++) {
				for (int j=0; j<15; j++) {		// �ж����������Ƿ��ڸ�����
					if ((mouse.x >= i*50+PLATE_X-15 && mouse.x <= i*50+PLATE_X+15) &&
						(mouse.y >= j*50+PLATE_Y-15 && mouse.y <= j*50+PLATE_Y+15)) {

							// �����㣬������û������
							if (Map[i][j] == 0) {
								fofr.x = i;		// ���ڸ�������
								fofr.y = j;

								mouses.x = i*50+PLATE_X;	// ��������
								mouses.y = j*50+PLATE_Y;

								pullBack.x.push_back(i);	// ���ڻ���
								pullBack.y.push_back(j);
								return 1;

							} else {
								return 2;
							}

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {	// ���¿�ʼ��Ϸ
						newGame();	// ���¿�ʼ��Ϸ����
						return 3;

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 650 && mouse.y < 700)) {		// �������
						if (pullBack.x.size() > 0 && pullBack.y.size() > 0) {	// �����㣬˵�������Ӽ�¼�����Ի���
							int x = pullBack.x[pullBack.x.size()-1];
							int y = pullBack.y[pullBack.y.size()-1];

							// ɾ�������ϵ�һ�������¼
								pullBack.x.pop_back();
								pullBack.y.pop_back();

				

								Map[x][y] = 0;
								// ���¼�����Ϸ
								gameInterface();	// ��ʼ����ͼ

	
								for (int i=0; i<15; i++) {	// ����ͼ�ϵ����Ӱڻ���
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
						
					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {		// �Ƴ���Ϸ����
						// ��������
						closegraph();
						exit(1);

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
						musicFlag();	// ���ֿ���
						continue;
					} 
				}
			}
		}

		Sleep(10);
	}
}


// ����
void playChess(void) {
	
	if (player.black) { // ���Ϊ��
		// Ԥ�ȼ���ͼƬ
		loadimage(&imageBlack, _T("black.jpg"), 30, 30);
		// �������µ��������
		putimage(mouses.x-15, mouses.y-15, &imageBlack);
		player.black = 0;	// ����˳���־
		player.white = 1;	// ����˳���־
		Map[fofr.x][fofr.y] = 2;	// ��������
	} else {
		// Ԥ�ȼ���ͼƬ
		loadimage(&imageWhite, _T("white.jpg"), 30, 30);
		// �������µ��������
		putimage(mouses.x-15, mouses.y-15, &imageWhite);
		player.black = 1;
		player.white = 0;
		Map[fofr.x][fofr.y] = 1;
	}
}

// ��ʾ�ô���������
void hint(void) {
	// �����ʾ
	deleteHints();

	// ���û��ʴ�ϸ
	setlinestyle(PS_SOLID, 2);

	// ����������ɫ
	settextcolor(RGB(0, 0, 0));

	// ��������
	settextstyle(25, 0, _T("΢���ź�"));

	// ������ķ���
	rectangle(760, 50, 850, 150);
	
	// д��
	outtextxy(788, 52, _T("�˴�")); 
	outtextxy(768, 80, _T("��������")); 


	// ȷ�� ������ķ���
	rectangle(765, 110, 845, 145);
	// ��������
	settextstyle(25, 0, _T("΢���ź�"));
	// д��
	outtextxy(790, 115, _T("ȷ��")); 


	MOUSEMSG mouse;	// ������

	while (1) {
		mouse = GetMouseMsg();	// ����ϵͳ�ĺ���

		// ������������������
		if (mouse.uMsg == WM_LBUTTONDOWN) {
			if ((mouse.x > 765 && mouse.x < 845) && (mouse.y > 90 && mouse.y < 145)) {
				// �����ʾ
				deleteHints();
				break;

			} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 250 && mouse.y < 300)) {
						newGame();	// ���¿�ʼ��Ϸ����
						break;

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 450 && mouse.y < 500)) {
						// ��������
						closegraph();
						exit(1);

					} else if ((mouse.x > 760 && mouse.x < 850) && (mouse.y > 175 && mouse.y < 225)) {
						musicFlag();	// ���ֿ���
						continue;
					}
		}

		Sleep(10);
	}
}


void playGames(void);
// ִ��ʤ������
void Victory(int victory) {
	Sleep(300);
	//closegraph();
	//initgraph(680, 417);

	//IMAGE image;

	//// ����ͼƬ
	//loadimage(&image, _T("timg.jpg"));
	//putimage(0, 0, &image);

	settextstyle(77, 0, _T("΢���ź�"));

	// ��������ı�����ɫΪ͸��
	setbkmode(TRANSPARENT);

	if (victory == 1) {
		settextcolor(RGB(255, 255, 255));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));

	} else if (victory == 2) {
		settextcolor(RGB(0, 0, 0));
		outtextxy(180, 150, _T("��ϲ�����ʤ"));

	} else {
		outtextxy(200, 150, _T("���������⣡"));
	}


	// �����ʼ��Ϸ
	if (beginGame()) {
		newGame();	// ���¼�����Ϸ

		// ����Ϸ
		playGames();
	} else {
		closegraph();
		exit(1);
	}

	/*system("pause");
	closegraph();
	exit(1);*/
}

// �ж��Ƿ����������һ��������
void ifVictory(void) {
	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {

			// �����㷨����Ϸ�����ж�
			if ((Map[i][j]==1 && Map[i-1][j-1]==1 && Map[i-2][j-2]==1 && Map[i-3][j-3]==1 && Map[i-4][j-4]==1) ||		// ���Ͻ�
				(Map[i][j]==1 && Map[i+1][j-1]==1 && Map[i+2][j-2]==1 && Map[i+3][j-3]==1 && Map[i+4][j-4]==1) ||		// ���Ͻ�
				(Map[i][j]==1 && Map[i-1][j+1]==1 && Map[i-2][j+2]==1 && Map[i-3][j+3]==1 && Map[i-4][j+4]==1) ||		// ���½�
				(Map[i][j]==1 && Map[i+1][j+1]==1 && Map[i+2][j+2]==1 && Map[i+3][j+3]==1 && Map[i+4][j+4]==1) ||		// ���½�
				(Map[i][j]==1 && Map[i][j-1]==1 && Map[i][j-2]==1 && Map[i][j-3]==1 && Map[i][j-4]==1) ||				// ��
				(Map[i][j]==1 && Map[i][j+1]==1 && Map[i][j+2]==1 && Map[i][j+3]==1 && Map[i][j+4]==1) ||				// ��
				(Map[i][j]==1 && Map[i-1][j]==1 && Map[i-2][j]==1 && Map[i-3][j]==1 && Map[i-4][j]==1) ||				// ��
				(Map[i][j]==1 && Map[i+1][j]==1 && Map[i+2][j]==1 && Map[i+3][j]==1 && Map[i+4][j]==1)) {				// ��
					Victory(1);	// ִ��ʤ������

			} else if ((Map[i][j]==2 && Map[i-1][j-1]==2 && Map[i-2][j-2]==2 && Map[i-3][j-3]==2 && Map[i-4][j-4]==2) ||		// ���Ͻ�
					   (Map[i][j]==2 && Map[i+1][j-1]==2 && Map[i+2][j-2]==2 && Map[i+3][j-3]==2 && Map[i+4][j-4]==2) ||		// ���Ͻ�
					   (Map[i][j]==2 && Map[i-1][j+1]==2 && Map[i-2][j+2]==2 && Map[i-3][j+3]==2 && Map[i-4][j+4]==2) ||		// ���½�
				   	   (Map[i][j]==2 && Map[i+1][j+1]==2 && Map[i+2][j+2]==2 && Map[i+3][j+3]==2 && Map[i+4][j+4]==2) ||		// ���½�
					   (Map[i][j]==2 && Map[i][j-1]==2 && Map[i][j-2]==2 && Map[i][j-3]==2 && Map[i][j-4]==2) ||				// ��
					   (Map[i][j]==2 && Map[i][j+1]==2 && Map[i][j+2]==2 && Map[i][j+3]==2 && Map[i][j+4]==2) ||				// ��
					   (Map[i][j]==2 && Map[i-1][j]==2 && Map[i-2][j]==2 && Map[i-3][j]==2 && Map[i-4][j]==2) ||				// ��
					   (Map[i][j]==2 && Map[i+1][j]==2 && Map[i+2][j]==2 && Map[i+3][j]==2 && Map[i+4][j]==2)) {				// ��
							Victory(2);	// ִ��ʤ������
			}
		}
	}
}

// ����Ϸ
void playGames(void) {
	while (1) {
		gamePlayerShow();		// ѡ��������ʾ	

		int keyword = ifbool();	// ���������

		if (keyword == 1) {
			playChess();	// ����
			ifVictory();	// �ж��Ƿ����������һ��������

		} else if (keyword == 2) {
			hint();			// ��ʾ�ô���������

		} else if (keyword == 3) {
			// ��ִ�н������¼��أ������ʼ��Ϸ��ʾ
			deleteHints();
		} else if (keyword == 4) {
			// ��ִ�н������¼��أ������ʼ��Ϸ��ʾ
			deleteHints();
		}
	}
}



int main(void) {
	// ��ɫΪ1�������ȳ�
	player.black = 0;
	player.white = 1;


	// ������Ϸ
	initgraphGame();

	// ��������
	music();

	// ��Ϸ����
	gameInterface();

	// ��ʼ��Ϸ
	if (beginGame()) {
		// ����Ϸ
		playGames();
	}

	return 0;
}