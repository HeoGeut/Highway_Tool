#pragma link "AdvGridWorkbook"
#pragma link "tmsAdvGridExcel"
#pragma link "AdvCustomTreeView"
#pragma link "AdvTreeView"
#pragma link "AdvTreeViewBase"
#pragma link "AdvTreeViewData"
#pragma link "AdvCheckTreeView"
#pragma link "AdvCombo"
#pragma link "AdvEdit"
#pragma link "AdvGlassButton"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "CryptBase"
#pragma link "DBAdvGrid"
#pragma link "HashObj"
#pragma link "RzDTP"
#pragma link "RzPrgres"
#pragma link "RzStatus"
#pragma link "RzTabs"
#pragma link "DBAdvGrid"
#pragma link "CryptBase"
#pragma link "HashObj"
#pragma link "AdvCheckTreeView"
#pragma link "AdvListBox"
#pragma link "RzDTP"
#pragma link "AdvCGrid"
#pragma link "AdvCombo"
#pragma link "AdvDateTimePicker"
#pragma link "AdvEdit"

#include "./RAD/Cru_HEADER.h"

#include <System.Net.HttpClientComponent.hpp>
#include <System.Json.hpp>
#include <memory>

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
#pragma package(smart_init)

// ♨ 주석풀면, 에러남
//#pragma link "odbcinst.lib"
#pragma link "odbccp32.lib"

#pragma resource "*.dfm"
//==============================================================================
TPGM *PGM; __fastcall TPGM::TPGM(TComponent* Owner) : TForm(Owner) { }
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 함수 프로토타입

void prePROCESS(void);

void PROC_Login(void);
void PROC_GET_Brands(void);

void Main_Table_ColDEF(void);

void ENABLE_DBconn(int iFLAG);

void DiSP_SHT_List(void);

void PROC_SHT_Zoom(int iZOOM);
void PROC_TBL_Zoom(int iZOOM);

void SET_Authority(char *iSTR);

void CLEAR_LastSEARCH(void);
void SAVE_LastSEARCH(void);
void LOAD_LastSEARCH(void);

int COMPACT_CustomerCODE(void);

void AutoSAVE_main_FLDs(void);
int  SEQ_Main_TBL_Field(int iSEQ);

void SYNC_OUT_FLDs(void);
void SYNC_main_FLDs(void);
void SYNC_main_CLWs(void);

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
// 외부참조 / 전역변수

Cru_SYSTEM xSYS;                                 // 시스템 개체                .

Cru_SCRiPT xSCR;                                 // 스크립트 개체              .

//●●●●●●●
CRITICAL_SECTION core_CS;                        // core 동기화用, 크리티칼 섹션
Cru_THR          *core_RUN;                      // core 쓰레드                .
//●●●●●●●

int Search_FOLDER_FiLEcnt;

    UnicodeString g_URL;
    UnicodeString g_AccKEY, g_SecKEY, g_Query, g_DateTiME;
    UnicodeString g_Algorithm;
    UnicodeString g_ContentType;
    UnicodeString g_Header;
    UnicodeString g_Methode, g_Path, g_Message, g_Signature;

int zTGL_SangPoom_List, zTGL_SangPoom_image;

//▩▩▩▩▩▩▩▩▩▩
int  Main_TBL_FNOs[1000];                        // 메인테이블 필드번호 리스트
int  Main_TBL_AVLs[1000];                        // 메인테이블 표시여부 리스트
int  Main_TBL_CLWs[1000];                        // 메인테이블 폭길이 리스트
char Main_TBL_FLDs[1000][64];                    // 메인테이블 영문필드이름
char Main_TBL_NMEs[1000][64];                    // 메인테이블 한글필드이름
int  Main_TBL_Field_CNT;                         // 메인테이블 필드개수
///////
int  Main_TBL_DEFAULTs[1000];                    // 메인테이블 디폴트필드 필드번호 리스트
int  Main_TBL_DEFAULTs_FLDcnt;                   // 메인테이블 디폴트필드 개수
///////
int  Main_TBL_SAVEs[1000];                       // 메인테이블 저장필드 필드번호 리스트
int  Main_TBL_SaveCLWs[1000];                    // 메인테이블 저장 폭길이 리스트
int  Main_TBL_SAVEs_FLDcnt;                      // 메인테이블 저장필드 개수
//▩▩▩▩▩▩▩▩▩▩

char FilePath_LastSEARCH[4096];

UnicodeString Brands_STR;
char Brands[1000][64];
int Start_BRAND;

int zFiNDiNG;                                    // 검색중 플랙
int FiNDiNG_LOOPcnt;

int MODE_MainDB;                                 // 메인DB 모드 (0= 읽기 mode / 1= 수정 mode)

