//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.NetEncoding.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.HttpClientComponent.hpp>
#include <System.Net.URLClient.hpp>
#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TProgressBar *ProgressBar1;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TButton *Button1;
	TNetHTTPClient *NetHTTPClient1;
	TNetHTTPClient *NetHTTPClient2;
	TMemo *Memo1;
	TLabel *Label1;
	void __fastcall NetHTTPClient2ReceiveData(TObject * const Sender, __int64 AContentLength,
          __int64 AReadCount, bool &AAbort);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
String __fastcall sEstraiDati( const String s, const String ultimo, const String primo );
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
const char sito[] = "aHR0cHM6Ly9rZWVwdGlrdG9rLmNvbS8=";
//---------------------------------------------------------------------------
#endif
