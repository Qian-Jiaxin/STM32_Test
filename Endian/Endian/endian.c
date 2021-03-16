#include "endian.h"

int IsBigEndian(void)
{
	short int a = 0x1122;
	char b = *(char *)&a;
	if(b == 0x11)//大端
	{
		return 1;
	}
	else//小端
	{
		return 0;
	}
}
