

import java.util.Arrays;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class BinaryTreeClass {
	 private Node root;

	    private static class Node{
	        Node left;
	        Node right;
	        int data;
	        String word;

	        Node (int newData, String newWord){
	            left = null;
	            right = null;
	            data = newData;
	            word = newWord;
	        }
	    }

	    public BinaryTreeClass(){
	        root = null;
	    }

	    public void insert(int data, String word){
	        root = insert(root, data, word);
	    }

	    private Node insert(Node node, int data, String word){
	        if(node==null){
	            node = new Node(data, word);
	        }
	        else{
	            if(data <= node.data){
	                node.left = insert(node.left, data, word);
	            }
	            else {
	                node.right = insert(node.right, data, word);
	            }
	        }
	        return node;
	    }

	    public boolean search(int data){
	        return(search(root, data));
	    }

	    private boolean search(Node node, int data){
	        if (node==null){
	            return false;
	        }

	        if (data==node.data){
	            return true;
	        }
	        else if (data<node.data){
	            return search(node.left, data);
	        }
	        else {
	            return search(node.right, data);
	        }
	    }

	    public void printTree(){
	        printTree(root);
	        System.out.println();
	    }

	    private void printTree(Node node){
	        if(node==null) return;

	        printTree(node.left);
	        System.out.print(node.data + " " + node.word + " ");
	        printTree(node.right);
	    }

       
        public static void accWordCount(String source, BinaryTreeClass bt){	
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
        	
        	System.out.println("Number of words: " + ll.size());
        	
        	for(int i = 0; i < ll.size(); i++){
        		accInt[i] = 1;
        		for(int j = i+1; j <= ll.size()-1; j++){
        			if(ll.get(i).equals(ll.get(j))) {
        				accInt[i]++;
        				ll.remove(j);
        				j--;
        			}     			
        		}
        		bt.insert(accInt[i], (String) ll.get(i));
        	}
        }



    	public void btClass(String message){
	    BinaryTreeClass bt = new BinaryTreeClass();
        accWordCount(message, bt);
        System.out.println("Binary tree sorted: ");
        bt.printTree();
	    }
}