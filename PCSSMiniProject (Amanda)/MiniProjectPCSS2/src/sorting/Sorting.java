package sorting;

import java.util.Random;

public class Sorting extends Thread{
	//put integers in the array
	int [] array = new int[100];
	//counter for the task of keeping track of the complexity of the two algorithms
	int counter =0;
	//we are gonna implement other types of sorting, like bubble and quick here we specify which one we are working with
	String name = "empty";

	public Sorting (String name){
		//this specific sorting class will have a name
		this.name = name;
	}

	public void getUserInput(){
		Random rg = new Random();
		for (int i=0; i < 100; i++)
			array[i] = rg.nextInt(1000);
	}

	//complexity counter
	public void increaseCounter(){
		//everytime in our algorithm when we think that this counts as a processing count we call this
		//at the end we will know how many steps the algorithm took to solve it
		counter++;
	}

	public void printArray(){
		System.out.println();
		for (int i=0; i < array.length; i++){
			System.out.print(array[i]);
			//here we choose print without printLN to make it pop up by the side
			System.out.print(" ");
		}
	}

	//what the complexity of this algorithm is
	public void printComplexity(){
		System.out.println("\nComplexity of " + name + ": " + "\nInput size: " + array.length + "\nNumer of executed commands: " + counter);
	}	

}
