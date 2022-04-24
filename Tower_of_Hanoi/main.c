#include <stdio.h>
#include <stdlib.h>

#define HanoiError 0

void InitVector_Hanoi(int ***Vector_Hanoi, int s32_NumPillar, int s32_NumRing);
void BuildHanoi(int ***Vector_Hanoi, int s32_NumRing);
void PrintBeforMove(int ***Vector_Hanoi, int s32_NumPillar, int s32_NumRing);
void PrintAfterMove(int ***Vector_Hanoi, int s32_numPillarm, int s32_NumRing);
int Tower_of_Hanoi(int ***Vector_Hanoi, int StartNumPillar, int StartNumRing, int VectorPilarSize, int VectorRingSize);
int MaxSizeRing, MaxSizePillar;

int BeginingMoveCount = 0;
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
	printf("\n");
	printf("The Entered Number is %d(Number of Ring) and %d(Number of Pillar)\n", MaxSizeRing, MaxSizePillar);

	/* 2x2 Vector of Tower*/
	int **Vector_Hanoi; 
	Vector_Hanoi = (int**)malloc(sizeof(int*) * MaxSizeRing);
	for (int VectorSizeRing = 0; VectorSizeRing < MaxSizeRing; VectorSizeRing++)
	{
		Vector_Hanoi[VectorSizeRing] = (int*)malloc(sizeof(int) * MaxSizePillar);
	}
	
	int TargetRingPosition = MaxSizeRing - 1;
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
int dbgcurrposring, dbgcurpospillar;
int Tower_of_Hanoi(int*** Vector_Hanoi, int CurrentPillarPosition, int CurrentRingPosition, int TargetPillarPosition, int TargetRingPosition)
{
	printf("pos : %d\n", CurrentPillarPosition);
	if( (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition]) <= MaxSizePillar) && (BeginingMoveCount <= MaxSizePillar))
	{
		
		if ((*Vector_Hanoi)[TargetRingPosition][CurrentPillarPosition+1] == 0) /* complete */
		{
			
			(*Vector_Hanoi)[TargetRingPosition][CurrentPillarPosition+1] = (*Vector_Hanoi)[CurrentRingPosition][0];
			(*Vector_Hanoi)[CurrentRingPosition][0] = 0;
			
			BeginingMoveCount++;
			
			return Tower_of_Hanoi(Vector_Hanoi, 0, CurrentRingPosition +1 , TargetPillarPosition, TargetRingPosition);
			
		}
		else 
		{
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition+1, CurrentRingPosition, TargetPillarPosition , TargetRingPosition);
		}
		
	}
	else if (BeginingMoveCount == (MaxSizePillar - 1))
	{
		BeginingMoveCount++;
		CurrentRingPosition = 0;
		CurrentPillarPosition = 0;
	}
	else if (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] != 0) && (LeftToRightOverFlag == 0))  /* Move Left To Right */
	{
		
		if ((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] < (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])
		{
			recursionTargetRingCount++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition - 1);
		}

		else if ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] == 0)
		{
			(*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] = (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition];
			(*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] = 0;
			TargetRingPosition = TargetRingPosition + recursionTargetRingCount;
			TargetPillarPosition = TargetPillarPosition - recursionTargetPillarCount;
			dbgcurpospillar = CurrentPillarPosition;
			recursionTargetRingCount = 0;
			recursionTargetPillarCount = 0;
			
			if (CurrentRingPosition < MaxSizeRing)
			{
				CurrentRingPosition = CurrentRingPosition + 1;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
			}
			else
			{
				CurrentRingPosition = CurrentRingPosition + recursionCurrentRingCount;
				CurrentPillarPosition = CurrentPillarPosition - recursionCurrentPillarCount;
				
				recursionCurrentRingCount = 0;
				recursionCurrentPillarCount = 0;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
			}

		}

		else if ((TargetPillarPosition - 1) > CurrentPillarPosition)
		{
			recursionCurrentPillarCount++;
			CurrentPillarPosition = CurrentPillarPosition + 1;
			TargetRingPosition = TargetRingPosition + recursionTargetRingCount;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else if ((TargetPillarPosition - 1) <= CurrentPillarPosition)
		{
			if (CurrentPillarPosition == (MaxSizePillar - 1))
			{
				TargetRingPosition = 0;
				TargetPillarPosition = 0;
				CurrentRingPosition = 0;
				CurrentPillarPosition = (MaxSizePillar - 1);
				recursionCurrentRingCount = 0;
				recursionCurrentPillarCount = 0;
				recursionTargetPillarCount = 0;
				recursionTargetRingCount = 0;
				LeftToRightOverFlag = 1;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, recursionCurrentRingCount, TargetPillarPosition, TargetRingPosition);
			}
			else
			{

				TargetPillarPosition = TargetPillarPosition + 1;
				recursionTargetPillarCount++;
				TargetRingPosition = TargetRingPosition + recursionTargetRingCount;
				CurrentRingPosition = CurrentRingPosition + recursionCurrentRingCount;
				recursionCurrentRingCount = 0;
				recursionTargetRingCount = 0;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, recursionCurrentRingCount, TargetPillarPosition, TargetRingPosition);
			}
		}

	}


	else if (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] != 0) && (RightToLeftOverFlag == 0))/* Move Right To Left*/
	{
		if ((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] == MaxSizeRing)
		{
			CurrentPillarPosition = CurrentPillarPosition + 1;
			recursionCurrentPillarCount++;
			return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
		}
		else
		{
			if ((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] < (*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition])
			{
				TargetRingPosition = TargetRingPosition - 1;
				recursionTargetRingCount++;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
			}
			else if ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] == 0)
			{
				if ((*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition + 1] != 0)
				{
					(*Vector_Hanoi)[TargetPillarPosition][TargetRingPosition] = (*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition];
					(*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] = 0;
					TargetRingPosition = TargetRingPosition + recursionTargetRingCount;
					TargetPillarPosition = TargetPillarPosition - recursionTargetPillarCount;
					recursionTargetRingCount = 0;
					recursionTargetPillarCount = 0;
					if (CurrentRingPosition < MaxSizeRing)
					{
						CurrentRingPosition = CurrentRingPosition + 1;
						recursionCurrentRingCount++;
						return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
					}
					else
					{
						CurrentRingPosition = CurrentRingPosition + recursionCurrentRingCount;
						CurrentPillarPosition = CurrentPillarPosition - recursionCurrentPillarCount;
						recursionCurrentRingCount = 0;
						recursionCurrentPillarCount = 0;
						return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
					}
				}
				else
				{
					TargetRingPosition = TargetRingPosition + 1;
					recursionTargetRingCount++;
					return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition, TargetRingPosition);
				}
			}
			else if (TargetPillarPosition < (CurrentPillarPosition - 1))
			{
				recursionTargetPillarCount++;
				return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition, TargetPillarPosition - 1, TargetRingPosition + recursionTargetRingCount);
			}
			else if (TargetPillarPosition = (CurrentPillarPosition - 1))
			{
				if (CurrentPillarPosition == 1)
				{
					TargetRingPosition = (MaxSizeRing - 1);
					TargetPillarPosition = (MaxSizePillar - 1);
					CurrentRingPosition = 0;
					CurrentPillarPosition = 0;
					recursionCurrentRingCount = 0;
					recursionCurrentPillarCount = 0;
					recursionTargetPillarCount = 0;
					recursionTargetRingCount = 0;
					LeftToRightOverFlag = 0;
					RightToLeftOverFlag = 1;
					return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, recursionCurrentRingCount, TargetPillarPosition, TargetRingPosition);
				}
				else
				{

					TargetPillarPosition = 0;
					TargetRingPosition = 0;
					CurrentRingPosition = CurrentRingPosition + recursionCurrentRingCount;
					CurrentPillarPosition = CurrentPillarPosition - 1;
					recursionCurrentRingCount++;
					recursionCurrentRingCount = 0;
					recursionTargetPillarCount = 0;
					recursionTargetRingCount = 0;
					return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, recursionCurrentRingCount, TargetPillarPosition, TargetRingPosition);
				}
			}
		}
		

	}
	else if (((*Vector_Hanoi)[CurrentRingPosition][CurrentPillarPosition] == 0))
	{
		recursionCurrentRingCount++;
		return Tower_of_Hanoi(Vector_Hanoi, CurrentPillarPosition, CurrentRingPosition + 1, TargetPillarPosition, TargetRingPosition);
	}
