#include <stdio.h>
#include <stdlib.h>

#define HanoiError 42

void InitVector_Hanoi(int ***Vector_Hanoi, int s32_NumPillar, int s32_NumRing);
void BuildHanoi(int ***Vector_Hanoi, int s32_NumRing);
void PrintBeforMove(int ***Vector_Hanoi, int s32_NumPillar, int s32_NumRing);
void PrintAfterMove(int ***Vector_Hanoi, int s32_numPillarm, int s32_NumRing);
int Tower_of_Hanoi(int ***Vector_Hanoi, int StartNumPillar, int StartNumRing, int VectorPilarSize, int VectorRingSize);
int MaxSizeRing, MaxSizePillar;
int VectorSizeRing, VectorSizePillar;
int BeginingMoveCount, HanoiEndFlag = 0;
int recursionCurrentPillarCount, recursionCurrentRingCount, recursionTargetRingCount, recursionTargetPillarCount = 0;
int LeftToRightOverFlag, RightToLeftOverFlag = 0;
int CurrentPillarPosition = 0;
int CurrentRingPosition = 0;


void main()
{
	
	
	
	printf("Enter numbr of Ring and Pillar\n Number of Ring : ");
	scanf_s("%d", &MaxSizeRing);
	printf("\n");
	printf("Number of Pillar : ");
	scanf_s("%d", &MaxSizePillar);
	if (MaxSizePillar < 3) /* Least Number of Pillar 3*/
	{
		printf("Please Enter Over 3\n Number of Pillar");
		scanf_s("%d", &MaxSizePillar);
	}
	else
	{
		;
	}
	VectorSizePillar = MaxSizePillar - 1;
	VectorSizeRing = MaxSizeRing - 1;

	printf("\n");
	printf("The Entered Number is %d(Number of Ring) and %d(Number of Pillar)\n", MaxSizeRing, MaxSizePillar);

	/* 2x2 Vector of Tower*/
	int **Vector_Hanoi; 
	Vector_Hanoi = (int**)malloc(sizeof(int*) * MaxSizeRing);
	for (int SizeRing = 0; SizeRing < MaxSizeRing; SizeRing++)
	{
		Vector_Hanoi[SizeRing] = (int*)malloc(sizeof(int) * MaxSizePillar);
	}
	
	int TargetRingPosition = VectorSizeRing;
	int TargetPillarPosition = 0;

	InitVector_Hanoi(&Vector_Hanoi, MaxSizePillar, MaxSizeRing);
	BuildHanoi(&Vector_Hanoi, MaxSizeRing);
	PrintBeforMove(&Vector_Hanoi, MaxSizePillar, MaxSizeRing);

	/*Run Tower of Hanoi*/
	Tower_of_Hanoi(&Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);


	PrintAfterMove(&Vector_Hanoi, MaxSizePillar, MaxSizeRing);


	for (int VetorFreeNum = 0; VetorFreeNum < MaxSizeRing; VetorFreeNum++)
	{
		free(Vector_Hanoi[VetorFreeNum]);
	}
	free(Vector_Hanoi);
	if(Tower_of_Hanoi(&Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition) == HanoiError)
	{
		printf("HanoiError");
	}

		
}
void InitVector_Hanoi(int*** Vector_Hanoi, int NumPillar, int NumRing)
{
	for (int numinit = 0; numinit < NumRing; numinit++)
	{
		for (int numinit2 = 0; numinit2 < NumPillar; numinit2++)
		{
			(*Vector_Hanoi)[numinit][numinit2] = 0;
		}
	}
	
}

void BuildHanoi(int*** Vector_Hanoi,int NumRing)
{

	for (int numbuild = 0; numbuild < NumRing; numbuild++)
	{
		(*Vector_Hanoi)[numbuild][0] = (numbuild+1);
	}
}

void PrintBeforMove(int*** Vector_Hanoi, int NumPillar, int NumRing)
{
	printf("The Tower Hanoi Befor Move\n");
	for (int num = 0; num < NumRing; num++)
	{
		for (int num2 = 0; num2 < NumPillar; num2++)
		{
			printf("[%d]  ", (*Vector_Hanoi)[num][num2]);
		}
		printf("\n");
	}
}
void PrintAfterMove(int*** Vector_Hanoi, int NumPillar, int NumRing)
{
	printf("The Tower Hanoi After Move \n");
	for (int numMove = 0; numMove < NumRing; numMove++)
	{
		for (int numMove2 = 0; numMove2 < NumPillar; numMove2++)
		{
			printf("[%d]  ", (*Vector_Hanoi)[numMove][numMove2]);
		}
		printf("\n");
	}
}

