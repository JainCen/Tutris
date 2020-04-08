#include "tutrisdemo.h"
extern HANDLE  output;


BLOCK     bl = {BACKGROUND_GREEN, 0, 0};
BMANAGER  bm = {0, -1, &bl};
GMANAGER  gameManager;

static  int delayTime[11] = {
    1000, 900, 800, 700, 600, 500, 400, 300, 200, 100, 50
};

int  getDelay()
{
    return delayTime[gameManager.level];
}

void* openMusic(void* arg)
{
    PlaySound("./data/groundmusic/1.wav",
            NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);


    return (void*)0;
}

//void* openMusic2(void* arg)
//{
//
//    mciSendString("play ./data/groundmusic/9586.wav",NULL,0,NULL);
//   // mciSendString(TEXT("mysong"),NULL,0,NULL);
//    Sleep(10000);
//
//
//    return (void*)0;
//}
//void* showTime(void* arg)
//{
//
//    int ttime = 0 ;
//    while(1)
//    {
//
//        Sleep(1000);
//        setPosition(12,5);
//        SetConsoleTextAttribute(output,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
//        printf("%d",ttime++);
//
//    }
//
//
//    return (void*)0;
//
//}

void* thread_fun(void* arg)
{
    while(1){
        Sleep(getDelay());
        if(isPause()){
            continue;
        }
        else move_down(&bm);
    }
    return (void*)0;
}

int main()
{
    //��ʼ����׼������
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    //print_block(bm.pbi);

    //1��������Ϸ����(��ȫ�����������)
    //    ���췽������߶��󣨷�����Ϣ����
    //2����ʼ����Ϸ����
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(output, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = 0; //���ؿ���̨���
    SetConsoleCursorInfo(output, &CursorInfo);//���ÿ���̨���״̬

    showMenu();
    starttime = clock();
    initGameManager(&gameManager);
    gameManager.pbm = &bm;
    bm.pbi->color = MColor[rand()%7];
    bm.pbi->group = rand()%GROUPS;
    bm.pbi->status = rand()%STATUS;
    gameManager.Ti.blockCounter[bm.pbi->group]++;
    //3��������Ϸ
    showNextblock();
    startGame("./data/loadhistory/ranking.bat");
    extern BOOL islock ;
    print_block(&bl);
    showInfo();
    pthread_t  tid,tm,showmerry;
    pthread_create(&tid, NULL, thread_fun, NULL);
    pthread_create(&tm,NULL,openMusic,NULL);

    //pthread_create(&showmerry,NULL,showSuppermarry,NULL);
    //pthread_create(&tm2,NULL,openMusic2,NULL);

    showAllcount();
    char ch;
    while(1){
        if(islock) ch = getch();
        switch(ch){
            case 'a': // left
            case '4':
            case 75:
            {
                if(!isPause())
                    move_left(&bm);
            }
                break;
            case 'w':
            case '8':
            case 72:  // up
            {
                if(!isPause())
                    turnAround(&bm);
            }
                break;
            case 'd':
            case '6':
            case 77:  //right
            {
                if(!isPause())
                    move_right(&bm);
            }
                break;
            case 's':
            case '2':
            case 80:  //down
            {
                if(!isPause())
                    move_down(&bm);
            }
                break;
            case ' ':
            {
                if(!isPause())
                    fallDown(&bm);
            }
                break;
//            case '\n':
            case 13:
            {
                if(isPause())
                    gameManager.status = 0;
                else
                    gameManager.status = 1;
            }
                break;
            case 'q':
                exit(0);
                break;
            default:
                break;
        }
    }



    getchar();
    return 0;
}








