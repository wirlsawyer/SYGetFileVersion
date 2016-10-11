//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
        std::wstring m_appPath = ExtractFilePath(Application->ExeName).c_str();

	GetVersionWithFile( (m_appPath+L"SYGetFileVersionDemo.exe").c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetVersionWithFile(const wchar_t *pFile)
{
     DWORD  verHandle = NULL;
     UINT   size      = 0;
     LPBYTE lpBuffer  = NULL;
     DWORD  verSize   = GetFileVersionInfoSize( pFile, &verHandle);

     if (verSize != NULL)
     {
    	LPSTR verData = new char[verSize];

        if (GetFileVersionInfo( pFile, verHandle, verSize, verData))
    	{
            if (VerQueryValue(verData,L"\\",(VOID FAR* FAR*)&lpBuffer,&size))
            {
            	if (size)
            	{
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                    	int major   = HIWORD(verInfo->dwFileVersionMS);
	                int minor   = LOWORD(verInfo->dwFileVersionMS);
                        int release = HIWORD(verInfo->dwFileVersionLS);
                    	int build   = LOWORD(verInfo->dwFileVersionLS);
                        wchar_t wszBuf[512];
                        memset(wszBuf, 0, sizeof(wszBuf));
                        wsprintf(wszBuf, L"major=%d minor=%d release=%d build=%d", major, minor, release, build);
                	OutputDebugString(wszBuf);
                    }
                }
            }
        }
        delete[] verData;
     }

}


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (OpenDialog1->Execute())
	{
  		GetVersionWithFile(OpenDialog1->FileName.w_str() );
	}
}
//---------------------------------------------------------------------------

