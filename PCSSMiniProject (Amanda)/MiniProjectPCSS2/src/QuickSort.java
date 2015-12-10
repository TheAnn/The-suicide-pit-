

import java.util.Arrays;
import java.util.LinkedList;


public class QuickSort{
	
	public void qSort(int low, int high, int array[], String llStr[] /*minimum maximum elements of the array*/){
		 int i = low, j = high;
		
	        int pivot = array[low + (high-low)/2];
	        while (i<=j){
	            while (array[i]<pivot){
	                i++;
	            }
	            while(array[j]> pivot){
	                j--;
	            }
	            if (i<=j){
	                swap(i,j, array, llStr);
	                i++;
	                j--;
	            }
	        }
	        if (low <j)
	            qSort(low,j, array, llStr);
	        if (i<high)
	            qSort (i, high, array, llStr);
	    }
	    
	    public void swap(int i, int j, int array[], String llStr[]){
	    	String tempStr = llStr[i];
	    	llStr[i] = llStr[j];
	        llStr[j] = tempStr;
	        
	    	int temp = array[i];
	        array[i] = array[j];
	        array[j] = temp;
	    }
		 
	  public static void accWordCount(String source, QuickSort qs){	
      	LinkedList ll = new LinkedList();        	
      	char[] sourceArr=source.toCharArray();
      	int newPos = 0;
      	for(int i=0;i<sourceArr.length;i++){
      		char x = source.charAt(i);
      		if(!Character.isLetter(x) || i+1 == sourceArr.length ){
      			if(i+1 == sourceArr.length && Character.isLetter(x))
      				i++;
      			char[] newSourceArr = Arrays.copyOfRange(sourceArr, newPos, i);
      			String sourcea = new String(newSourceArr);
      			ll.addLast(sourcea);
      			newPos = i + 1;
      			
      		}
      	}
      	
      	int[] accInt = new int [ll.size()];
      	//System.out.println("Number of words & additional spaces: " + ll.size());
      	for(int i = 0; i < ll.size(); i++){
      		accInt[i] = 1;
      		for(int j = i+1; j <= ll.size()-1; j++){
      			if(ll.get(i).equals(ll.get(j))) {
      				accInt[i]++;
      				ll.remove(j);
      				j--;
      			}     			
      		}	
      	}
        String[] llStr =  (String[]) ll.toArray(new String[0]);
      	qs.qSort(0, ll.size()-1, accInt, llStr);
      	System.out.println("Qucksort sorted: ");
      	for(int i = 0; i < ll.size(); i++){
      		System.out.print(accInt[i] + " ");
      		System.out.print(llStr[i] + "; ");
      	}
      	
      }
	  
	
	  public void qsClass(String message){  
		  QuickSort qs = new QuickSort();
		  accWordCount(message, qs);  
		  System.out.println("\n");
	}
}