int Export_SELcnt;
int Export_ALLcnt;
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void __fastcall TPGM::FormCreate(TObject *Sender)
{
    xSYS.FLAG[f_PGM_START] = 0x1;
    xSYS.FLAG[f_QUiT]      = 0x0;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::FormPaint(TObject *Sender)
{
    if(xSYS.FLAG[f_PGM_START])
    {
        xSYS.FLAG[f_PGM_START] = 0x0;
        /*                     */
        /**/  prePROCESS();  /**/
        /*                     */
    }
}
//---------------------------------------------------------------------------
void __fastcall TPGM::FormDestroy(TObject *Sender)
{
    SAVE_LastSEARCH();

    //▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧
    // 크리티칼섹션 삭제
    DeleteCriticalSection(&core_CS);

    // 쓰레드 종료
    core_RUN->Terminate();
    //▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧

    // 실행종료 플랙
    xSYS.FLAG[f_QUiT] = 0x1;
}
//==============================================================================
void prePROCESS(void)
{
    int n,p,k,cnt;

    char mSTR[1024], wSTR[1024];
    char zSTR[1024], fSTR[1024];
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .

    /*                      */
    /*  ★ 시스템 초기화    */
    /*                      */
    /**/                  /**/
    /**/  xSYS.Reset();   /**/
    /**/                  /**/
    /*                      */
    if(xSYS.FLAG[f_QUiT]) return;

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // 각종리셋처리

        ENABLE_DBconn(0x0);

        PGM->uLOG->Lines->Clear();

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ★ ODBC - DSN 추가

    // 레지스트리
    // HKEY_CURRENT_USER -> Software -> ODBC ->ODBC.INI
    //                                                .
    // mySQL_highway 정보                             .
    //                                                .

int err;
char mySQL_DRV[1024];
char odbc_ATTR[1024];

cpSTR(mySQL_DRV, "MySQL ODBC 3.51 Driver");

cpSTR(odbc_ATTR, "DSN=mySQL_highway;");
adSTR(odbc_ATTR, "DESCRIPTION=mySQL_highway;");

//■■■■■■■■■■
//▶▶로컬DB
//PGM->uLiNKname->Caption = "Local - DB";
//adSTR(odbc_ATTR, "SERVER=119.65.133.12;");
//adSTR(odbc_ATTR, "PORT=3456;");
//■■■■■■■■■■
//▶▶구글DB
PGM->uLiNKname->Caption = "FindK - DB";
adSTR(odbc_ATTR, "SERVER=35.197.140.210;");
adSTR(odbc_ATTR, "PORT=3306;");
//■■■■■■■■■■

adSTR(odbc_ATTR, "DATABASE=highway;");
adSTR(odbc_ATTR, "UID=root;");
adSTR(odbc_ATTR, "PWD=fkfk;");

err = SQLConfigDataSource(NULL,
                          ODBC_REMOVE_DSN,
                          mySQL_DRV,
                          odbc_ATTR);

err = SQLConfigDataSource(NULL,
                          ODBC_ADD_DSN,
                          mySQL_DRV,
                          odbc_ATTR);

err=err;

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ★ MAC 주소표시

         GET_MAC_Address(mSTR);

         sfSTR(wSTR, "MAC_addr= %s", mSTR);

         PGM->uMAC->Caption       = wSTR;
         PGM->uMAC_Login->Caption = wSTR;

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ★ 초기권한

        // 처음에는 로긴권한만 있슴
        cpSTR(wSTR, "1");

        /*                            */
        /**/  SET_Authority(wSTR);  /**/
        /*                            */

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ★ Ui 설정

    MODE_MainDB = 0x0;

    if(MODE_MainDB==000)

// 메인테이블 표시화면 넓게보기
//k = 300;
//PGM->uPageControl->Width += k;
//PGM->uMAiN_PNL1->Width   += k;
//PGM->uMAiN_PNL2->Width   += k;
//PGM->uDB_main->Width     += k-300;


PGM->uCKTR_1->FullExpand();
PGM->uCKTR_2->FullExpand();
PGM->uCKTR_3->FullExpand();
PGM->uCKTR_4->FullExpand();

/*
// uCHKLST_SangPoom_DispCOLs 에 체크고정
cnt = PGM->uCHKLST_SangPoom_DispCOLs->Items->Count;
for(n=1;n<=cnt;n++)
{
    PGM->uCHKLST_SangPoom_DispCOLs->Checked[n-1] = 0x0;
}

PGM->uCHKLST_SangPoom_DispCOLs->Checked[  0] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  1] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  2] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  3] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  4] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  5] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  6] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  7] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[  8] = 0x1;

PGM->uCHKLST_SangPoom_DispCOLs->Checked[ 27] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[ 28] = 0x1;
PGM->uCHKLST_SangPoom_DispCOLs->Checked[ 29] = 0x1;

PGM->uCHKLST_SangPoom_DispCOLs->Visible = 0x0;
*/

///////
zTGL_SangPoom_List  = 0x1;

cpSTR(fSTR, xSYS.resDiR);
adSTR(fSTR, "리스트");
sfSTR(zSTR, "%1d", zTGL_SangPoom_List);
adSTR(fSTR, zSTR);
adSTR(fSTR, ".png");

PGM->uTGL_SangPoom_List->Picture->LoadFromFile(fSTR);
///////
zTGL_SangPoom_image = 0x0;

cpSTR(fSTR, xSYS.resDiR);
adSTR(fSTR, "이미지");
sfSTR(zSTR, "%1d", zTGL_SangPoom_image);
adSTR(fSTR, zSTR);
adSTR(fSTR, ".png");

PGM->uTGL_SangPoom_image->Picture->LoadFromFile(fSTR);
///////


    // 엑셀칼럼 정의
    PGM->uEXCEL_FLDs->Cells[0][000] = "";
    PGM->uEXCEL_FLDs->Cells[1][000] = "순번";
    PGM->uEXCEL_FLDs->Cells[2][000] = "필드번호";
    PGM->uEXCEL_FLDs->Cells[3][000] = "필드영문이름";
    PGM->uEXCEL_FLDs->Cells[4][000] = "필드한글이름";
    PGM->uEXCEL_FLDs->Cells[5][000] = "칼럼폭";

    PGM->uEXCEL_FLDs->ColWidths[0]  = 30;
    PGM->uEXCEL_FLDs->ColWidths[1]  = 40;
    PGM->uEXCEL_FLDs->ColWidths[2]  = 50;
    PGM->uEXCEL_FLDs->ColWidths[3]  = 150;
    PGM->uEXCEL_FLDs->ColWidths[4]  = 160;
    PGM->uEXCEL_FLDs->ColWidths[5]  = 40;

    cnt = Main_TBL_Field_CNT;
    PGM->uEXCEL_FLDs->RowCount = cnt;

PGM->uEXCEL_FLDs->AddCheckBox(0, 000, 0x0, 0x0);

    p=000;
    for(n=1;n<=cnt;n++)
    {
        if(Main_TBL_FLDs[n][0]=='(') continue;

        ++p;

PGM->uEXCEL_FLDs->AddCheckBoxColumn(0, 0x0, 0x0);

        PGM->uEXCEL_FLDs->Cells[1][p] = p;                 // 순번
        PGM->uEXCEL_FLDs->Cells[2][p] = Main_TBL_FNOs[n];  // 필드번호
        PGM->uEXCEL_FLDs->Cells[3][p] = Main_TBL_FLDs[n];  // 필드영문이름
        PGM->uEXCEL_FLDs->Cells[4][p] = Main_TBL_NMEs[n];  // 필드한글이름
        PGM->uEXCEL_FLDs->Cells[5][p] = Main_TBL_CLWs[n];  // 칼럼폭
    }

    // 외부 APi 나열
    PGM->uOPT_extHOSTsClick(NULL);


    // 외부 APi 클리어
    PGM->uAPi_REQ_methode->Text = "";
    PGM->uAPi_REQ_path->Text    = "";
    PGM->uAPi_REQ_header->Text  = "";
    PGM->uAPi_REQ_message->Text = "";
    PGM->uAPi_REQ_url->Text     = "";

    PGM->uAPi_REP->Clear();


        //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩
        // ▶▶ 초기화버튼 자동실행
        PGM->uBTN_miNiTClick(NULL);
        //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩


    // 가장 최근의 검색내용 로딩
    cpSTR(FilePath_LastSEARCH, xSYS.resDiR);
    adSTR(FilePath_LastSEARCH, "LastFind.mem");

    LOAD_LastSEARCH();
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ▶▶▶ 각종테스트


//TTreeNode *node;
//
//node = PGM->uCKTR_1->Items->Item[4];
//PGM->uCKTR_1->Checked[node] = 0x1;


    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    // ★ core 쓰레드 초기화 / 가동

        InitializeCriticalSectionAndSpinCount(&core_CS, 4000);
        core_RUN = new Cru_THR(true);
        core_RUN->THR_iD = 001;
        core_RUN->FreeOnTerminate = true;
        core_RUN->Priority = tpNormal;
        core_RUN->Resume();

    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    //■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■
    //  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■ .
    zFiNDiNG = 0x0;
    FiNDiNG_LOOPcnt = 000;
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void PROC_Login(void)
{
    int rtn;

    char idSTR[1024];
    char pwSTR[1024];

    char Tab_USEs[1024];
    int  Start_TAB;

    AnsiString aSTR;
    //                                                                         .
    // 로그인 처리를 위한 DB 연결
    PGM->uADOconn->Connected = 0x1;

    PGM->uTBL_user->Active = 0x1;
    PGM->uTBL_grade->Active = 0x1;

    PGM->uQRY_ck->Active = 0x1;
    //                                                                         .
    aSTR = PGM->uLogin_iD->Text;
    cpSTR(idSTR, aSTR.c_str());
    ///////
    aSTR = PGM->uLogin_PW->Text;
    cpSTR(pwSTR, aSTR.c_str());

PGM->uSP_Login->ProcedureName = "proc_UserLOGiN";
PGM->uSP_Login->Prepared = 0x1;

PGM->uSP_Login->Parameters->Clear();
PGM->uSP_Login->Parameters->CreateParameter("iUser_iD", Data::Db::ftString, pdInput, 30, idSTR);
PGM->uSP_Login->Parameters->CreateParameter("iUser_PW", Data::Db::ftString, pdInput, 20, pwSTR);

        /*                               */
        /**/  PGM->uSP_Login->Open();  /**/
        /*                               */

    //                                                                         .

        // 메인테이블 칼럼정의
        Main_Table_ColDEF();

    //                                                                         .
//    PGM->uiPT_acc_iD->Text = PGM->uLogin_iD->Text;
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void PROC_GET_Brands(void)
{
    int rtn;

    char idSTR[1024];

    AnsiString aSTR;
    //                                                                         .
    // DB 연결
    PGM->uADOconn->Connected = 0x1;

    PGM->uQRY_ck->Active = 0x1;
    //                                                                         .
    aSTR = PGM->uLogin_iD->Text;
    cpSTR(idSTR, aSTR.c_str());
    ///////

PGM->uSP->ProcedureName = "proc_GET_Brands";
PGM->uSP->Prepared = 0x1;

PGM->uSP->Parameters->Clear();
PGM->uSP->Parameters->CreateParameter("iUser_iD", Data::Db::ftString, pdInput, 30, idSTR);

        /*                         */
        /**/  PGM->uSP->Open();  /**/
        /*                         */

    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void Main_Table_ColDEF(void)
{
/*
    int n,p,cnt;
    UnicodeString Field_STR;


//■■■■■■■■■■■■■■■■■■■■
// DB 인덱스        ( 1▶ idx            )
// 브랜드           (10▶ brd_name       )
// 계정ID           (49▶ acc_id         )
// 판매자관리코드   ( 3▶ sel_cod        )
// 상품명           (14▶ kr_prd_name    )
// 옵션1 (색상)     ( 6▶ op_1           )
// 옵션2 (사이즈)   ( 7▶ op_2           )
// 판매가           (18▶ sell_pri       )
// 선정일자         ( 2▶ sel_date       )
// 수정일자         (29▶ lastmod_date   )
// 메모1            (46▶ memo1          )
// 메모2            (47▶ memo2          )
// 메모3            (48▶ memo3          )
//========================================
// 중국선정마켓     (11▶ cn_mkt_name    )
// 카테고리         (13▶ cate_1         )
// 배송비 정책      (15▶ dlv_chg_pli    )
// 구매가격(￥위안) (16▶ cny_pri        )
// 구매가격(￦원)   (17▶ krw_pri        )
// 배송비           (19▶ dlv_chg        )
// 등록여부         (20▶ prd_reg_chk    )
// 예상 마진        (21▶ mrg_ex         )
// 마진율(20~30%)   (22▶ mrg_pct        )
// 최소수량         (23▶ min_qty        )
// 키워드           (24▶ re_kwd         )
// 한글카테고리     (28▶ cate_2         )
// 등록마켓         (30▶ mkt_name       )
// 계정             (31▶ mkt_id         )
// 카테고리(자사몰) (32▶ cate_3         )
// 상품상태         (34▶ prd_condi      )
// 거래처정보       (36▶ cust_info      )
// 판매상태(자사몰) (44▶ sale_condi     )
//■■■■■■■■■■■■■■■■■■■■


    PGM->uDB_Main->Columns->Clear();
    ///////
    cnt = Main_TBL_Field_CNT;
    for(n=1;n<=cnt;n++) { PGM->uDB_Main->Columns->Add(); }
    ///////
    for(n=1;n<=cnt;n++)
    {
        p = n-1;

        Field_STR = "";
        switch(p)
        {
        // 고정칼럼
        case  1: Field_STR = "idx";          break;
        case  2: Field_STR = "brd_name";     break;
        case  3: Field_STR = "acc_id";       break;
        case  4: Field_STR = "sel_cod";      break;
        case  5: Field_STR = "kr_prd_name";  break;
        case  6: Field_STR = "sell_pri";     break;
        case  7: Field_STR = "sel_date";     break;
        case  8: Field_STR = "lastmod_date"; break;
        // 선택칼럼
        case  9: Field_STR = "cn_mkt_name";  break;
        case 10: Field_STR = "cate_1";       break;
        case 11: Field_STR = "dlv_chg_pli";  break;
        case 12: Field_STR = "cny_pri";      break;
        case 13: Field_STR = "krw_pri";      break;
        case 14: Field_STR = "dlv_chg";      break;
        case 15: Field_STR = "prd_reg_chk";  break;
        case 16: Field_STR = "mrg_ex";       break;
        case 17: Field_STR = "mrg_pct";      break;
        case 18: Field_STR = "min_qty";      break;
        case 19: Field_STR = "re_kwd";       break;
        case 20: Field_STR = "cate_2";       break;
        case 21: Field_STR = "mkt_name";     break;
        case 22: Field_STR = "mkt_id";       break;
        case 23: Field_STR = "cate_3";       break;
        case 24: Field_STR = "prd_condi";    break;
        case 25: Field_STR = "cust_info";    break;
        case 26: Field_STR = "sale_condi";   break;
        case 27: Field_STR = "memo1";        break;
        case 28: Field_STR = "memo2";        break;
        case 29: Field_STR = "memo3";        break;
        ///////
        }

        if(Field_STR!="")
        {
            PGM->uDB_Main->Columns->Items[p]->FieldName = Field_STR;
            PGM->uDB_Main->ColWidths[p] = Main_TBL_CWs[n];
        }
    }
    ///////
*/
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void ENABLE_DBconn(int iFLAG)
{
//    PGM->uDBconn_BTN->Visible = iFLAG;
//    PGM->uDBcut_BTN->Visible  = iFLAG;
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void PROC_SHT_Zoom(int iZOOM)
{
    int n;
    int cnt;
    //                                                                         .
    switch(iZOOM)
    {
    //■■■■■■■■■■
    // 시트축소
    case -1:

        ///////
        PGM->uSHT_Zoom_BTN->Caption = "시트확대";
        ///////
        PGM->uGGtoDB_Trans_BTN->Visible = 0x1;
        PGM->uPGS_DB_import->Visible    = 0x1;
        PGM->uDB_RECcnt->Visible        = 0x1;
        PGM->uDB_Panel->Visible         = 0x1;

        PGM->uSHT_Show_BTN->Visible     = 0x1;
        PGM->uSHTcnt->Visible           = 0x1;
        PGM->uSHT_List->Visible         = 0x1;
        PGM->uSubSHTcnt->Visible        = 0x1;
        PGM->uSHT_WBs->Visible          = 0x1;
        ///////
        PGM->uSHT->Left   = 10;
        PGM->uSHT->Top    = 60;
        PGM->uSHT->Width  = 400;
        PGM->uSHT->Height = 185;
        PGM->uSHT->ColWidths[000] = 50;
        PGM->uG_Panel->Width  = PGM->uSHT->Width+20;
        PGM->uG_Panel->Height = PGM->uSHT->Height+20;

        cnt = PGM->uSHT->ColCount;
        for(n=1;n<cnt;n++)
        {
            PGM->uSHT->ColWidths[n] = 100;
        }
        ///////

    break;
    //■■■■■■■■■■
    // 시트확대
    case +1:

        ///////
        PGM->uSHT_Zoom_BTN->Caption = "시트축소";
        ///////
        PGM->uGGtoDB_Trans_BTN->Visible = 0x0;
        PGM->uPGS_DB_import->Visible    = 0x0;
        PGM->uDB_RECcnt->Visible        = 0x0;
        PGM->uDB_Panel->Visible         = 0x0;

        PGM->uSHT_Show_BTN->Visible     = 0x0;
        PGM->uSHTcnt->Visible           = 0x0;
        PGM->uSHT_List->Visible         = 0x0;
        PGM->uSubSHTcnt->Visible        = 0x0;
        PGM->uSHT_WBs->Visible          = 0x0;
        ///////
        PGM->uSHT->Left   = 10;
        PGM->uSHT->Top    = 60;
        PGM->uSHT->Width  = 960;
        PGM->uSHT->Height = 600;
        PGM->uSHT->ColWidths[000] = 50;
        PGM->uG_Panel->Width  = PGM->uSHT->Width+20;
        PGM->uG_Panel->Height = PGM->uSHT->Height+20;

        cnt = PGM->uSHT->ColCount;
        for(n=1;n<cnt;n++)
        {
            PGM->uSHT->ColWidths[n] = 300;
        }
        ///////

    break;
    //■■■■■■■■■■
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void PROC_TBL_Zoom(int iZOOM)
{
    int n;
    int cnt;
    //                                                                         .
    switch(iZOOM)
    {
    //■■■■■■■■■■
    // 테이블축소
    case -1:

        ///////
        PGM->uTBL_Zoom_BTN->Caption = "테이블확대";
        ///////
        PGM->uGGconn_BTN->Visible = 0x1;
        PGM->uGGcut_BTN->Visible  = 0x1;
        PGM->uG_Panel->Visible    = 0x1;

        PGM->uGGtoDB_Trans_BTN->Left =  20;
        PGM->uGGtoDB_Trans_BTN->Top  = 295;
        PGM->uPGS_DB_import->Left    = 190;
        PGM->uPGS_DB_import->Top     = 310;
        PGM->uDB_RECcnt->Left        = 330;
        PGM->uDB_RECcnt->Top         = 319;

//        PGM->uDBconn_BTN->Visible       = 0x1;
//        PGM->uDBcut_BTN->Visible        = 0x1;
        PGM->uGGtoDB_Trans_BTN->Visible = 0x1;
        PGM->uDB_Panel->Visible         = 0x1;

        PGM->uSHT_Show_BTN->Visible     = 0x1;
        PGM->uSHTcnt->Visible           = 0x1;
        PGM->uSHT_List->Visible         = 0x1;
        PGM->uSubSHTcnt->Visible        = 0x1;
        PGM->uSHT_WBs->Visible          = 0x1;
        ///////
        PGM->uDB_Panel->Left = 10;
        PGM->uDB_Panel->Top  = 340;

        PGM->uDB->Left   = 10;
        PGM->uDB->Top    = 30;
        PGM->uDB->Width  = 400;
        PGM->uDB->Height = 280;

        PGM->uDB->ColWidths[000] = 50;

        PGM->uDB_Panel->Width  = PGM->uDB->Width+20;
        PGM->uDB_Panel->Height = PGM->uDB->Height+40;

        cnt = PGM->uDB->ColCount;
        for(n=1;n<cnt;n++)
        {
            PGM->uDB->ColWidths[n] = 30;
        }
        ///////

    break;
    //■■■■■■■■■■
    // 테이블확대
    case +1:

        ///////
        PGM->uTBL_Zoom_BTN->Caption = "테이블축소";
        ///////
        PGM->uGGconn_BTN->Visible = 0x0;
        PGM->uGGcut_BTN->Visible  = 0x0;
        PGM->uG_Panel->Visible    = 0x0;

        PGM->uGGtoDB_Trans_BTN->Left =  20;
        PGM->uGGtoDB_Trans_BTN->Top  =  15;
        PGM->uPGS_DB_import->Left    = 190;
        PGM->uPGS_DB_import->Top     =  30;
        PGM->uDB_RECcnt->Left        = 330;
        PGM->uDB_RECcnt->Top         =  39;

        PGM->uSHT_Show_BTN->Visible  = 0x0;
        PGM->uSHTcnt->Visible        = 0x0;
        PGM->uSHT_List->Visible      = 0x0;
        PGM->uSubSHTcnt->Visible     = 0x0;
        PGM->uSHT_WBs->Visible       = 0x0;
        ///////
        PGM->uDB_Panel->Left = 10;
        PGM->uDB_Panel->Top  = 60;

        PGM->uDB->Left   = 10;
        PGM->uDB->Top    = 30;
        PGM->uDB->Width  = 960;
        PGM->uDB->Height = 560;
        PGM->uDB->ColWidths[000] = 50;

        PGM->uDB_Panel->Width  = PGM->uDB->Width+20;
        PGM->uDB_Panel->Height = PGM->uDB->Height+40;

        cnt = PGM->uDB->ColCount;
        for(n=1;n<cnt;n++)
        {
            PGM->uDB->ColWidths[n] = 300;
        }
        ///////

    break;
    //■■■■■■■■■■
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void SET_Authority(char *iSTR)
{
    int n;
    int cnt,pcnt;
    int tab;

    char pSTR[1024];
    //                                                                         .
    pcnt = PGM->uPageControl->PageCount;
    for(n=1;n<=pcnt;n++)
    {
        PGM->uPageControl->Pages[n-1]->TabEnabled = 0x0;
        PGM->uPageControl->Pages[n-1]->Color = RGB( 50, 50, 50);
    }
    //                                                                         .
    cnt = paraCNT_jCOMMA_List(iSTR);

    for(n=1;n<=cnt;n++)
    {
        cpSTR(pSTR, jCOMMA_List(iSTR, n));

        tab = atoi(pSTR);

        PGM->uPageControl->Pages[tab-1]->TabEnabled = 0x1;
        PGM->uPageControl->Pages[tab-1]->Color = RGB(200,200,200);
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void CLEAR_LastSEARCH(void)
{
    if(CHECK_FileEXiST(FilePath_LastSEARCH))
    {
        DeleteFile(FilePath_LastSEARCH);
    }
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void SAVE_LastSEARCH(void)
{
    FILE *Fw;
    char fSTR[4096], cSTR[4096], wSTR[4096];


    int n,cnt;
    char s[101][256];
    int  v[101];

    AnsiString aSTR,kSTR,pSTR;

    TDateTime date1, date2;
    unsigned short int y,m,d;

    TTreeNode *node;
    //                                                                         .
    memset(s, 000, sizeof(s));
    memset(v, 000, sizeof(v));

    CLEAR_LastSEARCH();
    //                                                                         .

    cpSTR(fSTR, FilePath_LastSEARCH);

    Fw = fopen(fSTR, "wt");


//■■■■■■■■■■
// ♣ 검색단어
aSTR = PGM->uFiND_word->Text;
cpSTR(s[1], aSTR.c_str());

v[2] = PGM->uFiND_Logos->ItemIndex;
v[3] = PGM->uFiND_Boundary->ItemIndex;

fprintf(Fw, "Find_1= \"%s\", %d, %d", s[1], v[2], v[3]);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 날짜
date1 = PGM->uFiND_Calendar1->Date;
date2 = PGM->uFiND_Calendar2->Date;

DecodeDate(date1, y,m,d);
y%=100;
sfSTR(s[1], "%02d_%02d_%02d", y,m,d);

DecodeDate(date2, y,m,d);
y%=100;
sfSTR(s[2], "%02d_%02d_%02d", y,m,d);


v[3] = PGM->uFiND_SELdate->ItemIndex;

fprintf(Fw, "Find_2= %s, %s, %d", s[1], s[2], v[3]);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 브랜드
v[1] = PGM->uFiND_Brand->ItemIndex;

fprintf(Fw, "Find_3= %d", v[1]);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 판매자관리코드

    // 여기에 빈라인 자동으로 붙이기 처리


cnt = PGM->uFiND_CustomerCODE->Lines->Count;
//cnt = (10<cnt)? 10 : cnt;

aSTR = "Find_4= ";
for(n=1;n<=cnt;n++)
{
    pSTR = PGM->uFiND_CustomerCODE->Lines->Strings[n-1];

    aSTR += pSTR;

    if(n<cnt) aSTR += ", ";
}

cpSTR(cSTR, aSTR.c_str());
fprintf(Fw, cSTR);
fprintf(Fw, "\n\n");
//■■■■■■■■■■
// ♣ 구매유형 체크트리노드
cnt = PGM->uCKTR_1->Items->Count;

aSTR = "CheckTreeNode_1= ";
for(n=1;n<=cnt;n++)
{
    node = PGM->uCKTR_1->Items->Item[n-1];

    sfSTR(wSTR, "%1d", PGM->uCKTR_1->Checked[node]);
    pSTR = wSTR;
    aSTR += pSTR;

    if(n<cnt) aSTR += ", ";
}

cpSTR(cSTR, aSTR.c_str());
fprintf(Fw, cSTR);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 작업상태 체크트리노드
cnt = PGM->uCKTR_2->Items->Count;

aSTR = "CheckTreeNode_2= ";
for(n=1;n<=cnt;n++)
{
    node = PGM->uCKTR_2->Items->Item[n-1];

    sfSTR(wSTR, "%1d", PGM->uCKTR_2->Checked[node]);
    pSTR = wSTR;
    aSTR += pSTR;

    if(n<cnt) aSTR += ", ";
}

cpSTR(cSTR, aSTR.c_str());
fprintf(Fw, cSTR);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 승인상태 체크트리노드
cnt = PGM->uCKTR_3->Items->Count;

aSTR = "CheckTreeNode_3= ";
for(n=1;n<=cnt;n++)
{
    node = PGM->uCKTR_3->Items->Item[n-1];

    sfSTR(wSTR, "%1d", PGM->uCKTR_3->Checked[node]);
    pSTR = wSTR;
    aSTR += pSTR;

    if(n<cnt) aSTR += ", ";
}

cpSTR(cSTR, aSTR.c_str());
fprintf(Fw, cSTR);
fprintf(Fw, "\n");
//■■■■■■■■■■
// ♣ 상품체크 체크트리노드
cnt = PGM->uCKTR_4->Items->Count;

aSTR = "CheckTreeNode_4= ";
for(n=1;n<=cnt;n++)
{
    node = PGM->uCKTR_4->Items->Item[n-1];

    sfSTR(wSTR, "%1d", PGM->uCKTR_4->Checked[node]);
    pSTR = wSTR;
    aSTR += pSTR;

    if(n<cnt) aSTR += ", ";
}

cpSTR(cSTR, aSTR.c_str());
fprintf(Fw, cSTR);
fprintf(Fw, "\n");
//■■■■■■■■■■


    //                                                                         .
    fclose(Fw);
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void LOAD_LastSEARCH(void)
{
    FILE *Fr;
    char fSTR[4096];
    char ORG_kSTR[1024], kSTR[1024];
    //                                                                         .
    if(!CHECK_FileEXiST(FilePath_LastSEARCH)) return;
    //                                                                         .
    cpSTR(fSTR, FilePath_LastSEARCH);

    Fr = fopen(fSTR, "rb");

    //■==■==■==■==■==■==■
    while(!feof(Fr))
    {
        jTextFile_ReadLiNE(Fr, kSTR);
        if(feof(Fr)) break;

cpSTR(ORG_kSTR, kSTR);
cmptSTR(kSTR);

xSCR.qCOMMAND(ORG_kSTR, kSTR);

    }
    //■==■==■==■==■==■==■

    //                                                                         .
    fclose(Fr);
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
int COMPACT_CustomerCODE(void)
{
    int rtn;
    int n,p,k,cnt;

    char wSTR[1024];
    AnsiString aSTR, jSTR;
    //                                                                         .
    // 공백최적화
    cnt = PGM->uFiND_CustomerCODE->Lines->Count;
    for(n=1;n<=cnt;n++)
    {

aSTR = PGM->uFiND_CustomerCODE->Lines->Strings[n-1];
jSTR = aSTR.Trim();

PGM->uFiND_CustomerCODE->Lines->Strings[n-1] = jSTR;

    }
    //                                                                         .
    // 라인최적화
    for(n=1;n<=cnt;n++)
    {

aSTR = PGM->uFiND_CustomerCODE->Lines->Strings[n-1];

        if(aSTR=="")
        {
            for(p=n;p<=cnt;p++)
            {
                k = p-1;

                PGM->uFiND_CustomerCODE->Lines->Strings[k] =
                PGM->uFiND_CustomerCODE->Lines->Strings[k+1];
            }

            PGM->uFiND_CustomerCODE->Lines->Strings[cnt-1] = "";
        }
    }
    rtn = cnt;
    //                                                                         .
    sfSTR(wSTR, "%d 라인", rtn);
    PGM->uFiND_CustomerCNT->Caption = wSTR;
    //                                                                         .
    return rtn;
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void AutoSAVE_main_FLDs(void)
{
    FILE *Fw;
    int n;
    int cnt,idx,width;

    char fSTR[1024], wSTR[1024];
    AnsiString aSTR;

    TTreeNode *node;
    //                                                                         .
    // ★ 결과출력칼럼 (3_save_FLDs.isq 파일 자동저장)
    cpSTR(fSTR, xSYS.resDiR);
    adSTR(fSTR, "/3_save_FLDs.isq");

    Fw = fopen(fSTR, "wt");

    //■■==■■==■■==■■==■■==■■==■■==■■
    fprintf(Fw, "// 자동저장칼럼\n");
    cnt = PGM->uEXCEL_OUTs->Items->Count;
    //■■==■■==■■==■■==■■==■■==■■==■■
    fprintf(Fw, "DB_save_main_FLDs = ");

        for(n=1;n<=cnt;n++)
        {
            node = PGM->uEXCEL_OUTs->Items->Item[n-1];
            aSTR = node->Text;
            cpSTR(wSTR, aSTR.c_str());

            idx = (wSTR[0]-'0')*10 + (wSTR[1]-'0');

            fprintf(Fw, "%3d", idx);

            if(n<cnt)
            {
                fprintf(Fw, ", ");
            }
        }

    fprintf(Fw, "\n");
    ///////
    fprintf(Fw, "DB_width_main_FLDs= ");

        for(n=1;n<=cnt;n++)
        {
            width = PGM->uDB_main->ColWidths[n];
            Main_TBL_SaveCLWs[n] = width;

            fprintf(Fw, "%3d", width);

            if(n<cnt)
            {
                fprintf(Fw, ", ");
            }
        }

    fprintf(Fw, "\n");
    //■■==■■==■■==■■==■■==■■==■■==■■
    fprintf(Fw, "DB_save_order_FLDs = ");
    fprintf(Fw, "\n");

    fprintf(Fw, "DB_width_order_FLDs= ");
    fprintf(Fw, "\n");
    //■■==■■==■■==■■==■■==■■==■■==■■
    fclose(Fw);
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
int SEQ_Main_TBL_Field(int iFNO)
{
    int rtn;
    int n,cnt,idx;

    rtn = 000;
    ///////
    cnt = Main_TBL_Field_CNT;
    for(n=1;n<=cnt;n++)
    {
        idx = Main_TBL_FNOs[n];
        if(iFNO==idx) rtn = n;
    }
    ///////
    return rtn;
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void SYNC_OUT_FLDs(void)
{
    int n;
    int cnt,idx,seq,Len;
    char wSTR[1024], bSTR[1024];
    AnsiString zzSTR;
    //                                                                         .
    PGM->uEXCEL_OUTs->Items->Clear();
    //                                                                         .
    cnt = Main_TBL_SAVEs_FLDcnt;
    for(n=1;n<=cnt;n++)
    {
        idx = Main_TBL_SAVEs[n];

        seq = SEQ_Main_TBL_Field(idx);

        Len = 15 - lenSTR(Main_TBL_FLDs[seq]);
        CHAR_String(bSTR, '_', Len);

        sfSTR(wSTR, "%02d : %s%s : %s",
                    Main_TBL_FNOs[seq],
                    Main_TBL_FLDs[seq],
                    bSTR,
                    Main_TBL_NMEs[seq]);

        zzSTR = wSTR;

        PGM->uEXCEL_OUTs->Items->Add(NULL, zzSTR);
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void SYNC_main_FLDs(void)
{
    int n;
    int cnt,idx,seq;
    //                                                                         .
    cnt = Main_TBL_SAVEs_FLDcnt;
    PGM->uDB_main->ColCount = cnt + 1;
    //                                                                         .
    for(n=1;n<=cnt;n++)
    {
        idx = Main_TBL_SAVEs[n];

        seq = SEQ_Main_TBL_Field(idx);

        PGM->uDB_main->Cells[n][000] = Main_TBL_NMEs[seq];
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void SYNC_main_CLWs(void)
{
    int n;
    int cnt,idx,seq;
    //                                                                         .
    cnt = Main_TBL_SAVEs_FLDcnt;
    PGM->uDB_main->ColWidths[000] = Main_TBL_CLWs[1];
    //                                                                         .
    for(n=1;n<=cnt;n++)
    {
        PGM->uDB_main->ColWidths[n] = Main_TBL_SaveCLWs[n];
    }
    //                                                                         .
}
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■.
void __fastcall TPGM::uDBconn_BTNClick(TObject *Sender)
{
    // ▶▶ DB 연결
    PGM->uADOconn->Connected = 0x1;
    PGM->uTBL->Active = 0x1;

    PGM->uTBL_user->Active = 0x1;
    PGM->uTBL_grade->Active = 0x1;
    PGM->uTBL_product->Active = 0x1;

    PGM->uTBL_Zoom_BTN->Visible = 0x1;

    PROC_TBL_Zoom(-1);
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDBcut_BTNClick(TObject *Sender)
{
    // ■ DB연결 절단
    PGM->uADOconn->Connected = 0x0;

    PGM->uTBL_Zoom_BTN->Visible = 0x0;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uGGtoDB_Trans_BTNClick(TObject *Sender)
{
    int n,p,x,y;

    int rcnt, pcnt, nowREC;

    float pgs;

    char wSTR[4096], shtSTR[1024], wbSTR[1024];

    UnicodeString Query_STR;
    char DB_Table_NAME[1024];
    UnicodeString tblSTR;
    UnicodeString iSQL;

    UnicodeString uSTR, paraSTR;
    AnsiString aSTR, nSTR;

    UTF8String utf8STR;

    int ziMPORT;

    //                                                                         .
    // ▶▶ DB 전송
    ziMPORT = 0x0;

    x = PGM->uSHT_List->Col;
    y = PGM->uSHT_List->Row;
    aSTR = PGM->uSHT_List->Cells[x][y];
    cpSTR(shtSTR, aSTR.c_str());

    x = PGM->uSHT_WBs->Col;
    y = PGM->uSHT_WBs->Row;
    aSTR = PGM->uSHT_WBs->Cells[x][y];
    cpSTR(wbSTR, aSTR.c_str());

        //■==■==■==■==■==■==■==■==■==■
        if(3 > PGM->uSHT->ColCount
        && 3 > PGM->uSHT->RowCount)
        {
            okMSG("시트 데이타가 없습니다");
            return;
        }
        //■==■==■==■==■==■==■==■==■==■
//        else if(eqSTR(shtSTR, "하이웨이_상품선정 통합")
//        &&      eqSTR(wbSTR,  "하이웨이_상품선정 통합"))
        if(eqSTR(wbSTR, "하이웨이_상품선정 통합"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "productlist");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`sel_date`, ";       // ● 선정일자
iSQL+= "`sel_cod`, ";        // ● 판매자 관리코드
iSQL+= "`list_img_thum`, ";  // ● 이미지 미리보기
iSQL+= "`cn_prd_name`, ";    // ● 중국 상품명

iSQL+= "`op_1`, ";           // ● 옵션1(색상)
iSQL+= "`op_2`, ";           // ● 옵션2(사이즈)
iSQL+= "`list_img_url`, ";   // ● 대표 이미지
iSQL+= "`mkt_n_id`, ";       // ● 등록마켓 / 계정
iSQL+= "`brd_name`, ";       // ● 브랜드

iSQL+= "`cn_mkt_name`, ";    // ● 중국선정마켓이름
iSQL+= "`cn_itm_url`, ";     // ● URL
iSQL+= "`cate_1`, ";         // ● 카테고리
iSQL+= "`kr_prd_name`, ";    // ● 한글상품명
iSQL+= "`dlv_chg_pli`, ";    // ● 배송비 정책

iSQL+= "`cny_pri`, ";        // ● 구매가격 (위안)
iSQL+= "`krw_pri`, ";        // ● 구매가격 (원)
iSQL+= "`sell_pri`, ";       // ● 판매가격
iSQL+= "`dlv_chg`, ";        // ● 배송비
iSQL+= "`prd_reg_chk`, ";    // ● 등록여부

iSQL+= "`mrg_ex`, ";         // ● 예상 마진
iSQL+= "`mrg_pct`, ";        // ● 마진율 (20~30%)
iSQL+= "`min_qty`, ";        // ● 최소수량
iSQL+= "`re_kwd`, ";         // ● 키워드
iSQL+= "`prd_inf`, ";        // ● 상세이미지

iSQL+= "`prd_inf_data`, ";   // ● 상품정보
iSQL+= "`siz_inf`, ";        // ● 사이즈표
iSQL+= "`cate_2`, ";         // ● 한글카테고리
iSQL+= "`lastmod_data`, ";   // ● 수정일자
iSQL+= "`mkt_name`, ";       // ● 등록마켓

iSQL+= "`mkt_id`, ";         // ● 계정
iSQL+= "`cate_3`, ";         // ● 카테고리(자사몰)
iSQL+= "`prd_inf_data2`, ";  // ● 상품정보2
iSQL+= "`prd_condi`, ";      // ● 상품상태
iSQL+= "`buy_type`, ";       // ● 구매유형

iSQL+= "`cust_info`, ";      // ● 거래처정보
iSQL+= "`model_info`, ";     // ● 모델정보
iSQL+= "`prd_inf_data3`, ";  // ● 상품정보3
iSQL+= "`prd_gosi`, ";       // ● 정보고시
iSQL+= "`codi_cod`, ";       // ● 코디상품

iSQL+= "`insta_td`, ";       // ● 인스타그램 연결
iSQL+= "`work_condi`, ";     // ● 작업상태
iSQL+= "`app_condi`, ";      // ● 승인상태
iSQL+= "`sale_condi`, ";     // ● 판매상태 (자사몰)
iSQL+= "`prd_check`, ";      // ● 상품체크

iSQL+= "`memo1`, ";          // ● 메모1
iSQL+= "`memo2`, ";          // ● 메모2
iSQL+= "`memo3`, ";          // ● 메모3

iSQL+= "`acc_id`, ";         // ● 계정ID계정iD
iSQL+= "`sup_url`, ";        // ● 공급사 URL
iSQL+= "`origin`";           // ● 원산지
iSQL+= " ) VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR, "옵션 필터링 키워드 리스트"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "op_keyfilter");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`optxt`, ";          // ● 변경할 단어
iSQL+= "`optxt_new` ";       // ● 변경후 단어
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR, "상품명 필터링 키워드 리스트"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "name_keyfilter");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`nametxt`, ";        // ● 변경할 단어
iSQL+= "`nametxt_new` ";     // ● 변경후 단어
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR,  "자사몰 카테고리표"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "corp_catelist");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`cate_cod`, ";       // ● 카테고리코드
iSQL+= "`bi_cate`, ";        // ● 대분류명
iSQL+= "`mi_cate`, ";        // ● 중분류명
iSQL+= "`sm_cate`, ";        // ● 소분류명
iSQL+= "`sv_cate` ";         // ● 세분류명
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR,  "플레이오토 카테고리표"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "pa_catelist");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`cate_cod`, ";       // ● 카테고리코드
iSQL+= "`bi_cate`, ";        // ● 대분류명
iSQL+= "`mi_cate`, ";        // ● 중분류명
iSQL+= "`sm_cate`, ";        // ● 소분류명
iSQL+= "`sv_cate` ";         // ● 세분류명
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR,  "해외거래처리스트"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "foreign_mktlist");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`fi_url`, ";         // ● URL
iSQL+= "`fi_name` ";         // ● 거래처명
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else if(eqSTR(wbSTR,  "모델정보 리스트"))
        {
            ziMPORT = 0x1;
            // ♣ 임포팅될 DB 테이블 이름
            cpSTR(DB_Table_NAME, "model_infolist");
            tblSTR = DB_Table_NAME;


// ▶▶ iNSERT - SQL 문장조립
iSQL = "INSERT INTO " + tblSTR + " ( ";
iSQL+= "`idx`, ";            // ● 인덱스
iSQL+= "`acc_id`, ";         // ● 등록계정
iSQL+= "`mod_name`, ";       // ● 모델이름
iSQL+= "`mod_heig`, ";       // ● 키
iSQL+= "`mod_top`, ";        // ● 상의
iSQL+= "`mod_bott`, ";       // ● 하의
iSQL+= "`mod_shoe`, ";       // ● 발
iSQL+= "`mod_main`, ";       // ● 대표모델
iSQL+= "`mod_img` ";         // ● 모델이미지
iSQL+= ") VALUES ( ";

        }
        //■==■==■==■==■==■==■==■==■==■
        else
        {
            okMSG("임포팅할 시트 대상이 아닙니다");
            return;
        }
        //■==■==■==■==■==■==■==■==■==■

    //                                                                         .
    if(ziMPORT)
    {
        // ♣ DB 테이블 - 데이타 클리어
        Query_STR  = "DELETE FROM ";
        Query_STR += "`" + tblSTR + "` ";
        Query_STR += "WHERE 1;";
        PGM->uQRY->SQL->Text = Query_STR;
        PGM->uQRY->ExecSQL();
        PGM->uQRY->Close();

        // ♣ DB 테이블 - 임포팅
        rcnt = PGM->uSHT->RowCount;
        for(y=2;y<=rcnt;y++)
        {

nowREC = y-1;


// ■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■.
// ▶▶ 필드주입 (유니코드가능)
nSTR = nowREC;
paraSTR = nSTR + ", ";

//■==■==■==■==■==■==■
if(eqSTR(DB_Table_NAME, "productlist"))
{
    pcnt = 48;
    for(p=1;p<=pcnt;p++)
    {
        paraSTR += "'" + PGM->uSHT->Cells[p][y] + "'";

        if(p<pcnt) paraSTR += ",";
    }
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "op_keyfilter"))
{
    paraSTR += "'" + PGM->uSHT->Cells[1][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'";
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "name_keyfilter"))
{
    paraSTR += "'" + PGM->uSHT->Cells[1][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'";
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "corp_catelist"))
{
    if(PGM->uSHT->Cells[1][y]=="") goto NEXT_Record;

    nSTR = PGM->uSHT->Cells[1][y].ToInt();
    paraSTR += nSTR + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[3][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[4][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[5][y] + "'";
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "pa_catelist"))
{
    if(PGM->uSHT->Cells[1][y]=="") goto NEXT_Record;

    nSTR = PGM->uSHT->Cells[1][y].ToInt();
    paraSTR += nSTR + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[3][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[4][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[5][y] + "'";
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "foreign_mktlist"))
{
    paraSTR += "'" + PGM->uSHT->Cells[1][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'";
}
//■==■==■==■==■==■==■
else if(eqSTR(DB_Table_NAME, "model_infolist"))
{
    paraSTR += "'" + PGM->uSHT->Cells[1][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[2][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[3][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[4][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[5][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[6][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[7][y] + "'" + ", ";
    paraSTR += "'" + PGM->uSHT->Cells[8][y] + "'";
}
//■==■==■==■==■==■==■


PGM->uQRY->SQL->Clear();

// ▶▶ iNSERT - SQL 문장조립
Query_STR  = iSQL;
Query_STR += paraSTR;
Query_STR += " );";
// ■■■■■■■■■■■■■■■■■■■.
//■■■■■■■■■■■■■■■■■■■■
// ■■■■■■■■■■■■■■■■■■■.

PGM->uQRY->SQL->Add(Query_STR);

PGM->uQRY->ExecSQL();

PGM->uQRY->Close();

// pgs:100=x:rcnt
// pgs*rcnt=100*x
// pgs = 100*x/rcnt
pgs=100*nowREC/rcnt;

PGM->uPGS_DB_import->Percent = pgs;
PGM->uPGS_DB_import->Refresh();

PGM->uDB_RECcnt->Caption = nowREC;
PGM->uDB_RECcnt->Refresh();

NEXT_Record:

        }

PGM->uPGS_DB_import->Percent = 100;

    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uLogin_BTNClick(TObject *Sender)
{
    PROC_Login();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uLogin_PWKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key==VK_RETURN)
    {
        PGM->uLogin_BTNClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uSHT_Zoom_BTNClick(TObject *Sender)
{
    //                                                                         .
    if(PGM->uSHT_Zoom_BTN->Caption=="시트확대")
    {
        PROC_SHT_Zoom(+1);
    }
    else if(PGM->uSHT_Zoom_BTN->Caption=="시트축소")
    {
        PROC_SHT_Zoom(-1);
    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uTBL_Zoom_BTNClick(TObject *Sender)
{
    //                                                                         .
    if(PGM->uTBL_Zoom_BTN->Caption=="테이블확대")
    {
        PROC_TBL_Zoom(+1);
    }
    else if(PGM->uTBL_Zoom_BTN->Caption=="테이블축소")
    {
        PROC_TBL_Zoom(-1);
    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDBPainted(TObject *Sender)
{
    int cnt;
    char wSTR[256];
    AnsiString aSTR;
    if(!PGM->uADOconn->Connected) return;
    if(!PGM->uTBL->Active) return;
    cnt = PGM->uTBL->RecordCount;
    sfSTR(wSTR, "%d Rec", cnt); aSTR = wSTR;
    PGM->uDB_RECcnt->Caption = aSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_userPainted(TObject *Sender)
{
    int cnt;
    char wSTR[256];
    AnsiString aSTR;
    if(!PGM->uADOconn->Connected) return;
    if(!PGM->uTBL_user->Active) return;
    cnt = PGM->uTBL_user->RecordCount;
    sfSTR(wSTR, "%d Rec", cnt); aSTR = wSTR;
    PGM->uDB_user_RECcnt->Caption = aSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_gradePainted(TObject *Sender)
{
    int cnt;
    char wSTR[256];
    AnsiString aSTR;
    if(!PGM->uADOconn->Connected) return;
    if(!PGM->uTBL_grade->Active) return;
    cnt = PGM->uTBL_grade->RecordCount;
    sfSTR(wSTR, "%d Rec", cnt); aSTR = wSTR;
    PGM->uDB_grade_RECcnt->Caption = aSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uHTTP_REQRequestCompleted(TObject * const Sender, IHTTPResponse * const AResponse)
{
    char rDATA[4096];

    TEncoding *enc;
    //                                                                         .

//    enc = new TEncoding->(NULL);

    enc->GetEncoding(932);


AResponse->Version;

AResponse->StatusCode;

AResponse->ContentAsString(enc);

    //                                                                         .
}
//---------------------------------------------------------------------------

void __fastcall TPGM::uHTTPzzChunkReceived(TObject *Sender, TIdBytes &Chunk)
{
    Chunk = Chunk;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uSP_LoginAfterOpen(TDataSet *DataSet)
{
    int  n;
    int  oResult;
    char Tab_USEs[1024];
    int  Start_TAB;

    UnicodeString uSTR, nSTR;
    AnsiString aSTR;
    //                                                                         .
    oResult = DataSet->FieldByName("$oRESULT")->AsInteger;

switch(oResult)
{
//■==■==■==■==■==■==■==■==■==■
// 아이디없슴
case 1:

    okMSG("아이디가 존재하지 않습니다");

break;
//■==■==■==■==■==■==■==■==■==■
// 암호틀림
case 2:

    okMSG("암호가 틀립니다");

break;
//■==■==■==■==■==■==■==■==■==■
// 사용불가
case 4:

    okMSG("사용불가 유저입니다");

break;
//■==■==■==■==■==■==■==■==■==■
// 탈퇴유저
case 6:

    okMSG("탈퇴한 유저입니다");

break;
//■==■==■==■==■==■==■==■==■==■
// 로긴성공
case 7:

        // 이름표시
        nSTR = DataSet->FieldByName("$oNAME")->AsString;
        PGM->uNAME->Caption = nSTR;

        // ▶▶ 권한부여 (사용탭 활성화)
        uSTR = DataSet->FieldByName("$oTab_USEs")->AsString;
        aSTR = uSTR;
        cpSTR(Tab_USEs, aSTR.c_str());

        SET_Authority(Tab_USEs);

        // 개시 탭선택
        Start_TAB = DataSet->FieldByName("$oStart_TAB")->AsInteger;

        PGM->uPageControl->TabIndex = Start_TAB-1;

break;
//■==■==■==■==■==■==■==■==■==■
}

    //                                                                         .

        // ♣ 저장프로시저 리셋
        PGM->uSP_Login->Close();

    //                                                                         .
    if(oResult==7)
    {
        // 브랜드 리스트 가져오기
        PROC_GET_Brands();
    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_mFiNDClick(TObject *Sender)
{
    int n;

    int sel, cnt, logos, DaySEL, BRDsel;

    int zALL;

    UnicodeString Query_STR;
    UnicodeString tblSTR;

    UnicodeString gSTR, fSTR, fSTR1, fSTR2, fSTR3, fSTR4, fSTR5;
    UnicodeString kSTR, vSTR, sSTR, bSTR;
    UnicodeString dSTR, day1, day2;

    char wSTR[1024], jSTR[1024];

    AnsiString aSTR;

    TDateTime date1, date2;
    unsigned short int yy,mm,dd;

    //                                                                         .
    if(zFiNDiNG) return;
    PGM->uBTN_mFiND->Enabled = 0x0;
    PGM->uBTN_mFiND->Refresh();
    //                                                                         .

gSTR  = PGM->uFiND_word->Text;

gSTR = gSTR.TrimLeft();
gSTR = gSTR.TrimRight();

fSTR = gSTR;

/*
    if(fSTR=="")
    {
        okMSG("검색내용을 입력하세요");
        return;
    }
*/
    zALL = (fSTR=="");
    //                                                                         .
    zFiNDiNG = 0x1;
    FiNDiNG_LOOPcnt = 000;

    PGM->uFiND_STAT->Caption = "검색중 ...";
    PGM->uFiND_STAT->Repaint();
    //                                                                         .

aSTR = fSTR;

cpSTR(jSTR, aSTR.c_str());

fSTR1  = "";
fSTR2  = "";
fSTR3  = "";

// 공백구분 문자열 추출
cnt = paraCNT_jSPACE_List(jSTR);

for(n=1;n<=cnt;n++)
{
    ///////
    switch(n)
    {
    case 1: cpSTR(wSTR, jSPACE_List(jSTR, 1)); fSTR1 = wSTR; break;
    case 2: cpSTR(wSTR, jSPACE_List(jSTR, 2)); fSTR2 = wSTR; break;
    case 3: cpSTR(wSTR, jSPACE_List(jSTR, 3)); fSTR3 = wSTR; break;
    }
    ///////
}

    //                                                                         .
    // ♣ 메인테이블 검색
    tblSTR = "productlist";

    Query_STR  = "SELECT * FROM ";
    Query_STR += "`" + tblSTR + "` ";

logos = PGM->uFiND_Logos->ItemIndex + 1;

//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
sel = PGM->uFiND_Boundary->ItemIndex;
sel = (sel<000)? 000 : sel;

//                            .
//--------------------------------------
// 판매자관리코드   (  3▶ sel_cod     )
// 한글상품명       ( 14▶ kr_prd_name )
// 옵션1 (색상)     (  6▶ op_1        )
// 옵션2 (사이즈)   (  7▶ op_2        )
// 키워드           ( 24▶ re_kwd      )
// 메모1            ( 46▶ memo1       )
// 메모2            ( 47▶ memo2       )
// 메모3            ( 48▶ memo3       )
// 계정ID           ( 49▶ acc_id      )
// 옵션1 (색상)     (  6▶ op_1        )
// 옵션1 (색상)     (  7▶ op_2        )
//--------------------------------------
//                            .
// sel == 000 인경우,,        .
// 필드일치조건이 전체선택이면,
//                            .
// 위의 9개 필드를 대상으로   .
// 모두검색                   .
//                            .

//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
//▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩
if(zALL) goto proc_WHERE;


switch(logos)
{
//■■■■■■■■■■■■■■■■■■■■
// 완전일치
case 1:

    kSTR  = "( ";
    //==============================
    if(1<=cnt)
    {
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     = '" + fSTR1 + "' OR ";
            kSTR += "`kr_prd_name` = '" + fSTR1 + "' OR ";
            kSTR += "`re_kwd`      = '" + fSTR1 + "' OR ";
            kSTR += "`memo1`       = '" + fSTR1 + "' OR ";
            kSTR += "`memo2`       = '" + fSTR1 + "' OR ";
            kSTR += "`memo3`       = '" + fSTR1 + "' OR ";
            kSTR += "`acc_id`      = '" + fSTR1 + "' OR ";
            kSTR += "`op_1`        = '" + fSTR1 + "' OR ";
            kSTR += "`op_2`        = '" + fSTR1 + "'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     = '" + fSTR1 + "'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` = '" + fSTR1 + "'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      = '" + fSTR1 + "'"; break;

        case 4: kSTR += "`memo1`       = '" + fSTR1 + "' OR ";
                kSTR += "`memo2`       = '" + fSTR1 + "' OR ";
                kSTR += "`memo3`       = '" + fSTR1 + "'"; break;
        ///////
        case 5: kSTR += "`acc_id`      = '" + fSTR1 + "'"; break;
        ///////
        case 6: kSTR += "`op_1`        = '" + fSTR1 + "' OR ";
                kSTR += "`op_2`        = '" + fSTR1 + "'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(2<=cnt)
    {
        kSTR += " AND ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     = '" + fSTR2 + "' OR ";
            kSTR += "`kr_prd_name` = '" + fSTR2 + "' OR ";
            kSTR += "`re_kwd`      = '" + fSTR2 + "' OR ";
            kSTR += "`memo1`       = '" + fSTR2 + "' OR ";
            kSTR += "`memo2`       = '" + fSTR2 + "' OR ";
            kSTR += "`memo3`       = '" + fSTR2 + "' OR ";
            kSTR += "`acc_id`      = '" + fSTR2 + "' OR ";
            kSTR += "`op_1`        = '" + fSTR2 + "' OR ";
            kSTR += "`op_2`        = '" + fSTR2 + "'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     = '" + fSTR2 + "'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` = '" + fSTR2 + "'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      = '" + fSTR2 + "'"; break;

        case 4: kSTR += "`memo1`       = '" + fSTR2 + "' OR ";
                kSTR += "`memo2`       = '" + fSTR2 + "' OR ";
                kSTR += "`memo3`       = '" + fSTR2 + "'"; break;
        ///////
        case 5: kSTR += "`acc_id`      = '" + fSTR2 + "'"; break;
        ///////
        case 6: kSTR += "`op_1`        = '" + fSTR2 + "' OR ";
                kSTR += "`op_2`        = '" + fSTR2 + "'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(3<=cnt)
    {
        kSTR += " AND ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     = '" + fSTR3 + "' OR ";
            kSTR += "`kr_prd_name` = '" + fSTR3 + "' OR ";
            kSTR += "`re_kwd`      = '" + fSTR3 + "' OR ";
            kSTR += "`memo1`       = '" + fSTR3 + "' OR ";
            kSTR += "`memo2`       = '" + fSTR3 + "' OR ";
            kSTR += "`memo3`       = '" + fSTR3 + "' OR ";
            kSTR += "`acc_id`      = '" + fSTR3 + "' OR ";
            kSTR += "`op_1`        = '" + fSTR3 + "' OR ";
            kSTR += "`op_2`        = '" + fSTR3 + "'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     = '" + fSTR3 + "'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` = '" + fSTR3 + "'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      = '" + fSTR3 + "'"; break;

        case 4: kSTR += "`memo1`       = '" + fSTR3 + "' OR ";
                kSTR += "`memo2`       = '" + fSTR3 + "' OR ";
                kSTR += "`memo3`       = '" + fSTR3 + "'"; break;
        ///////
        case 5: kSTR += "`acc_id`      = '" + fSTR3 + "'"; break;
        ///////
        case 6: kSTR += "`op_1`        = '" + fSTR3 + "' OR ";
                kSTR += "`op_2`        = '" + fSTR3 + "'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
//    kSTR += " ) ";

break;
//■■■■■■■■■■■■■■■■■■■■
// 부분일치 AND
case 2:

    kSTR  = "( ";
    //==============================
    if(1<=cnt)
    {
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR1 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR1 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR1 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR1 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR1 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR1 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR1 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR1 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR1 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR1 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR1 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR1 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR1 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR1 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(2<=cnt)
    {
        kSTR += " AND ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR2 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR2 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR2 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR2 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR2 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR2 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR2 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR2 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR2 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR2 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR2 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR2 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR2 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR2 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(3<=cnt)
    {
        kSTR += " AND ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR3 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR3 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR3 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR3 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR3 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR3 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR3 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR3 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR3 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR3 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR3 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR3 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR3 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR3 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
//    kSTR += " ) ";

break;
//■■■■■■■■■■■■■■■■■■■■
// 부분일치 OR
case 3:

    kSTR  = "( ";
    //==============================
    if(1<=cnt)
    {
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR1 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR1 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR1 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR1 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR1 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR1 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR1 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR1 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR1 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR1 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR1 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR1 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR1 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR1 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR1 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(2<=cnt)
    {
        kSTR += " OR ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR2 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR2 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR2 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR2 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR2 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR2 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR2 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR2 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR2 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR2 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR2 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR2 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR2 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR2 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR2 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
    if(3<=cnt)
    {
        kSTR += " OR ";
        kSTR += "( ";

        switch(sel)
        {
        ///////
        case 000:

            kSTR += "`sel_cod`     like '%" + fSTR3 + "%' OR ";
            kSTR += "`kr_prd_name` like '%" + fSTR3 + "%' OR ";
            kSTR += "`re_kwd`      like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo1`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo2`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`memo3`       like '%" + fSTR3 + "%' OR ";
            kSTR += "`acc_id`      like '%" + fSTR3 + "%' OR ";
            kSTR += "`op_1`        like '%" + fSTR3 + "%' OR ";
            kSTR += "`op_2`        like '%" + fSTR3 + "%'";

        break;
        ///////
        case 1: kSTR += "`sel_cod`     like '%" + fSTR3 + "%'"; break;
        ///////
        case 2: kSTR += "`kr_prd_name` like '%" + fSTR3 + "%'"; break;
        ///////
        case 3: kSTR += "`re_kwd`      like '%" + fSTR3 + "%'"; break;

        case 4: kSTR += "`memo1`       like '%" + fSTR3 + "%' OR ";
                kSTR += "`memo2`       like '%" + fSTR3 + "%' OR ";
                kSTR += "`memo3`       like '%" + fSTR3 + "%'"; break;
        ///////
        case 5: kSTR += "`acc_id`      like '%" + fSTR3 + "%'"; break;
        ///////
        case 6: kSTR += "`op_1`        like '%" + fSTR3 + "%' OR ";
                kSTR += "`op_2`        like '%" + fSTR3 + "%'"; break;
        ///////
        }

        kSTR += " )";
    }
    //==============================
//    kSTR += " ) ";

break;
//■■■■■■■■■■■■■■■■■■■■
}

proc_WHERE:

Query_STR += "WHERE ";
Query_STR += kSTR;


    //                                                                         .
    // ▶▶ 선정일자 / 수정일자 검색적용

if(!zALL)
{
    dSTR += " AND ";
}

    dSTR += "( ";
    //==============================
    // 날짜범위쿼리 조립
    DaySEL = PGM->uFiND_SELdate->ItemIndex;

    switch(DaySEL)
    {
    case 000: vSTR = "date(`sel_date`)";     break;
    case 001: vSTR = "date(`lastmod_date`)"; break;
    }


date1 = PGM->uFiND_Calendar1->Date;
DecodeDate(date1,yy,mm,dd);
sfSTR(wSTR, "str_to_date('%d,%d,%d', '%%Y,%%m,%%d')", yy,mm,dd);
day1 = wSTR;

date2 = PGM->uFiND_Calendar2->Date;
DecodeDate(date2,yy,mm,dd);
sfSTR(wSTR, "str_to_date('%d,%d,%d', '%%Y,%%m,%%d')", yy,mm,dd);
day2 = wSTR;


    dSTR += " ( ";
    dSTR += day1;
    dSTR += " <= ";
    dSTR += vSTR;
    dSTR += " ) ";

    dSTR += " AND ";

    dSTR += " ( ";
    dSTR += vSTR;
    dSTR += " <= ";
    dSTR += day2;
    dSTR += " ) ";
    //==============================
if(!zALL)
{
    dSTR += " ) ";
}

Query_STR += dSTR;

    //                                                                         .
    // ▶▶ 브랜드 검색적용

    //==============================
    BRDsel = PGM->uFiND_Brand->ItemIndex;
    if(000 < BRDsel)
    {

kSTR  = " AND ";
kSTR += "( ";

        bSTR = PGM->uFiND_Brand->Items->Strings[BRDsel];

        kSTR += "`brd_name` = ";
        kSTR += "'";
        kSTR += bSTR;
        kSTR += "'";

kSTR += " ) ";

Query_STR += kSTR;

    }
    //==============================

    //                                                                         .
    // ▶▶ 판매자 관리코드 리스트 검색적용
    cnt = COMPACT_CustomerCODE();

    if(000 < cnt)
    {

kSTR  = " AND ";
kSTR += "( ";

for(n=1;n<=cnt;n++)
{
    bSTR = PGM->uFiND_CustomerCODE->Lines->Strings[n-1];

//??? 옵션으로 아래를 선택하게 만들것

    // 완전일치검색
//    kSTR += "`sel_cod` = ";
//    kSTR += "'";
//    kSTR += bSTR;
//    kSTR += "'";

    // 와일드검색
    kSTR += "`sel_cod` like ";
    kSTR += "'";
    kSTR += "%";
    kSTR += bSTR;
    kSTR += "%";
    kSTR += "'";

    if(n < cnt)
    {
        kSTR += " OR ";
    }
}

kSTR += " ) ";

Query_STR += kSTR;

    }

    //                                                                         .
    // WHERE 종결 괄호
    Query_STR += " ) ";
    //                                                                         .
    // 날짜 최신순으로 정렬
    sSTR  = "ORDER BY ";
    sSTR += vSTR;
    sSTR += " DESC";

    Query_STR += sSTR;
    //                                                                         .
    // SQL 문장종결
    Query_STR += ";";

    //                                                                         .
    PGM->uQRY_main->SQL->Text = Query_STR;

    zFiNDiNG = 0x1;
    FiNDiNG_LOOPcnt = 000;

    PGM->uQRY_main->Open();
    //                                                                         .
int k;

    k = PGM->uQRY_main->RecordCount;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_miNiTClick(TObject *Sender)
{
// ▶ 초기화

    PGM->uFiND_word->Text = "";

    PGM->uFiND_Logos->ItemIndex = 000;

    PGM->uFiND_Boundary->ItemIndex = 000;

    PGM->uFiND_SELdate->ItemIndex = 000;

    PGM->uFiND_Brand->ItemIndex = 000;

    // 오늘날짜 리셋
    PGM->uDTE_TodayClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uCKTR_1Collapsed(TObject *Sender, TTreeNode *Node)
{
    PGM->uCKTR_1->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uCKTR_2Collapsed(TObject *Sender, TTreeNode *Node)
{
    PGM->uCKTR_2->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uCKTR_3Collapsed(TObject *Sender, TTreeNode *Node)
{
    PGM->uCKTR_3->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uCKTR_4Collapsed(TObject *Sender, TTreeNode *Node)
{
    PGM->uCKTR_4->FullExpand();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uOPT_extHOSTsClick(TObject *Sender)
{
    int sel;
    //                                                                         .
    sel = PGM->uOPT_extHOSTs->ItemIndex;

    switch(sel)
    {
    // 타오바오 - APi
    case 0:

PGM->uOPT_extAPis->Columns = 2;

PGM->uOPT_extAPis->Items->Clear();

PGM->uOPT_extAPis->Items->Add("구매자 정보");              // 사용자 APi   : taobao.user.buyer.get
PGM->uOPT_extAPis->Items->Add("판매자 사용자 정보");       // 사용자 APi   : taobao.user.seller.get
PGM->uOPT_extAPis->Items->Add("계정 데이터 검색");         // 사용자 APi   : taobao.user.buyer.get
PGM->uOPT_extAPis->Items->Add("제품정보");                 // 제품 APi     : taobao.products.search
PGM->uOPT_extAPis->Items->Add("제품목록보기");             // 제품 APi     : taobao.appstore.subscribe.get
PGM->uOPT_extAPis->Items->Add("판매자상점 기본정보");      // 상점 APi     : taobao.shop.get
PGM->uOPT_extAPis->Items->Add("물류정보조회");             // 물류 APi     : taobao.logistics.trace.search
PGM->uOPT_extAPis->Items->Add("라이더의 현재 위치 조회");  // 물류 APi     : alibaba.ele.fengniao.carrierdriver.location
PGM->uOPT_extAPis->Items->Add("단일거래의 세부정보");      // 무역 APi     : taobao.trade.fullinfo.get
PGM->uOPT_extAPis->Items->Add("카테고리정보 가져오기");    // 카테고리 APi : alibaba.wholesale.category.get

//PGM->uAPi_REQ_url->Text         = "http://gw.api.taobao.com/router/rest";
//
//PGM->uAPi_REQ_contenttype->Text = "content-type:application/x-www-form-urlencoded";
//
//PGM->uAPi_REQ_charset->Text     = "charset=utf-8";
//
//    PGM->uREQ_para->Lines->Clear();
//    PGM->uREQ_para->Lines->Add("Lease_id=14192");
//    PGM->uREQ_para->Lines->Add("nick=tbtest110");
//
//PGM->uAPi_REP->Clear();

    break;
    //■■■■■■■■■■
    // 쿠팡 - APi
    case 1:\

PGM->uOPT_extAPis->Columns = 1;

PGM->uOPT_extAPis->Items->Clear();


PGM->uOPT_extAPis->Items->Add("HMAC 인증");
PGM->uOPT_extAPis->Items->Add("게이트웨이");
PGM->uOPT_extAPis->Items->Add("카테고리 조회");
PGM->uOPT_extAPis->Items->Add("카테고리 목록 조회");
PGM->uOPT_extAPis->Items->Add("카테고리 유효성 검사");
PGM->uOPT_extAPis->Items->Add("카테고리 메타정보 조회");

//PGM->uAPi_REQ_contenttype->Text = "";
//PGM->uAPi_REQ_charset->Text     = "";
//
//PGM->uREQ_para->Lines->Clear();
//PGM->uREQ_para->Lines->Add("Lease_id=14192");
//PGM->uREQ_para->Lines->Add("nick=tbtest110");

PGM->uAPi_REP->Clear();

    break;
    //■■■■■■■■■■
    }
}
//---------------------------------------------------------------------------

void __fastcall TPGM::uHTTP_REQAfterExecute(TCustomRESTRequest *Sender)
{
        UnicodeString rDATA;

// ♣ 데이타 수신
rDATA = PGM->uHTTP_REP->Content;

        //■■■■■■■■■■■■■■■■■■■■
        // ♣ 응답표시

PGM->uAPi_REP->Lines->Clear();
PGM->uAPi_REP->Lines->Add(rDATA);

        //■■■■■■■■■■■■■■■■■■■■
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uOPT_extAPisClick(TObject *Sender)
{
    int idx,sel,Len;

    UnicodeString hostSTR;

    UnicodeString Date_STR;
    UnicodeString Time_STR;

    UnicodeString Methode;
    UnicodeString URL;
    UnicodeString Path;
    UnicodeString DateTiME, Query, Message;

    char wSTR[1024], dSTR[1024], tSTR[1024];
    //                                                                         .
    idx = PGM->uOPT_extHOSTs->ItemIndex;
    hostSTR = PGM->uOPT_extHOSTs->Items->Strings[idx];

    //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩
    if(hostSTR=="타오바오")
    {
        sel = PGM->uOPT_extAPis->ItemIndex + 1;

        switch(sel)
        {
        // ● A .
        case   1:

//PGM->uAPi_REQ_url->Text = "http://gw.api.tbsandbox.com/router/rest";
URL  = "?";
Path = "?";

        break;
        // ● B .
        case   2:

URL  = "?";
Path = "?";

        break;
        // ● C .
        case   3:

URL  = "?";
Path = "?";

        break;
        // ● D .
        case   4:

URL  = "?";
Path = "?";

        break;
        // ● E .
        case   5:

URL  = "?";
Path = "?";

        break;
        // ● F .
        case   6:

URL  = "?";
Path = "?";

        break;
        // ● G .
        case   7:

URL  = "?";
Path = "?";

        break;
        // ● H .
        case   8:

URL  = "?";
Path = "?";

        break;
        // ● i .
        case   9:

URL  = "?";
Path = "?";

        break;
        // ● J .
        case  10:

URL  = "?";
Path = "?";

        break;
        }
    }
    //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩
    else if(hostSTR=="쿠팡")
    {

g_AccKEY = "e3ae6995-01ed-43c8-a1a4-669b8ca9aa22";
g_SecKEY = "e0a2536f181c9c2d971d5e76549cc022aee6e34d";

//■■■■■■■■■■
//■■■■■■■■■■
        sel = PGM->uOPT_extAPis->ItemIndex + 1;

        switch(sel)
        {
        // ● HMAC 인증
        case   1:

Methode = "GET";

URL  = "https://api-gateway.coupang.com";
Path = "/v2/providers/openapi/apis/api/v4/vendors/A00075121/returnRequests";

Query   = "createdAtFrom=2018-10-31&createdAtTo=2018-10-31&status=UC";

        break;
        // ● 게이트웨이
        case   2:

Methode = "GET";

URL  = "https://api-gateway.coupang.com";
Path = "";

Query   = "";

        break;
        // ● 카테고리 조회
        case   3:

Methode = "GET";

URL  = "https://api-gateway.coupang.com/targets/wing/seller_api/apis/api";
Path = "/v1/marketplace/meta/display-categories/0";

Query   = "";

        break;
        // ● 카테고리 목록 조회
        case   4:

Methode = "GET";

//https://api-gateway.coupang.com

URL  = "https://api-gateway.coupang.com/targets/wing/seller_api/apis/api";
Path = "/v1/marketplace/meta/display-categories";

Query   = "";

        break;
        // ● 카테고리 유효성 검사
        case   5:

Methode = "GET";

URL  = "https://api-gateway.coupang.com/targets/wing/seller_api/apis/api";
Path = "/v1/marketplace/meta/display-categories/0/status";

Query   = "";

        break;
        // ● 카테고리 메타정보 조회
        case   6:
/*
URL  = "https://api-gateway.coupang.com/targets/wing/seller_api/apis/api";
Path = "/v1/marketplace/meta/category-related-metas/display-category-codes/78877";
*/
Methode = "GET";

URL  = "?";
Path = "?";

Query   = "";

        break;
        ///////
        }

//■■■■■■■■■■
//■■■■■■■■■■
//■■■■■■■■■■
fYMDHMS(wSTR);
Len = lenSTR(wSTR);

subcpSTR(dSTR, wSTR, 1, 8);
subcpSTR(tSTR, wSTR, Len-6+1, 6);

Date_STR = dSTR;
Time_STR = tSTR;

// ● 메소드
g_Methode = Methode;

// ● 기능 경로
g_Path = Path;

// ● 날짜
g_DateTiME  = Date_STR;
g_DateTiME += "T";
g_DateTiME += Time_STR;
g_DateTiME += "Z";

// ● 쿼리
g_Query   = Query;

// ● 메세지
g_Message = g_DateTiME + g_Methode + g_Path + g_Query;

// ● 알고리즘
g_Algorithm = "HmacSHA256";

// ● HMAC 시그니처
g_Signature = PGM->uSHA2Hash->HMAC(g_Message, g_SecKEY);

// ● 컨텐츠타입
g_ContentType = "application/json;charset=UTF-8";

// ● 인증문자열 조립
g_Header  = "CEA ";
g_Header += "algorithm="   + g_Algorithm + ", ";
g_Header += "access-key="  + g_AccKEY    + ", ";
g_Header += "signed-date=" + g_DateTiME  + ", ";
g_Header += "signature="   + g_Signature;

// URL 조립
/*
URL  = URL;
URL += Path;

if(Message!="")
{
    URL += "?";
    URL += Message;
}
*/
g_URL  = URL;
//■■■■■■■■■■
//■■■■■■■■■■
//■■■■■■■■■■

    }
    //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩

g_Header = "CEA algorithm=HmacSHA256, access-key=e3ae6995-01ed-43c8-a1a4-669b8ca9aa22, signed-date=181031T095311Z, signature=62a425450db4dc9777a835569d9cd52d93055eb42678ca544e92dd9c1e32fa1a";

    PGM->uAPi_REQ_methode->Text = g_Methode;
    PGM->uAPi_REQ_path->Text    = g_Path;
    PGM->uAPi_REQ_header->Text  = g_Header;
    PGM->uAPi_REQ_message->Text = g_Message;
    PGM->uAPi_REQ_url->Text     = g_URL;
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uAPi_REQUESTClick(TObject *Sender)
{
    int n;
    int cnt,idx,sel,Len;

//    TStringList *FLD;

    UnicodeString mSTR, qSTR, hmacSTR;

    UnicodeString pSTR, vSTR, fSTR, rSTR;
    UnicodeString hostSTR;

    TRESTRequestParameter *param;

    char rDATA[4096];
    //                                                                         .
    idx = PGM->uOPT_extHOSTs->ItemIndex;
    hostSTR = PGM->uOPT_extHOSTs->Items->Strings[idx];

    //▩==▩==▩==▩==▩==▩==▩==▩==▩==▩
    if(hostSTR=="쿠팡")
    {
        sel = PGM->uOPT_extAPis->ItemIndex + 1;

        PGM->uAPi_REP->Lines->Clear();
        /*                                            */
        /* ♣ 요청                                    */
        /*                                            */
        /**/                                        /**/


PGM->uHTTP_CLT->BaseURL = g_URL;

     if(g_Methode=="GET")  PGM->uHTTP_REQ->Method = rmGET;
else if(g_Methode=="POST") PGM->uHTTP_REQ->Method = rmPOST;

PGM->uHTTP_CLT->Accept = g_ContentType;
PGM->uHTTP_CLT->AcceptCharset = "UTF-8, *;q=0.8";

PGM->uHTTP_REQ->Params->Clear();
param = PGM->uHTTP_REQ->Params->AddHeader("Authorization", g_Header);
param->Options = (TRESTRequestParameterOptions) TRESTRequestParameterOption::poDoNotEncode;


//PGM->uHTTP_CLT->Params->Clear();
//PGM->uHTTP_CLT->Params->AddHeader("Content-Type",  g_Header);
//PGM->uHTTP_CLT->Params->AddHeader("Authorization", g_authSTR);

PGM->uHTTP_REQ->Resource = g_Path + "?" + "query=" + g_Query;


PGM->uHTTP_REQ->Execute();


        /**/                                        /**/
        /*                                            */

    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_SangPoom_LiSTClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "상품리스트";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_SangPoom_ADDClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "상품추가";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_SangPoom_UPDATEClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "상품수정";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_SangPoom_REMOVEClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "상품삭제";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_wSTAT_REQClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "작업상태 요청";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_wSTAT_ENDClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "작업상태 완료";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_sSTAT_REQClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "승인상태 요청";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_sSTAT_ENDClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "승인상태 승인";
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_sSTAT_DLYClick(TObject *Sender)
{
PGM->uOUT_React->Caption = "승인상태 보류";
}
//----------------------------------------------------------------------------
void __fastcall TPGM::uTGL_SangPoom_ListClick(TObject *Sender)
{
    char fSTR[1024], zSTR[1024];
    //                                                                         .
    zTGL_SangPoom_List = !zTGL_SangPoom_List;

        cpSTR(fSTR, xSYS.resDiR);
        adSTR(fSTR, "리스트");
        sfSTR(zSTR, "%1d", zTGL_SangPoom_List);
        adSTR(fSTR, zSTR);
        adSTR(fSTR, ".png");

    PGM->uTGL_SangPoom_List->Picture->LoadFromFile(fSTR);
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uTGL_SangPoom_imageClick(TObject *Sender)
{
    char fSTR[1024], zSTR[1024];
    //                                                                         .
    zTGL_SangPoom_image = !zTGL_SangPoom_image;

        cpSTR(fSTR, xSYS.resDiR);
        adSTR(fSTR, "이미지");
        sfSTR(zSTR, "%1d", zTGL_SangPoom_image);
        adSTR(fSTR, zSTR);
        adSTR(fSTR, ".png");

    PGM->uTGL_SangPoom_image->Picture->LoadFromFile(fSTR);
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_mainPainted(TObject *Sender)
{
    int cnt;
    char wSTR[256];
    AnsiString aSTR;
    if(!PGM->uADOconn->Connected) return;
    if(!PGM->uQRY_main->Active) return;
    cnt = PGM->uQRY_main->RecordCount;
    sfSTR(wSTR, "%d Rec", cnt); aSTR = wSTR;
    PGM->uDBmain_RECcnt->Caption = aSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDTE_TodayClick(TObject *Sender)
{
    TDateTime today;
    TDateTime date1, date2;

    // ▶ 오늘
    today = TDateTime::CurrentDate();
    date1 = today;
    date2 = today;

    PGM->uFiND_Calendar1->Date = date1;
    PGM->uFiND_Calendar2->Date = date2;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDTE_YesterdayClick(TObject *Sender)
{
    TDateTime today;
    TDateTime date1, date2;

    // ▶ 어제
    today = TDateTime::CurrentDate();
    date1 = today -1;
    date2 = today;

    PGM->uFiND_Calendar1->Date = date1;
    PGM->uFiND_Calendar2->Date = date2;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDTE_3MonthClick(TObject *Sender)
{
    TDateTime today;
    TDateTime date1, date2;

    unsigned short int y,m,d;
    AnsiString dSTR;
    //                                                                         .
//    today = TDateTime::CurrentDate();
//    dSTR = today.DateString();

//날짜디버깅
//today = TDateTime(2018, 5, 29);

//date1 = IncMonth(today, -3);
//DecodeDate(date1,y,m,d);

//date1 = TDateTime::CurrentDate() -90;
    //                                                                         .
    // ▶ 3개월
    today = TDateTime::CurrentDate();
    date1 = IncMonth(today, -3);
    date2 = TDateTime::CurrentDate();

    PGM->uFiND_Calendar1->Date = date1;
    PGM->uFiND_Calendar2->Date = date2;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDTE_6MonthClick(TObject *Sender)
{
    TDateTime today;
    TDateTime date1, date2;

    // ▶ 6개월
    today = TDateTime::CurrentDate();
    date1 = IncMonth(today, -6);
    date2 = today;

    PGM->uFiND_Calendar1->Date = date1;
    PGM->uFiND_Calendar2->Date = date2;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDTE_1YearClick(TObject *Sender)
{
    TDateTime today;
    TDateTime date1, date2;

    // ▶ 1년
    today = TDateTime::CurrentDate();
    date1 = IncMonth(today, -12);
    date2 = today;

    PGM->uFiND_Calendar1->Date = date1;
    PGM->uFiND_Calendar2->Date = date2;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uQUiTClick(TObject *Sender)
{
    // 프로그램종료
    PGM->Close();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_cn_itm_urlKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_cn_itm_url->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 500);
//    PGM->uLEN_cn_itm_url->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_cn_mkt_nameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_cn_mkt_name->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 50);
//    PGM->uLEN_cn_mkt_name->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_cn_prd_nameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_cn_prd_name->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 200);
//    PGM->uLEN_cn_prd_name->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_sup_urlKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_sup_url->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 200);
//    PGM->uLEN_sup_url->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_mkt_nameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_mkt_name->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 50);
//    PGM->uLEN_mkt_name->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_sel_codKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_sel_cod->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 40);
//    PGM->uLEN_sel_cod->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uiPT_kr_prd_nameKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int Len; char wSTR[256];
//    Len = PGM->uiPT_kr_prd_name->Text.Length();
//    sfSTR(wSTR, "%d/%d", Len, 200);
//    PGM->uLEN_kr_prd_name->Caption = wSTR;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uSPAfterOpen(TDataSet *DataSet)
{
    int n,cnt;

    char wSTR[1024];

    UnicodeString oResult;
    UnicodeString kSTR;

    AnsiString aSTR;
    //                                                                         .
    oResult = DataSet->FieldByName("$oBRANDs")->AsString;

Brands_STR = oResult;

    aSTR = Brands_STR;
    cpSTR(wSTR, aSTR.c_str());

    ///////
    PGM->uFiND_Brand->Items->Clear();

    cpSTR(Brands[000], "브랜드 전체");
    aSTR = Brands[000];
    PGM->uFiND_Brand->Items->Add(aSTR);
    ///////
    cnt = paraCNT_jCOMMA_List(wSTR);
    for(n=1;n<=cnt;n++)
    {
        cpSTR(Brands[n], jCOMMA_List(wSTR, n));
    }
    //                                                                         .
    // 메인화면의 브랜드 콤보박스에 적용

        for(n=1;n<=cnt;n++)
        {
            aSTR = Brands[n];
            PGM->uFiND_Brand->Items->Add(aSTR);
        }

    PGM->uFiND_Brand->Text = Brands[000];
    //                                                                         .
    PGM->uFiND_Brand->ItemIndex = Start_BRAND;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_CustomerCLEARClick(TObject *Sender)
{
    PGM->uFiND_CustomerCODE->Lines->Clear();

    COMPACT_CustomerCODE();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uQRY_mainAfterOpen(TDataSet *DataSet)
{
    int n,cnt;
    //                                                                         .
    // uDB_main 에 체크칼럼 생성
    cnt = Main_TBL_Field_CNT;

    // 체크박스 추가
    PGM->uDB_main->AddCheckBoxColumn(000, 0x0, 0x0);
    //                                                                         .
    PGM->uFiND_STAT->Caption = "검색완료";
    PGM->uFiND_STAT->Repaint();

    zFiNDiNG = 0x0;
    FiNDiNG_LOOPcnt = 000;

    PGM->uBTN_mFiND->Enabled = 0x1;
    PGM->uBTN_mFiND->Refresh();
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_ExcelEXPORTClick(TObject *Sender)
{
    int k;
    int x,y,Jx,Jy;
    int COLcnt, ROWcnt;

    UnicodeString dSTR, fSTR;
    //                                                                         .

// ▶▶ 메인테이블 형상그대로 저장한다
COLcnt = PGM->uDB_main->ColCount;
ROWcnt = PGM->uDB_main->RowCount;

PGM->uEXCEL_wb->Grid->ColCount = COLcnt;
PGM->uEXCEL_wb->Grid->RowCount = ROWcnt;


    // ■ 헤더필드 주입
    // 필드이름 / 필드폭길이 적용
    for(x=1;x<=COLcnt;x++)
    {
        PGM->uEXCEL_wb->Grid->Cells[x-1][000] = Main_TBL_NMEs[x];
        PGM->uEXCEL_wb->Grid->Cells[x-1][001] = Main_TBL_FLDs[x];
        PGM->uEXCEL_wb->Grid->ColWidths[x-1]  = Main_TBL_CLWs[x];
    }

    // ■ 데이타 주입
    for(y=1;y<=ROWcnt;y++)
    {
        for(x=1;x<=COLcnt;x++)
        {
            PGM->uEXCEL_wb->Grid->Cells[x-1][y+1] = PGM->uDB_main->Cells[x-1][y];
        }
    }
    //                                                                         .
    // ★ 엑셀파일저장

    dSTR = xSYS.runDiR;
    dSTR += "/OUT";
    PGM->uSaveFiLE->InitialDir = dSTR;
    PGM->uSaveFiLE->FileName = "RESULTs.xls";

    PGM->uSaveFiLE->Execute(NULL);

    fSTR = PGM->uSaveFiLE->FileName;

    PGM->uEXCEL->XLSExport(fSTR, "검색결과");
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_SendFLDsClick(TObject *Sender)
{
    TTreeNode *node;

    int n,p,k;
    int cnt,pcnt,idx,seq,CHKidx,Len;

    char wSTR[1024], bSTR[1024];
    AnsiString aSTR;
    UnicodeString zzSTR;
    //                                                                         .
    // ▶▶ 체크된 항목만 검색결과 (엑셀출력항목) 로 보낸다
    cnt = PGM->uEXCEL_FLDs->RowCount;

    for(n=2;n<=cnt;n++)
    {
        if(PGM->uEXCEL_FLDs->IsChecked(000, n-1)==0x1)
        {
            CHKidx = PGM->uEXCEL_FLDs->Cells[2][n-1].ToInt();

            // 이미 출력리스트에 있으면 스킵 !
            pcnt = PGM->uEXCEL_OUTs->Items->Count;
            for(p=1;p<=pcnt;p++)
            {
                node = PGM->uEXCEL_OUTs->Items->Item[p-1];

                aSTR = node->Text;

                cpSTR(wSTR, aSTR.c_str());

                idx = (wSTR[0]-'0')*10 + (wSTR[1]-'0');

                if(CHKidx==idx)
                {
                    goto NEXT_Checked_FLD;
                }
            }

            // 출력리스트에 체크된 항목들 추가
            Len = 15 - lenSTR(Main_TBL_FLDs[n]);
            CHAR_String(bSTR, '_', Len);

            sfSTR(wSTR, "%02d : %s%s : %s",
                        Main_TBL_FNOs[n],
                        Main_TBL_FLDs[n],
                        bSTR,
                        Main_TBL_NMEs[n]);

            zzSTR = wSTR;

            PGM->uEXCEL_OUTs->Items->Add(NULL, zzSTR);

++Main_TBL_SAVEs_FLDcnt;

seq = SEQ_Main_TBL_Field(CHKidx);
Main_TBL_SAVEs[Main_TBL_SAVEs_FLDcnt]    = Main_TBL_FNOs[seq];
Main_TBL_SaveCLWs[Main_TBL_SAVEs_FLDcnt] = Main_TBL_CLWs[seq];

NEXT_Checked_FLD: ;
        }
    }
    //                                                                         .

SYNC_main_FLDs();
SYNC_main_CLWs();

AutoSAVE_main_FLDs();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_OUTsDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
    Accept = true;
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_OUTsDragDrop(TObject *Sender, TObject *Source, int X,
          int Y)
{
    int n,k1,k2;
    TNodeAttachMode    attachMode;
    TTreeNode *destNode, *selNode;
    int from, to, swap;

    char wSTR[1024];
    AnsiString aSTR;
    //                                                                         .
    if(Source->ClassNameIs("TTreeView") && Sender->ClassNameIs("TTreeView"))
    {
        // 타겟노드
        destNode = PGM->uEXCEL_OUTs->GetNodeAt(X, Y);

        // 선택된노드
        selNode = PGM->uEXCEL_OUTs->Selected;

if(destNode==NULL || selNode==NULL) return;

from = selNode->Index+1;
to   = destNode->Index+1;

        // 타겟노드에 선택된 노드를 추가한다
        attachMode = naInsert;
        selNode->MoveTo(destNode, attachMode);

        PGM->uEXCEL_OUTs->FullExpand();
    }
    //                                                                         .
    if(from < to)
    {
        --to;

        k1 = Main_TBL_SAVEs[from];
        k2 = Main_TBL_SaveCLWs[from];

        for(n=from;n<to;n++)
        {
            Main_TBL_SAVEs[n]    = Main_TBL_SAVEs[n+1];
            Main_TBL_SaveCLWs[n] = Main_TBL_SaveCLWs[n+1];
        }
        Main_TBL_SAVEs[to]    = k1;
        Main_TBL_SaveCLWs[to] = k2;
    }
    else
    {
        k1 = Main_TBL_SAVEs[from];
        k2 = Main_TBL_SaveCLWs[from];

        for(n=from;n>to;n--)
        {
            Main_TBL_SAVEs[n]    = Main_TBL_SAVEs[n-1];
            Main_TBL_SaveCLWs[n] = Main_TBL_SaveCLWs[n-1];
        }
        Main_TBL_SAVEs[to]    = k1;
        Main_TBL_SaveCLWs[to] = k2;
    }
    //                                                                         .

SYNC_main_FLDs();
SYNC_main_CLWs();

AutoSAVE_main_FLDs();

}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_ExcelRESETClick(TObject *Sender)
{
    int n,seq,cnt,Len;
    char wSTR[1024], kSTR[1024], bSTR[1024];
    AnsiString zzSTR;
    //                                                                         .
    // 기본출력칼럼 리셋

    cnt = Main_TBL_DEFAULTs_FLDcnt;
    for(n=1;n<=cnt;n++)
    {

Main_TBL_SAVEs[n]    = Main_TBL_FNOs[n+1];
Main_TBL_SaveCLWs[n] = Main_TBL_CLWs[n+1];

    }

Main_TBL_SAVEs_FLDcnt = cnt;

    //                                                                         .

SYNC_OUT_FLDs();
SYNC_main_FLDs();
SYNC_main_CLWs();

AutoSAVE_main_FLDs();

}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_OUTsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    int n,idx,cnt;
    TTreeNode *node;

    // 선택한 노드삭제
    if(Key==VK_DELETE)
    {
        node = PGM->uEXCEL_OUTs->Selected;

        if(node==NULL) return;

idx = node->Index+1;


cnt = PGM->uEXCEL_OUTs->Items->Count;
for(n=idx;n<=cnt;n++)
{
    Main_TBL_SAVEs[n]    = Main_TBL_SAVEs[n+1];
    Main_TBL_SaveCLWs[n] = Main_TBL_SaveCLWs[n+1];
}

    /*                       */
    /**/  node->Delete();  /**/
    /*                       */
    Main_TBL_SAVEs_FLDcnt = PGM->uEXCEL_OUTs->Items->Count;


SYNC_OUT_FLDs();
SYNC_main_FLDs();

AutoSAVE_main_FLDs();

    }
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_mainColumnMoved(TObject *Sender, int FromIndex, int ToIndex)
{
    int n,k1,k2;
    int from, to, swap;
    //                                                                         .
    // ▶▶ 메인테이블 칼럼위치 변경시 적용
    from = FromIndex;
    to   = ToIndex;
    //                                                                         .
    if(from < to)
    {
//        --to;

        k1 = Main_TBL_SAVEs[from];
        k2 = Main_TBL_SaveCLWs[from];

        for(n=from;n<to;n++)
        {
            Main_TBL_SAVEs[n]    = Main_TBL_SAVEs[n+1];
            Main_TBL_SaveCLWs[n] = Main_TBL_SaveCLWs[n+1];
        }
        Main_TBL_SAVEs[to]    = k1;
        Main_TBL_SaveCLWs[to] = k2;
    }
    else
    {
        k1 = Main_TBL_SAVEs[from];
        k2 = Main_TBL_SaveCLWs[from];

        for(n=from;n>to;n--)
        {
            Main_TBL_SAVEs[n]    = Main_TBL_SAVEs[n-1];
            Main_TBL_SaveCLWs[n] = Main_TBL_SaveCLWs[n-1];
        }
        Main_TBL_SAVEs[to]    = k1;
        Main_TBL_SaveCLWs[to] = k2;
    }
    //                                                                         .


SYNC_OUT_FLDs();

AutoSAVE_main_FLDs();

    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_mainEndColumnSize(TObject *Sender, int ACol)
{
    //                                                                         .
    // ▶▶ 메인테이블 칼럼폭 변경시 적용

AutoSAVE_main_FLDs();

    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uDB_mainClickCell(TObject *Sender, int ARow, int ACol)
{
    int x,y,chk;
    //                                                                         .
    x = ACol;
    y = ARow;
/*
    if(x==000 && y==000)
    {
        chk = PGM->uEXCEL_FLDs->IsChecked(000, 000);

        // 전체셀 체크/언체크
        if(!chk) PGM->uEXCEL_FLDs->CheckAll(0);
        else     PGM->uEXCEL_FLDs->UnCheckAll(0);
    }
*/
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_FLDsCheckBoxClick(TObject *Sender, int ACol, int ARow,
          bool State)
{
    int x,y,chk;
    //                                                                         .
    x = ACol;
    y = ARow;

    if(x==000 && y==000)
    {
        chk = PGM->uEXCEL_FLDs->IsChecked(x, y);
        // 전체셀 체크/언체크
        if(chk) PGM->uEXCEL_FLDs->CheckAll(0);
        else    PGM->uEXCEL_FLDs->UnCheckAll(0);
    }
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uEXCEL_FLDsClickCell(TObject *Sender, int ARow, int ACol)
{
    int x,y,chk;
    //                                                                         .
    x = ACol;
    y = ARow;

    // 각각셀만 클릭해도,, 라인이 체크/언체크 되게한다
    chk = PGM->uEXCEL_FLDs->IsChecked(000, y);

    PGM->uEXCEL_FLDs->SetCheckBoxState(000,y,!chk);
    //                                                                         .
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uPageControlPageChange(TObject *Sender)
{
    int idx;

    idx = PGM->uPageControl->TabIndex;

    switch(idx)
    {
    ///////
    case 0:

PGM->uLogin_BTN->SetFocus();

    break;
    ///////
    }
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_XLS_importClick(TObject *Sender)
{
    //엑셀 임포트 팝업표시
    pEXCEL_import->Show();
}
//---------------------------------------------------------------------------
void __fastcall TPGM::uBTN_XLS_exportClick(TObject *Sender)
{
    int n;
    int cnt,rcnt,chk;
    char wSTR[1024];

    AnsiString aSTR;
    //                                                                         .

    //■■■■■■■■■■
    // 선택된 건수표시
    cnt = PGM->uDB_main->RowCount-1;
    rcnt = 000;
    for(n=1;n<=cnt;n++)
    {
        chk = PGM->uDB_main->IsChecked(0, n);

        rcnt += (0x0<chk);
    }

Export_SELcnt = rcnt;

    sfSTR(wSTR, "선택건 출력 ( %d 건)", rcnt);
    aSTR = wSTR;
    pEXCEL_export->uOPT_XLS_export_Type->Items->Strings[0] = aSTR;
    //■■■■■■■■■■
    // 검색된 전체 건수표시
    rcnt = PGM->uDB_main->RowCount-1;

Export_ALLcnt = rcnt;

    sfSTR(wSTR, "검색된 전체건 출력 ( %d 건)", rcnt);
    aSTR = wSTR;
    pEXCEL_export->uOPT_XLS_export_Type->Items->Strings[1] = aSTR;
    //■■■■■■■■■■

    //엑셀 익스포트 팝업표시
    pEXCEL_export->Show();
    //                                                                         .
}
//---------------------------------------------------------------------------






