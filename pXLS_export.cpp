#pragma link "AdvGrid"
#pragma link "AdvGridWorkbook"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "tmsAdvGridExcel"
#include <vcl.h>
#pragma hdrstop

#include "./RAD/Cru_HEADER.h"
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma resource "*.dfm"
//==============================================================================
TpEXCEL_export *pEXCEL_export;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 외부참조 / 전역변수

Cru_SYSTEM xSYS;                                 // 시스템 개체                .

Cru_SCRiPT xSCR;                                 // 스크립트 개체              .

//▩▩▩▩▩▩▩▩▩▩
extern int  Main_TBL_FNOs[1000];                       // 메인테이블 필드번호 리스트
extern int  Main_TBL_AVLs[1000];                       // 메인테이블 표시여부 리스트
extern int  Main_TBL_CLWs[1000];                       // 메인테이블 폭길이 리스트
extern char Main_TBL_FLDs[1000][64];                   // 메인테이블 영문필드이름
extern char Main_TBL_NMEs[1000][64];                   // 메인테이블 한글필드이름
extern int  Main_TBL_Field_CNT;                        // 메인테이블 필드개수
///////
extern int  Main_TBL_DEFAULTs[1000];                   // 메인테이블 디폴트필드 필드번호 리스트
extern int  Main_TBL_DEFAULTs_FLDcnt;                  // 메인테이블 디폴트필드 개수
///////
extern int  Main_TBL_SAVEs[1000];                      // 메인테이블 저장필드 필드번호 리스트
extern int  Main_TBL_SaveCLWs[1000];                   // 메인테이블 저장 폭길이 리스트
extern int  Main_TBL_SAVEs_FLDcnt;                     // 메인테이블 저장필드 개수
//▩▩▩▩▩▩▩▩▩▩

extern int Export_SELcnt;
extern int Export_ALLcnt;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
__fastcall TpEXCEL_export::TpEXCEL_export(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_export::uBTN_XLS_export_SaveClick(TObject *Sender)
{
    int n,p,k;
    int x,y,Jx,Jy;
    int chk,cnt,COLcnt,ROWcnt;
    int zSEL;

    UnicodeString dSTR, fSTR;
    //                                                                         .
    // 엑셀 익스포팅 - 파일저장 다이얼로그 실행
    pEXCEL_export->uDLG_XLS_export->Execute(NULL);

    COLcnt = PGM->uDB_main->ColCount;


        switch(pEXCEL_export->uOPT_XLS_export_Type->ItemIndex)
        {
        // 선택된 건수출력
        case 000: zSEL=0x1; ROWcnt = Export_SELcnt; break;
        // 검색된 전체건수출력
        case 001: zSEL=0x0; ROWcnt = Export_ALLcnt; break;
        }


// ▶▶ 메인테이블 형상그대로 저장한다
PGM->uEXCEL_wb->Grid->ColCount = COLcnt;
PGM->uEXCEL_wb->Grid->RowCount = ROWcnt+2;


    // ■ 헤더필드 주입
    // 필드이름 / 필드폭길이 적용
    for(x=1;x<=COLcnt-1;x++)
    {
        PGM->uEXCEL_wb->Grid->Cells[x-1][000] = Main_TBL_NMEs[x+1];
        PGM->uEXCEL_wb->Grid->Cells[x-1][001] = Main_TBL_FLDs[x+1];
        PGM->uEXCEL_wb->Grid->ColWidths[x-1]  = Main_TBL_CLWs[x+1];
    }

    // ■ 데이타 주입
    cnt = Export_ALLcnt;

    y = 000;
    for(n=1;n<=cnt;n++)
    {
        chk = PGM->uDB_main->IsChecked(0, n);
        if(zSEL==0x0 || (zSEL==0x1 && chk))
        {
            ++y;

            x = 000;
            for(p=1;p<=COLcnt;p++)
            {
                if(1<p)
                {
                    ++x;
                    PGM->uEXCEL_wb->Grid->Cells[x-1][y+1] = PGM->uDB_main->Cells[p-1][n];
                }
            }
        }
    }
    //                                                                         .
    // ★ 엑셀파일저장
    dSTR = xSYS.runDiR;
    dSTR += "/OUT";
    PGM->uSaveFiLE->InitialDir = dSTR;

    fSTR = pEXCEL_export->uDLG_XLS_export->FileName;

    pEXCEL_export->uEXCEL->XLSExport(fSTR, "검색결과");
    //                                                                         .
    pEXCEL_export->Close();
}
//---------------------------------------------------------------------------
void __fastcall TpEXCEL_export::uBTN_XLS_export_CloseClick(TObject *Sender)
{
    pEXCEL_export->Close();
}
//---------------------------------------------------------------------------

