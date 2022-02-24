package application;

import java.util.ArrayList;

public class Node {
	private Node parent;
	private String tag;
	private String val;
	private boolean isParent;
	private ArrayList<Node> childs = new ArrayList<Node>();
	
	public Node getParent() {
		return parent;
	}
	public Node(Node parent,String name,String value) {
		this.parent = parent;
		this.tag = name;
		this.val = value;
		this.isParent = false;
	}
	public Node(Node parent,String name) {
		this.parent = parent;
		this.tag = name;
		this.isParent = true;
	}
	public Node addNode(Node child) {
		childs.add(child);
		return child;
	}
	public boolean isParent() {
		return isParent;
	}
	public String getTag() {
		return tag;
	}

}