#if 0
		for (int compare = 0; compare > VectorRingSize; compare++)
		{
			if ((*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] > (*Vector_Hanoi)[StartNumRing][StartNumPillar])
			{
				;
			}
			else if ((*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] == 0)
			{
				(*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] = (*Vector_Hanoi)[StartNumRing][StartNumPillar];
				(*Vector_Hanoi)[StartNumRing][StartNumPillar] = 0;
				break;
			}
			else if ((*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] != 0)
			{
				for (int compare2 = 0; compare2 > VectorPillarSize; compare2++)
				{
					if ((*Vector_Hanoi)[VectorRingSize][VectorPillarSize - compare2] == 0)
					{
						(*Vector_Hanoi)[VectorRingSize][VectorPillarSize - compare2] = (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize];
						(*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] = 0;
						break;
					}
					else if ((*Vector_Hanoi)[VectorRingSize][VectorPillarSize - compare2] < (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize])
					{
						;
					}
					else if ((*Vector_Hanoi)[VectorRingSize][VectorPillarSize - compare2] > (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize])
					{
						for (int compare3 = 1; compare3 > VectorRingSize; compare3++)
						{
							if ((*Vector_Hanoi)[VectorRingSize- compare3][VectorPillarSize - compare2] == 0)
							{
								(*Vector_Hanoi)[VectorRingSize - compare3][VectorPillarSize - compare2] = (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize];
								(*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize] = 0;
								break;
							}
							else if ((*Vector_Hanoi)[VectorRingSize - compare3][VectorPillarSize - compare2] > (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize])
							{
								;
							}
							else if (((*Vector_Hanoi)[VectorRingSize - compare3][VectorPillarSize - compare2] < (*Vector_Hanoi)[VectorRingSize - compare][VectorPillarSize])
							{
								break;
							}
						}
						
					}
					else
					{
						return HanoiError;
					}
				}
			}
		}
#endif

	else
	{
		return 0;
	}


	
}

