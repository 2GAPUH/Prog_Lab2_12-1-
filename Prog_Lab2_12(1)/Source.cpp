#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "StrappedArray.h"

/*Массив представлен дескриптором. Количество строк
определяется полем дескриптора. Количество элементов строк
определяется динамическим массивом размеров.*/


int main()
{
	descriptor desc;
	int type = 0;
	bool flug1 = 0, runing = 1;

	while (runing)
	{
		printf_s("\
0 - Exit\n\
1 - Manual array filling\n\
2 - Text file array filling\n\
3 - Bin file array filling\n");
		printf_s("Enter what you want to do: ");
		scanf_s("%d", &type);
		switch (type)
		{
		case 0:
			if (flug1)
				runing = 0;
			else
				printf_s("Need to filling Array!\n");
			break;

		case 1:
			ManualArrayFilling(&desc);
			flug1 = 1;
			break;

		case 2:
			TextFileArrayFilling(&desc);
			flug1 = 1;
			break;

		case 3:
			BinFileArrayFilling(&desc);
			flug1 = 1;
			break;

		default:
			printf_s("Invalid type! Try again.\n");
		}
	}

	runing = 1;

	while (runing)
	{
		printf_s("\
0 - Exit\n\
1 - Print array\n\
2 - Text file array save\n\
3 - Bin file array save\n\
4 - Add new line\n\
5 - Delete last line\n\
6 - Shift rows\n\
7 - Columns shift\n");
		printf_s("Enter what you want to do: ");
		scanf_s("%d", &type);
		switch (type)
		{
		case 0:
			runing = 0;
			break;

		case 1:
			ArrayPrinting(desc);
			break;

		case 2:
			ArraySaveTextFile(desc);
			break;

		case 3:
			ArraySaveBinFile(desc);
			break;

		case 4:
			AddLine(&desc);
			break;

		case 5:
			DeleteLine(&desc);
			break;

		case 6:
			RowsShift(&desc);
			break;

		case 7:
			ColumnsShift(&desc);
			break;

		default:
			printf_s("Invalid type! Try again.\n");
		}
	};

	MemoryFree(&desc);

	return 0;
}