int Tower_of_Hanoi(int*** Vector_Hanoi, int CurrentPillarPosition, int CurrentRingPosition, int TargetPillarPosition, int TargetRingPosition)
{
	if(((*Vector_Hanoi)[0][(VectorSizePillar)]) != 0)
	{
		return HanoiEndFlag;
	}
	else if( (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition]) < MaxSizePillar) && (BeginingMoveCount < MaxSizePillar))
	{
		
		if ((*Vector_Hanoi)[TargetRingPosition][TargetPillarPosition+1] == 0) /* 최초 데이터 이동  */
		{
			
			(*Vector_Hanoi)[TargetRingPosition][TargetPillarPosition+1] = (*Vector_Hanoi)[CurrentRingPosition][0];
			(*Vector_Hanoi)[CurrentRingPosition][0] = 0;
			
			BeginingMoveCount++;
			CurrentRingPosition = CurrentRingPosition + 1;
			recursionCurrentRingCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, 0, CurrentRingPosition , TargetPillarPosition, TargetRingPosition);
			
		}
		else 
		{
			TargetPillarPosition = TargetPillarPosition + 1;
			recursionTargetPillarCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition , TargetRingPosition);
		}
		
	}
	
	else if (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] != 0) && (LeftToRightOverFlag == 0))  /* Move Left To Right */
	{
		if(BeginingMoveCount == (MaxSizePillar - 1))
		{
			
			CurrentRingPosition = 0;
			TargetPillarPosition = 0;
			recursionCurrentRingCount = 0;
			recursionTargetPillarCount = 0;
			BeginingMoveCount = MaxSizePillar;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		
		else if ((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] < (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])/* Target Y Position up*/
		{
			TargetRingPosition = TargetRingPosition -1;
			recursionTargetRingCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((TargetRingPosition == 0) && (TargetPillarPosition != (MaxSizePillar-1) )&&  ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] < (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition])) /*Target X Position >*/
		{
			TargetPillarPosition = TargetPillarPosition + 1;
			TargetRingPosition = (VectorSizeRing);
			recursionTargetPillarCount++;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] == 0)/* Current Y Position Down */
		{
			CurrentRingPosition = CurrentRingPosition + 1;
			recursionCurrentRingCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((TargetRingPosition == (MaxSizeRing-1) && (TargetPillarPosition != (MaxSizePillar-1) && (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] > (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])))/* Current X Position > */
		{
			CurrentPillarPosition = CurrentPillarPosition + 1;
			CurrentRingPosition = 0;
			recursionCurrentPillarCount ++;
			recursionCurrentRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] == 0) /*Data 이동 */
		{
			(*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] = (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition];
			(*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] = 0;
			TargetRingPosition = TargetRingPosition + recursionTargetRingCount;
			TargetPillarPosition = TargetPillarPosition - recursionTargetPillarCount;
			CurrentPillarPosition = 0; /* 현제 좌표 초기화 */
			CurrentRingPosition = 0;
			recursionCurrentPillarCount = 0;
			recursionCurrentRingCount = 0;
			recursionTargetPillarCount = 0;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
			
		}
		else if((CurrentPillarPosition == (MaxSizePillar-1) && (TargetPillarPosition == (MaxSizePillar-1) && (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] > (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition]))) /* Left < Right End Flag */
		{
			LeftToRightOverFlag = 0;
			RightToLeftOverFlag = 1;
			TargetRingPosition = (VectorSizeRing);
			TargetPillarPosition = 0;
			CurrentPillarPosition = (VectorSizePillar); 
			CurrentRingPosition = 0;
			recursionCurrentPillarCount = 0;
			recursionCurrentRingCount = 0;
			recursionTargetPillarCount = 0;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}

	

		

	}

	else if (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] != 0) && (RightToLeftOverFlag == 0))/* Move Right To Left*/
	{
		if ((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] < (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])/* Target Y Position up*/
		{
			TargetRingPosition = TargetRingPosition -1;
			recursionTargetRingCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((TargetRingPosition == 0) && (TargetPillarPosition != (MaxSizePillar-1) )&&  ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] < (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition])) /*Target X Position >*/
		{
			TargetPillarPosition = TargetPillarPosition + 1;
			TargetRingPosition = (VectorSizeRing);
			recursionTargetPillarCount++;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] == 0)/* Current Y Position Down */
		{
			CurrentRingPosition = CurrentRingPosition - 1;
			recursionCurrentRingCount ++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if((TargetRingPosition == (MaxSizeRing-1) && (TargetPillarPosition != (MaxSizePillar-1) && (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] > (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])))/* Current X Position < */
		{
			CurrentPillarPosition = CurrentPillarPosition + 1;
			CurrentRingPosition = 0;
			recursionCurrentPillarCount++;
			recursionCurrentRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] == 0) /*Data 이동 */
		{
			(*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] = (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition];
			(*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] = 0;
			TargetRingPosition = 0;
			TargetPillarPosition = 0;
			CurrentPillarPosition = CurrentPillarPosition + recursionCurrentPillarCount; /* 현제 좌표 초기화 */
			CurrentRingPosition = CurrentRingPosition - recursionCurrentRingCount;
			recursionCurrentPillarCount = 0;
			recursionCurrentRingCount = 0;
			recursionTargetPillarCount = 0;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
			
		}
		else if((CurrentPillarPosition == (MaxSizePillar-1) && (TargetPillarPosition == (MaxSizePillar-1) && (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] > (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition]))) /* Left > Right End Flag */
		{
			LeftToRightOverFlag = 1;
			RightToLeftOverFlag = 0;
			TargetRingPosition = (VectorSizeRing);
			TargetPillarPosition = 0;
			CurrentPillarPosition = (VectorSizePillar); 
			CurrentRingPosition = 0;
			recursionCurrentPillarCount = 0;
			recursionCurrentRingCount = 0;
			recursionTargetPillarCount = 0;
			recursionTargetRingCount = 0;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
	}	
	else
	{
		return HanoiError;
	}


}

