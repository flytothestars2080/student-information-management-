#include<stdbool.h>
#include<stdlib.h>
bool login(void);
void Manage();
int main()
{
	bool nes=login();
	if(nes==true)
	{ 
		
		system("cls");
		
	}
	Manage();
	return 0;
}