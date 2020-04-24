#include "sort.h"


bool cardsCompare(const Card& card1, const Card& card2)
{
	if (card1.getColor() != card2.getColor())
		return (card1.getColor() < card2.getColor());
	return (card1.getRank() < card2.getRank());
}

int partition(Card arr[], int low, int high)
{
	Card pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (cardsCompare(arr[j], pivot))
		{
			i++;    // increment index of smaller element 
			std::swap<Card>(arr[i], arr[j]);
		}
	}
	std::swap<Card>(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(Card arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}