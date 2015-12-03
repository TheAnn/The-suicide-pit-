package sorting;

import java.util.HashMap;
import java.util.Map;

public class QuickSort extends Sorting {


	//26 is the size of the hash map
	Map<String, Integer> numWords = new HashMap<String, Integer>(26);

	public QuickSort() {
		super("QuikSort");
	}

	public void qSort(int low, int high /*minimum maximum elements of the array*/){
		int i = low, j = high;

		//the pivot is in the middle. here we find the middle
		int pivot = array[low + (high-low)/2];

		//as long as the low is less or equal then our high index we do something
		while (i <= j)
			//check if the left element is less then the pivot. then leave it there if it is
			while (array[i] < pivot){
				i++;
				increaseCounter();
			}
		//check the other maximum side of the array. right most side
		while (array[j] > pivot){
			j--;
			increaseCounter();
		}
		//we need to check if we are still in boundaries with the pivot
		if (i<=j){
			swap(i,j);
			//check if all the elements are on place
			i++;
			j--;
			increaseCounter();
		}
		if (low<j)
			qSort(low,j);
		if (high<high)
			qSort (i, high);
	} 


	public void swap (int i, int j){
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;

	}

	public void run(){

	}
}
