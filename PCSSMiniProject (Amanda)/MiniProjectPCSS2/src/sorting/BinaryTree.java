package sorting;

public class BinaryTree extends Thread{

private Node root;
    
    private static class Node{
        int data;
        Node left;
        Node right;
        
        Node(int newdata){
            data = newdata;
            left = null;
            right = null;
        }
        
    }
    
    public void BinaryTree(){
        root = null;
    }
    
    public void insert(int data){
        root = insert(root,data);
    }
    
    private Node insert(Node node, int data){
        if (node==null){
            node = new Node(data);
        }
        else {
            if (data <=node.data){
                node.left = insert(node.left, data);
            }
            else {
                node.right = insert(node.right, data);
            }
        }
        return node;
    }
    
    //we search a data and wanna know if this is inside our tree
    public boolean search(int data){
    	return (search(root, data));
    	
    }
    
    private boolean search(Node node, int data){
    	//we have a specific way of filling the tree up
    	//we only need to search the tree for the relevant parts
    	if (node == null){
    		//if we find nothing in the node it returns false
    		return false;
    	}
    	
    	if (data == node.data){
    		return true;
    	}
    	
    	else if (data < node.data){
    		//if this is the case we know we have to look at the left side of the tree to find it
    		return search(node.left, data);
    	}
    	
    	else {
    		//data is greater then the data in the node
    		return search(node.right, data);
    	}
    }
    
    public void printTree(){
    	printTree(root);
    	System.out.println();
    }
    
    private void printTree(Node node){
    	//the moment we call a function on an empty node we can stop
    	if (node == null) return;
    	
    	printTree(node.left);
    	System.out.print(node.data+ " ");
    	printTree(node.right);
    }
    
	public void run(){

	}
}
