#pragma once

#ifndef __Cru_SYSTEM_H
#define __Cru_SYSTEM_H

// Pre-Compiled 헤더링크
//#include "./RAD/Pre_Compiled.h"

    #include "./RAD/Cru_DEFiNE.h"

    #include "./RAD/Sys_DEBUG.h"
    #include "./RAD/Sys_PARSiNG.h"
    #include "./RAD/Sys_TiMER.h"

    #include "./RAD/Cru_SCRiPT.h"

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 시스템 클래스
class Cru_SYSTEM
{
public:

    /* 플랙 */
    int FLAG[MAX_FLAG];                          // 상태플랙 메모리            .

    /* 디렉토리 */
    char runDiR[256],                            // PGM 실행 - 현재경로        .
         resDiR[256];                            // 리소스   - 경로            .

    /* 스크립트 */
    int zALREADY_Kernel_iSQrun,                  // Kernel.iSQ 를 이미 해독인지 플랙
        zALREADY_Game_iSQrun,                    // Game.iSQ   를 이미 해독인지 플랙
        zEventSKiP_iSQrun;                       // 이벤트내용 인가 ? 플랙

                                                 //                            .
    char SystemSCR_FiLE[256];                    // 시스템 설정파일            .
                                                 //                            .

    int zGOOGLE_Link;                            // 구글연결 플랙

    /* 타이밍 */
                                                 //=====================================
    Cru_TiCK tm_MAiN;                            // 메인커널 Tick                      .
    int clk,                                     // 메인커널클럭                       .
        FLiPFLOP,                                // 메인커널클럭   플립플롭            .
        rCLKdir;                                 // 메인커널클럭用 플립플롭 다이렉션   .
                                                 //=====================================
    int tm_FLiPFLOP,                             // 순차커널틱   플립플롭 카운터       .
        tm_rCLKdir;                              // 순차커널틱用 플립플롭 다이렉션     .
                                                 //=====================================
    ///////
    Cru_SYSTEM() { };
    ~Cru_SYSTEM() { };

    void Reset(void);                            // 시스템 리셋                .

        void SET_DiRECTORY(void);                // 디렉토리 정의              .
        void KERNEL_CLOCK_Generator(void);       // 커널클럭 - 제너레이터      .

        char *sYMDHMS(void);                     // 현재날짜와 시각을 문자열로 리턴 (표준출력用)
        char *fYMDHMS(void);                     // 현재날짜와 시각을 문자열로 리턴 (파일스펙用)

    ///////
};
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
#endif

