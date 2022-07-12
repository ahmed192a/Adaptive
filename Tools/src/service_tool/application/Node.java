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
	public ArrayList<Node> getChilds() {
		return childs;
	}
	public String getVal() {
		return val;
	}
	public static Node ParseXML(String Data) {
		Node root = new Node(null,"root");  
		Node current = root;
		for(int Ptr = 0;Ptr < Data.length();Ptr++) {
			if(Character.isWhitespace(Data.charAt(Ptr)))continue;
			else if(Data.charAt(Ptr)=='<') {
				Ptr++;
				if(Ptr==Data.length())return null;
				else if(Data.charAt(Ptr) == '/'){
					Ptr++;
					String nextTag = get_tag(Data,Ptr);
					if(current.getTag().equals(nextTag)) {
						current = current.getParent();
						Ptr+=nextTag.length();
					}
					else return null;
				}
				else {
					String nextTag = get_tag(Data,Ptr);
					Ptr+=nextTag.length();
					if(hasChild(Data,Ptr+1)){
						current = current.addNode(new Node(current,nextTag));
					}
					else {
						int end = Ptr + 1;
						for(; end+1!=Data.length() && Data.charAt(end+1)!='<'&& Data.charAt(end+1)!='>';end++);
						if(end+1 == Data.length() || Data.charAt(end+1)=='>')return null;
						String Val= Data.substring(Ptr+1, end+1);
						Ptr = end;
						current = current.addNode(new Node(current,nextTag,Val));
					}
				}
			}
			else return null;
		}
		if(current != root)return null;
		else return root;
	}
	private static String get_tag(String Data,int start) {
		int end = start;
		for(;end+1!=Data.length() && Data.charAt(end+1)!='<' && Data.charAt(end+1)!='>';end++);
		if(end + 1 == Data.length() || Data.charAt(end+1)=='<')return "ERROR";
		return Data.substring(start,end+1);
	}
	private static boolean hasChild(String Data,int pos) {
		while(pos!=Data.length() && Character.isWhitespace(Data.charAt(pos)))pos++;
		if(pos == Data.length() || Data.charAt(pos) == '<')return true;
		else return false;
	}	
	public ArrayList<Node> Search(String...strings) {
		ArrayList<Node> Res = new ArrayList<Node>();
		Node current = this;
		for (String path : strings) {
			for(Node i : current.getChilds()) {
				if(i.getTag().equals(path)) {
					if(path.equals(strings[strings.length - 1])) {
						Res.add(i);
					}
					else {
						current = i;
						break;	
					}
				}
			}
		}
        return Res;
	}
}


