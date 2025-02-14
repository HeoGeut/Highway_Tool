#include "./RAD/Cru_HEADER.h"

    #define WIN32
    #define DLL_EXPORTS

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 외부참조 전역변수

//●●●●●●●
extern CRITICAL_SECTION core_CS;                 // core 동기화用, 크리티칼 섹션

extern Cru_THR *core_RUN;                        // core 쓰레드                .
//●●●●●●●

extern Cru_SYSTEM xSYS;                          // 시스템   개체              .

extern Cru_SCRiPT xSCR;                          // 스크립트 개체              .

extern CRITICAL_SECTION core_CS;                 // core 동기화用, 크리티칼 섹션
extern Cru_THR          *core_RUN;               // core 쓰레드                .

extern int zFiNDiNG;                             // 검색중 플랙
extern int FiNDiNG_LOOPcnt;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
Cru_THR::Cru_THR(bool CreateSuspended) : TThread(CreateSuspended) { }
//==============================================================================
void __fastcall Cru_THR::Execute(void)
{
    do
    {


        if(xSYS.FLAG[f_QUiT]) return;
        //■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■
        /*                                       */
        /* 크리티칼섹션 진입                     */
        /*                                       */
        /**/  EnterCriticalSection(&core_CS);  /**/
        /*                                       */
        //▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤

            //■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
            // 커널 클럭 제너레이터
            xSYS.KERNEL_CLOCK_Generator();


                    //▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩
                  //▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩ .
                  /**/  DBG_sQ();  /**/
                  /*                 */

                  // ▣ Core 루프
//                      Synchronize(&Core);

                  Core();

                                                       /*                 */
                                                       /**/  DBG_eQ();  /**/
                  //▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩ .
                    //▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩  ▩


            // 프레임 속도계산
//            xSYS.FPS_CALC();

            //■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

        //▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤
        /*                                       */
        /* 크리티칼섹션 탈출                     */
        /*                                       */
        /**/  LeaveCriticalSection(&core_CS);  /**/
        /*                                       */
        //■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■

// 모듈러 멀티플렉시브 딜레이
if(xSYS.clk%16==000)
{
Sleep(1);
}

    } while(!xSYS.FLAG[f_QUiT]);
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void __fastcall Cru_THR::Core(void)
{
    //  □■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□ .
    //□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□

        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
        // ▣ 섹터 - 1 ▣

Sector_1:

if(zFiNDiNG)
{
    if(xSYS.tm_MAiN.Reach())
    {
        FiNDiNG_LOOPcnt = (FiNDiNG_LOOPcnt<003)? FiNDiNG_LOOPcnt+1 : 000;

        switch(FiNDiNG_LOOPcnt)
        {
        case 000: PGM->uFiND_STAT->Caption = "검색중";     break;
        case 001: PGM->uFiND_STAT->Caption = "검색중 .";   break;
        case 002: PGM->uFiND_STAT->Caption = "검색중 ..";  break;
        case 003: PGM->uFiND_STAT->Caption = "검색중 ..."; break;
        }

        PGM->uFiND_STAT->Repaint();
    }
}

        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
        //▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩

    //□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□
    //  □■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□ .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.

