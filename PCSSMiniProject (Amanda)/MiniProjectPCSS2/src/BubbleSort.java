

import java.util.Arrays;
import java.util.LinkedList;

public class BubbleSort {

	public void bSort(int array[], String llStr[]){

		int n = llStr.length;
        int temp = 0;
        String tempStr;
        
        for (int i=0; i<n; i++){
            boolean noSwap = true;
            for (int j=1; j<(n-i); j++){
                if (array[j-1]>array[j]){
                    temp = array[j-1];
                    array[j-1] = array[j];
                    array[j]=temp;
                    
                    tempStr = llStr[j-1];
                    llStr[j-1] = llStr[j];
                    llStr[j]=tempStr;
                    noSwap=false;
                }
            }
           if (noSwap) i=n;
        }
        
    }
	
	  public static void accWordCount(String source, BubbleSort bs){	
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
	        
	      	bs.bSort(accInt, llStr);
	      	
	      	System.out.println("Bubblesort sorted: ");
	      	for(int i = 0; i < ll.size(); i++){
	      		System.out.print(accInt[i] + " ");
	      		System.out.print(llStr[i] + "; ");
	      	}
	      	System.out.println();
	      }
	
	  public void bsClass(String message){  
		BubbleSort bs = new BubbleSort();
		  accWordCount(message, bs); 

	}
}
