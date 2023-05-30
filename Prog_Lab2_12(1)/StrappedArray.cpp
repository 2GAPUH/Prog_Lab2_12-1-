#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include "StrappedArray.h"

void GetRows(int* rows)
{
	do {
		printf_s("Enter rows: ");
		scanf_s("%d", rows);
		if (*rows <= 0)
			printf_s("Invalid value! Try again.\n");
		else
			break;
	} while (true);
}

void MainMalloc(descriptor * desc)
{
	desc->array = (int**)malloc(sizeof(int*) * desc->rows);
	if (desc->array == 0)
	{
		printf_s("Can't add memmory!\n");
		exit(1);
	}

	desc->columnsCount = (int*)malloc(sizeof(int) * desc->rows);
	if (desc->columnsCount == 0)
	{
		printf_s("Can't add memmory!\n");
		exit(1);
	}
}

void ManualArrayFilling(descriptor* desc)
{
	if (desc->array != NULL)
		MemoryFree(desc);

	GetRows(&desc->rows);
	MainMalloc(desc);

	for (int i = 0; i < desc->rows; i++)
	{
		while (true)
		{
			printf_s("Enter count of columns in %d line: ", i + 1);
			scanf_s("%d", &desc->columnsCount[i]);
			if (desc->columnsCount[i] <= 0)
				printf_s("Invalid value!\n");
			else
				break;
		}
		desc->array[i] = (int*)malloc(sizeof(int) * desc->columnsCount[i]);
		if (desc->array[i] == 0)
		{
			printf_s("Can't add memmory!\n");
			exit(1);
		}
		for (int j = 0; j < desc->columnsCount[i]; j++)
		{
			printf_s("Enter array[%d][%d]: ", i + 1, j + 1);
			scanf_s("%d", &desc->array[i][j]);
		}
	}
}

void ArrayPrinting(descriptor const desc)
{
	for (int i = 0; i < desc.rows; i++)
	{
		for (int j = 0; j < desc.columnsCount[i]; j++)
			printf_s("%5d\t", desc.array[i][j]);
		printf_s("\n");
	}
}

void MemoryFree(descriptor* desc)
{
	for (int i = 0; i < desc->rows; i++)
		free(desc->array[i]);
	free(desc->array);
	free(desc->columnsCount);

	desc->rows = 0;
	desc->columnsCount = NULL;
	desc->array = NULL;
}

void GetFileName(char fileName[])
{
	printf_s("Enter file name('file.txt'): ");
	while (getchar() != '\n');
	gets_s(fileName, 20);
}

void ArraySaveTextFile(descriptor const desc)
{
	FILE* f;
	char fileName[20];

	GetFileName(fileName);
	if (fopen_s(&f, fileName, "w") != 0)
	{
		printf_s("Error opening file.\n");
		return;
	}

	fprintf_s(f, "%d\n", desc.rows);

	for (int i = 0; i < desc.rows; i++)
	{
		fprintf_s(f, "%d ", desc.columnsCount[i]);
		for (int j = 0; j < desc.columnsCount[i]; j++)
			fprintf_s(f, "%d ", desc.array[i][j]);
		fprintf_s(f, "\n");
	}

	fclose(f);
}

void TextFileArrayFilling(descriptor* desc)
{
	FILE* f;
	char fileName[20];

	if (desc->array != NULL)
		MemoryFree(desc);

	GetFileName(fileName);
	if (fopen_s(&f, fileName, "r") != 0)
	{
		printf_s("Error opening file.\n");
		return;
	}

	fscanf_s(f, "%d", &desc->rows);

	MainMalloc(desc);

	for (int i = 0; i < desc->rows; i++)
	{
		fscanf_s(f, "%d", &desc->columnsCount[i]);
		desc->array[i] = (int*)malloc(sizeof(int) * desc->columnsCount[i]);
		if (desc->array[i] == 0)
		{
			printf_s("Can't add memmory!\n");
			exit(1);
		}
		for (int j = 0; j < desc->columnsCount[i]; j++)
		{
			fscanf_s(f, "%d", &desc->array[i][j]);
		}
	}

	fclose(f);

	printf_s("Succesful filling.\n");
}

