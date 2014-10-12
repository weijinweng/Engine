#include "Canvas.h"






int main(int argv, char* argc[])
{
	if(!CVS_Initialize())
		return false;
	Editor editorApp;
	editorApp.InitializeApp();

	editorApp.Run();

	editorApp.End();
}