void ArraySaveBinFile(descriptor const desc)
{
	FILE* f;
	char fileName[20];

	GetFileName(fileName);
	if (fopen_s(&f, fileName, "wb") != 0)
	{
		printf_s("Error opening file.\n");
		return;
	}

	fwrite(&desc.rows, sizeof(int), 1, f);

	for (int i = 0; i < desc.rows; i++)
	{
		fwrite(&desc.columnsCount[i], sizeof(int), 1, f);

		fwrite(desc.array[i], sizeof(int), desc.columnsCount[i], f);
	}

	fclose(f);
}

void BinFileArrayFilling(descriptor* desc)
{
	FILE* f;
	char fileName[20];

	if (desc->array != NULL)
		MemoryFree(desc);

	GetFileName(fileName);
	if (fopen_s(&f, fileName, "rb") != 0)
	{
		printf_s("Error opening file.\n");
		return;
	}

	fread(&desc->rows, sizeof(int), 1, f);

	MainMalloc(desc);

	for (int i = 0; i < desc->rows; i++)
	{
		fread(&desc->columnsCount[i], sizeof(int), 1, f);
		desc->array[i] = (int*)malloc(sizeof(int) * desc->columnsCount[i]);
		if (desc->array[i] == 0)
		{
			printf_s("Can't add memmory!\n");
			exit(1);
		}

		fread(desc->array[i], sizeof(int), desc->columnsCount[i], f);
	}

	fclose(f);

	printf_s("Succesful filling.\n");
}

void AddLine(descriptor* desc)
{

	desc->columnsCount = (int*)realloc(desc->columnsCount, ++desc->rows * sizeof(int));
	desc->array = (int**)realloc(desc->array, desc->rows * sizeof(int*));
	

	while (true)
	{
		printf_s("Enter count of columns in line: ");
		scanf_s("%d", &desc->columnsCount[desc->rows - 1]);
		if (desc->columnsCount[desc->rows - 1] <= 0)
			printf_s("Invalid value!\n");
		else
			break;
	}
	desc->array[desc->rows - 1] = (int*)malloc(sizeof(int) * desc->columnsCount[desc->rows - 1]);

	for (int i = 0; i < desc->columnsCount[desc->rows - 1]; i++)
	{
		printf_s("Enter Array[%d][%d]", desc->rows, i);
		scanf_s("%d", &desc->array[desc->rows - 1][i]);
	}
}

void DeleteLine(descriptor* desc)
{
	if (desc->array == NULL)
		return;

	if (desc->rows == 1)
	{
		MemoryFree(desc);
		return;
	}

	desc->rows--;
	free(desc->array[desc->rows]);
}

void RowsShift(descriptor* desc)
{
	if (desc->rows <= 1)
		return;

	int* tmp = desc->array[desc->rows - 1];
	for (int i = desc->rows - 1; i > 0; i--)
	{
		desc->array[i] = desc->array[i - 1];
	}
	desc->array[0] = tmp;

	int j = desc->columnsCount[desc->rows - 1];
	for (int i = desc->rows - 1; i > 0; i--)
	{
		desc->columnsCount[i] = desc->columnsCount[i - 1];
	}
	desc->columnsCount[0] = j;

	ArrayPrinting(*desc);
}

void ColumnsShift(descriptor* desc)
{
	int tmp = 0;
	for (int i = 0; i < desc->rows; i++)
		for (int j = desc->columnsCount[i] - 1; j > 0 ; j--)
		{
			desc->array[i][j] ^= desc->array[i][j - 1] ^= desc->array[i][j] ^= desc->array[i][j - 1];
		}

	ArrayPrinting(*desc);
}

//Написать фyн-цию которая прокручивает строки на 1 элемент вперёд
